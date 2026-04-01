/*
 * Copyright (C) Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "colo_engine.h"

#include "common.hpp"
#include "input_util.hpp"
#include "joystick-support.hpp"
#include "scene_manager.hpp"
#include "welcome_scene.hpp"

// verbose debug logs on?
#define VERBOSE_LOGGING 1

#if VERBOSE_LOGGING
#define VLOGD LOGD
#else
#define VLOGD
#endif

// max # of GL errors to print before giving up
#define MAX_GL_ERRORS 200

// ADD THIS LINE HERE:
ColoEngine *g_ColoEngine = nullptr; 

//static ColoEngine *_singleton = NULL;
// ... rest of your code

static ColoEngine *_singleton = NULL;

// workaround for internal bug b/149866792
static ColoEngineSavedState appState = {false};

ColoEngine::ColoEngine(struct android_app *app) {
  LOGD("ColoEngine: initializing.");
  mApp = app;
  mHasFocus = mIsVisible = mHasWindow = false;
  mHasGLObjects = false;
  mEglDisplay = EGL_NO_DISPLAY;
  mEglSurface = EGL_NO_SURFACE;
  mEglContext = EGL_NO_CONTEXT;
  mEglConfig = 0;
  mSurfWidth = mSurfHeight = 0;
  mApiVersion = 0;
  mJniEnv = NULL;
  memset(&mState, 0, sizeof(mState));
  mIsFirstFrame = true;

  if (app->savedState != NULL) {
    // we are starting with previously saved state -- restore it
    mState = *(struct ColoEngineSavedState *)app->savedState;
  }

  // only one instance of ColoEngine may exist!
  MY_ASSERT(_singleton == NULL);
  _singleton = this;

  VLOGD("ColoEngine: querying API level.");
  LOGD("ColoEngine: API version %d.", mApiVersion);
  
  g_ColoEngine = this;
  
}

ColoEngine *ColoEngine::GetInstance() {
  MY_ASSERT(_singleton != NULL);
  return _singleton;
}

ColoEngine::~ColoEngine() {
  VLOGD("ColoEngine: destructor running");
  KillContext();
  if (mJniEnv) {
    LOGD("Detaching current thread from JNI.");
    mApp->activity->vm->DetachCurrentThread();
    LOGD("Current thread detached from JNI.");
    mJniEnv = NULL;
  }
  _singleton = NULL;
}

static void _handle_cmd_proxy(struct android_app *app, int32_t cmd) {
  ColoEngine *engine = (ColoEngine *)app->userData;
  engine->HandleCommand(cmd);
}

static int _handle_input_proxy(struct android_app *app, AInputEvent *event) {
  ColoEngine *engine = (ColoEngine *)app->userData;
  return engine->HandleInput(event) ? 1 : 0;
}

bool ColoEngine::IsAnimating() {
  return mHasFocus && mIsVisible && mHasWindow;
}

// Support up to 10 fingers
PointerState g_PointerTracker[10];


// from GameActivity Default project Renderer::
void ColoEngine::ColoHandleInput() {
    auto *inputBuffer = android_app_swap_input_buffers(mApp);
    if (!inputBuffer) return;

    SceneManager *mgr = SceneManager::GetInstance();

    // 1. Process Motion Events (Touch/Mouse)
    for (auto i = 0; i < inputBuffer->motionEventsCount; i++) {
        auto &motionEvent = inputBuffer->motionEvents[i];
        auto action = motionEvent.action & AMOTION_EVENT_ACTION_MASK;
        int pointerIndex = (motionEvent.action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) 
                           >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

        auto &pointer = motionEvent.pointers[pointerIndex];
        PointerCoords coords;
        coords.x = GameActivityPointerAxes_getX(&pointer);
        coords.y = GameActivityPointerAxes_getY(&pointer);
        coords.isScreen = true; // Relative to window

        switch (action) {
            case AMOTION_EVENT_ACTION_DOWN:
            case AMOTION_EVENT_ACTION_POINTER_DOWN: { // <--- Add brace
                int id = pointer.id;
                if (id < 10) {
                    g_PointerTracker[id].lastX = coords.x;
                    g_PointerTracker[id].lastY = coords.y;
                    g_PointerTracker[id].isActive = true;
                }
                mgr->OnPointerDown(id, &coords);
                aout << "(" << id << ", " << coords.x << ", " << coords.y << ") Pointer Down" << std::endl;
                break;
            } // <--- Close brace

            case AMOTION_EVENT_ACTION_UP:
            case AMOTION_EVENT_ACTION_POINTER_UP:
            case AMOTION_EVENT_ACTION_CANCEL: {
                int id = pointer.id;
                if (id < 10) {
                    g_PointerTracker[id].isActive = false;
                }
                mgr->OnPointerUp(id, &coords);
                aout << "(" << id << ", " << coords.x << ", " << coords.y << ") Pointer Up/Cancel" << std::endl;
                break;
            }

            case AMOTION_EVENT_ACTION_MOVE: { // <--- Add brace
                for (int j = 0; j < motionEvent.pointerCount; j++) {
                    auto &p = motionEvent.pointers[j];
                    float curX = GameActivityPointerAxes_getX(&p);
                    float curY = GameActivityPointerAxes_getY(&p);
                    int id = p.id;

                    if (id >= 10) continue;

                    float dx = 0.0f;
                    float dy = 0.0f;

                    if (g_PointerTracker[id].isActive) {
                        dx = curX - g_PointerTracker[id].lastX;
                        dy = curY - g_PointerTracker[id].lastY;
                    }

                    g_PointerTracker[id].lastX = curX;
                    g_PointerTracker[id].lastY = curY;
                    g_PointerTracker[id].isActive = true;

                    mgr->OnPointerMove(id, curX, curY, dx, dy);

                    // Reduced spam: only log if there is actual movement
                    if (dx != 0.0f || dy != 0.0f) {
                        aout << "ID: " << id << " DX: " << dx << " DY: " << dy << std::endl;
                    }
                }
                break;
            } // <--- Close brace
        }
    }

    // 2. Process Key Events
    for (auto i = 0; i < inputBuffer->keyEventsCount; i++) {
        auto &keyEvent = inputBuffer->keyEvents[i];
        if (keyEvent.action == AKEY_EVENT_ACTION_DOWN) {
            mgr->OnKeyDown(keyEvent.keyCode);
        } else if (keyEvent.action == AKEY_EVENT_ACTION_UP) {
            mgr->OnKeyUp(keyEvent.keyCode);
        }
    }

    android_app_clear_motion_events(inputBuffer);
    android_app_clear_key_events(inputBuffer);
}

void ColoEngine::GameLoop() {
	
	   aout << "void ColoEngine::GameLoop():"<<std::endl;
    LOGD("void ColoEngine::GameLoop():"); // Use LOGD here

  mApp->userData = this;
  mApp->onAppCmd = _handle_cmd_proxy;
  // mApp->onInputEvent = _handle_input_proxy;
	// ColoHandleInput(); // DO NOT PUT HERE, INFINIATE LOOP, APP START, BUT STOPPED FOREVER HERE.!
// If your device/emulator is slow to report Focus, IsAnimating() stays false, and the loop stays stuck in ALooper_pollOnce (blocking mode). By moving ColoHandleInput() inside the if (IsAnimating()) block, you ensure you don't touch the input buffers until the Android Activity is fully "Alive."
// 2. Log this immediately so you know you entered the loop
    aout << "ColoEngine: Entering GameLoop" << std::endl;
    LOGD("ColoEngine: Entering GameLoop"); // Use LOGD here

  while (!mApp->destroyRequested) {
    // If not animating, block until we get an event; if animating, don't block.
    struct android_poll_source *source = nullptr;
    auto result = ALooper_pollOnce(IsAnimating() ? 0 : -1, NULL, nullptr,
                            (void **)&source);
    MY_ASSERT(result != ALOOPER_POLL_ERROR);
    // process event
    if (source != NULL) {
      source->process(mApp, source);
    }

    if (IsAnimating()) {
		ColoHandleInput(); // new place after theres input to pool in, PULL-IN!
      DoFrame();
    }
  }
}

JNIEnv *ColoEngine::GetJniEnv() {
  if (!mJniEnv) {
    LOGD("Attaching current thread to JNI.");
    if (0 != mApp->activity->vm->AttachCurrentThread(&mJniEnv, NULL)) {
      LOGE("*** FATAL ERROR: Failed to attach thread to JNI.");
      ABORT_GAME;
    }
    MY_ASSERT(mJniEnv != NULL);
    LOGD("Attached current thread to JNI, %p", mJniEnv);
  }

  return mJniEnv;
}

void ColoEngine::HandleCommand(int32_t cmd) {
  SceneManager *mgr = SceneManager::GetInstance();

  VLOGD("ColoEngine: handling command %d.", cmd);
  switch (cmd) {
    case APP_CMD_SAVE_STATE: {
      // The system has asked us to save our current state.
      VLOGD("ColoEngine: APP_CMD_SAVE_STATE");
      mState.mHasFocus = mHasFocus;
	  
	  // Grab the camera from the current scene
    SceneManager *mgr = SceneManager::GetInstance();
  //  Scene* current = mgr->GetCurrentScene();
    Scene* current = mgr->GetScene(); // Use the name from your .hpp
	
    // Check if the current scene is actually a UiScene (or derivative)
    UiScene* uiScene = static_cast<UiScene*>(current);

    if (uiScene != nullptr) {
      //  PerspectiveCamera& cam = uiScene->mCamera;
       //2. The Benefit of making it public, harder to debug 
      //  mState.camX = cam.Position.x;
      //  mState.camY = cam.Position.y;
      //  mState.camZ = cam.Position.z;
      //  mState.camYaw = cam.Yaw;
      //  mState.camPitch = cam.Pitch;
      //  mState.isInitialized = true;
	    PerspectiveCamera* cam = uiScene->GetCamera();
        if (cam) {
         mState.camX = cam->Position.x;
		 mState.camY = cam->Position.y;
         mState.camZ = cam->Position.z;
         mState.camYaw = cam->Yaw;
         mState.camPitch = cam->Pitch;
         mState.isInitialized = true;
         // ... etc
        }
    }
	  
      mApp->savedState = malloc(sizeof(mState));
      *((ColoEngineSavedState *)mApp->savedState) = mState;
      mApp->savedStateSize = sizeof(mState);
      break;
  } // <--- CLOSE BRACE HERE
    case APP_CMD_INIT_WINDOW:
      // We have a window!
      VLOGD("ColoEngine: APP_CMD_INIT_WINDOW");
      if (mApp->window != NULL) {
        mHasWindow = true;
        if (mApp->savedStateSize == sizeof(mState) &&
            mApp->savedState != nullptr) {
          mState = *((ColoEngineSavedState *)mApp->savedState);
          mHasFocus = mState.mHasFocus;
        } else {
          // Workaround APP_CMD_GAINED_FOCUS issue where the focus state is not
          // passed down from NativeActivity when restarting Activity
          mHasFocus = appState.mHasFocus;
        }
      }
      VLOGD("HandleCommand(%d): hasWindow = %d, hasFocus = %d", cmd,
            mHasWindow ? 1 : 0, mHasFocus ? 1 : 0);
      break;
    case APP_CMD_TERM_WINDOW:
      // The window is going away -- kill the surface
      VLOGD("ColoEngine: APP_CMD_TERM_WINDOW");
      KillSurface();
      mHasWindow = false;
      break;
    case APP_CMD_GAINED_FOCUS:
      VLOGD("ColoEngine: APP_CMD_GAINED_FOCUS");
      mHasFocus = true;
      mState.mHasFocus = appState.mHasFocus = mHasFocus;
      break;
    case APP_CMD_LOST_FOCUS:
      VLOGD("ColoEngine: APP_CMD_LOST_FOCUS");
      mHasFocus = false;
      mState.mHasFocus = appState.mHasFocus = mHasFocus;
      break;
    case APP_CMD_PAUSE:
      VLOGD("ColoEngine: APP_CMD_PAUSE");
      mgr->OnPause();
      break;
    case APP_CMD_RESUME:
      VLOGD("ColoEngine: APP_CMD_RESUME");
      mgr->OnResume();
      break;
    case APP_CMD_STOP:
      VLOGD("ColoEngine: APP_CMD_STOP");
      mIsVisible = false;
      break;
    case APP_CMD_START:
      VLOGD("ColoEngine: APP_CMD_START");
      mIsVisible = true;
      break;
    case APP_CMD_WINDOW_RESIZED:
    case APP_CMD_CONFIG_CHANGED:
      VLOGD("ColoEngine: %s", cmd == APP_CMD_WINDOW_RESIZED
                                    ? "APP_CMD_WINDOW_RESIZED"
                                    : "APP_CMD_CONFIG_CHANGED");
      // Window was resized or some other configuration changed.
      // Note: we don't handle this event because we check the surface
      // dimensions every frame, so that's how we know it was resized. If you
      // are NOT doing that, then you need to handle this event!
      break;
    case APP_CMD_LOW_MEMORY:
      VLOGD("ColoEngine: APP_CMD_LOW_MEMORY");
      // system told us we have low memory. So if we are not visible, let's
      // cooperate by deallocating all of our graphic resources.
      if (!mHasWindow) {
        VLOGD("ColoEngine: trimming memory footprint (deleting GL objects).");
        KillGLObjects();
      }
      break;
    default:
      VLOGD("ColoEngine: (unknown command). %d", cmd);
      break;
  }

  VLOGD("ColoEngine: STATUS: F%d, V%d, W%d, EGL: D %p, S %p, CTX %p, CFG %p",
        mHasFocus, mIsVisible, mHasWindow, mEglDisplay, mEglSurface,
        mEglContext, mEglConfig);
}

static bool _cooked_event_callback(struct CookedEvent *event) {
  SceneManager *mgr = SceneManager::GetInstance();
  PointerCoords coords;
  memset(&coords, 0, sizeof(coords));
  coords.x = event->motionX;
  coords.y = event->motionY;
  coords.minX = event->motionMinX;
  coords.maxX = event->motionMaxX;
  coords.minY = event->motionMinY;
  coords.maxY = event->motionMaxY;
  coords.isScreen = event->motionIsOnScreen;

  switch (event->type) {
    case COOKED_EVENT_TYPE_JOY:
      mgr->UpdateJoy(event->joyX, event->joyY);
      return true;
    case COOKED_EVENT_TYPE_POINTER_DOWN:
      mgr->OnPointerDown(event->motionPointerId, &coords);
      return true;
    case COOKED_EVENT_TYPE_POINTER_UP:
      mgr->OnPointerUp(event->motionPointerId, &coords);
      return true;
    case COOKED_EVENT_TYPE_POINTER_MOVE:
     // mgr->OnPointerMove(event->motionPointerId, &coords);
      return true;
    case COOKED_EVENT_TYPE_KEY_DOWN:
      mgr->OnKeyDown(event->keyCode);
      return true;
    case COOKED_EVENT_TYPE_KEY_UP:
      mgr->OnKeyUp(event->keyCode);
      return true;
    case COOKED_EVENT_TYPE_BACK:
      return mgr->OnBackKeyPressed();
    default:
      return false;
  }
}

bool ColoEngine::HandleInput(AInputEvent *event) {
  return CookEvent(event, _cooked_event_callback);
}

bool ColoEngine::InitDisplay() {
  if (mEglDisplay != EGL_NO_DISPLAY) {
    // nothing to do
    LOGD("ColoEngine: no need to init display (already had one).");
    return true;
  }

  LOGD("ColoEngine: initializing display.");
  mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (EGL_FALSE == eglInitialize(mEglDisplay, 0, 0)) {
    LOGE("ColoEngine: failed to init display, error %d", eglGetError());
    return false;
  }
  return true;
}

bool ColoEngine::InitSurface() {
  // need a display
  MY_ASSERT(mEglDisplay != EGL_NO_DISPLAY);

  if (mEglSurface != EGL_NO_SURFACE) {
    // nothing to do
    LOGD("ColoEngine: no need to init surface (already had one).");
    return true;
  }

  LOGD("ColoEngine: initializing surface.");

  EGLint numConfigs;

  const EGLint attribs[] = {EGL_RENDERABLE_TYPE,
                            EGL_OPENGL_ES2_BIT,  // request OpenGL ES 2.0
                            EGL_SURFACE_TYPE,
                            EGL_WINDOW_BIT,
                            EGL_BLUE_SIZE,
                            8,
                            EGL_GREEN_SIZE,
                            8,
                            EGL_RED_SIZE,
                            8,
                            EGL_DEPTH_SIZE,
                            16,
                            EGL_NONE};

  // since this is a simple sample, we have a trivial selection process. We pick
  // the first EGLConfig that matches:
  eglChooseConfig(mEglDisplay, attribs, &mEglConfig, 1, &numConfigs);

  // create EGL surface
  mEglSurface =
      eglCreateWindowSurface(mEglDisplay, mEglConfig, mApp->window, NULL);
  if (mEglSurface == EGL_NO_SURFACE) {
    LOGE("Failed to create EGL surface, EGL error %d", eglGetError());
    return false;
  }

  LOGD("ColoEngine: successfully initialized surface.");
  return true;
}

bool ColoEngine::InitContext() {
  // need a display
  MY_ASSERT(mEglDisplay != EGL_NO_DISPLAY);

  EGLint attribList[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                         EGL_NONE};  // OpenGL 2.0

  if (mEglContext != EGL_NO_CONTEXT) {
    // nothing to do
    LOGD("ColoEngine: no need to init context (already had one).");
    return true;
  }

  LOGD("ColoEngine: initializing context.");

  // create EGL context
  mEglContext = eglCreateContext(mEglDisplay, mEglConfig, NULL, attribList);
  if (mEglContext == EGL_NO_CONTEXT) {
    LOGE("Failed to create EGL context, EGL error %d", eglGetError());
    return false;
  }

  LOGD("ColoEngine: successfull initialized context.");

  return true;
}

void ColoEngine::ConfigureOpenGL() {
  glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

bool ColoEngine::PrepareToRender() {
  if (mEglDisplay == EGL_NO_DISPLAY || mEglSurface == EGL_NO_SURFACE ||
      mEglContext == EGL_NO_CONTEXT) {
    // create display if needed
    if (!InitDisplay()) {
      LOGE("ColoEngine: failed to create display.");
      return false;
    }

    // create surface if needed
    if (!InitSurface()) {
      LOGE("ColoEngine: failed to create surface.");
      return false;
    }

    // create context if needed
    if (!InitContext()) {
      LOGE("ColoEngine: failed to create context.");
      return false;
    }

    LOGD(
        "ColoEngine: binding surface and context (display %p, surface %p, "
        "context %p)",
        mEglDisplay, mEglSurface, mEglContext);

    // bind them
    if (EGL_FALSE ==
        eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext)) {
      LOGE("ColoEngine: eglMakeCurrent failed, EGL error %d", eglGetError());
      HandleEglError(eglGetError());
    }

    // configure our global OpenGL settings
    ConfigureOpenGL();
  }
  if (!mHasGLObjects) {
    LOGD("ColoEngine: creating OpenGL objects.");
    if (!InitGLObjects()) {
      LOGE("ColoEngine: unable to initialize OpenGL objects.");
      return false;
    }
  }

  // ready to render
  return true;
}

void ColoEngine::KillGLObjects() {
  if (mHasGLObjects) {
    SceneManager *mgr = SceneManager::GetInstance();
    mgr->KillGraphics();
    mHasGLObjects = false;
  }
}

void ColoEngine::KillSurface() {
  LOGD("ColoEngine: killing surface.");
  eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  if (mEglSurface != EGL_NO_SURFACE) {
    eglDestroySurface(mEglDisplay, mEglSurface);
    mEglSurface = EGL_NO_SURFACE;
  }
  LOGD("ColoEngine: Surface killed successfully.");
}

void ColoEngine::KillContext() {
  LOGD("ColoEngine: killing context.");

  // since the context is going away, we have to kill the GL objects
  KillGLObjects();

  eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

  if (mEglContext != EGL_NO_CONTEXT) {
    eglDestroyContext(mEglDisplay, mEglContext);
    mEglContext = EGL_NO_CONTEXT;
  }
  LOGD("ColoEngine: Context killed successfully.");
}

void ColoEngine::KillDisplay() {
  // causes context and surface to go away too, if they are there
  LOGD("ColoEngine: killing display.");
  KillContext();
  KillSurface();

  if (mEglDisplay != EGL_NO_DISPLAY) {
    LOGD("ColoEngine: terminating display now.");
    eglTerminate(mEglDisplay);
    mEglDisplay = EGL_NO_DISPLAY;
  }
  LOGD("ColoEngine: display killed successfully.");
}

bool ColoEngine::HandleEglError(EGLint error) {
  switch (error) {
    case EGL_SUCCESS:
      // nothing to do
      return true;
    case EGL_CONTEXT_LOST:
      LOGW("ColoEngine: egl error: EGL_CONTEXT_LOST. Recreating context.");
      KillContext();
      return true;
    case EGL_BAD_CONTEXT:
      LOGW("ColoEngine: egl error: EGL_BAD_CONTEXT. Recreating context.");
      KillContext();
      return true;
    case EGL_BAD_DISPLAY:
      LOGW("ColoEngine: egl error: EGL_BAD_DISPLAY. Recreating display.");
      KillDisplay();
      return true;
    case EGL_BAD_SURFACE:
      LOGW("ColoEngine: egl error: EGL_BAD_SURFACE. Recreating display.");
      KillSurface();
      return true;
    default:
      LOGW("ColoEngine: unknown egl error: %d", error);
      return false;
  }
}

static void _log_opengl_error(GLenum err) {
  switch (err) {
    case GL_NO_ERROR:
      LOGE("*** OpenGL error: GL_NO_ERROR");
      break;
    case GL_INVALID_ENUM:
      LOGE("*** OpenGL error: GL_INVALID_ENUM");
      break;
    case GL_INVALID_VALUE:
      LOGE("*** OpenGL error: GL_INVALID_VALUE");
      break;
    case GL_INVALID_OPERATION:
      LOGE("*** OpenGL error: GL_INVALID_OPERATION");
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      LOGE("*** OpenGL error: GL_INVALID_FRAMEBUFFER_OPERATION");
      break;
    case GL_OUT_OF_MEMORY:
      LOGE("*** OpenGL error: GL_OUT_OF_MEMORY");
      break;
    default:
      LOGE("*** OpenGL error: error %d", err);
      break;
  }
}

void ColoEngine::DoFrame() {
  // prepare to render (create context, surfaces, etc, if needed)
  if (!PrepareToRender()) {
    // not ready
    VLOGD("ColoEngine: preparation to render failed.");
    return;
  }

    // --- HEARTBEAT LOGIC START ---
    struct timespec res;
    clock_gettime(CLOCK_MONOTONIC, &res);
    double currentTime = res.tv_sec + (double)res.tv_nsec / 1e9;

    mFrameCount++;

    // Every 60 frames, calculate and log the FPS
    if (mFrameCount >= 60) {
        double fps = 60.0 / (currentTime - mLastTime);
        LOGD("ColoEngine Heartbeat: FPS = %.2f (Surface: %dx%d)", fps, mSurfWidth, mSurfHeight);

        mFrameCount = 0;
        mLastTime = currentTime;
    }

  SceneManager *mgr = SceneManager::GetInstance();

  // how big is the surface? We query every frame because it's cheap, and some
  // strange devices out there change the surface size without calling any
  // callbacks...
  int width, height;
  eglQuerySurface(mEglDisplay, mEglSurface, EGL_WIDTH, &width);
  eglQuerySurface(mEglDisplay, mEglSurface, EGL_HEIGHT, &height);

  if (width != mSurfWidth || height != mSurfHeight) {
    // notify scene manager that the surface has changed size
    LOGD("ColoEngine: surface changed size %dx%d --> %dx%d", mSurfWidth,
         mSurfHeight, width, height);
    mSurfWidth = width;
    mSurfHeight = height;
    mgr->SetScreenSize(mSurfWidth, mSurfHeight);
    glViewport(0, 0, mSurfWidth, mSurfHeight);
  }

  // if this is the first frame, install the welcome scene
  if (mIsFirstFrame) {
    mIsFirstFrame = false;
    mgr->RequestNewScene(new WelcomeScene());
  }

    //LOGD("mgr->DoFrame(); ");

    // render!
  mgr->DoFrame();

  // swap buffers
  if (EGL_FALSE == eglSwapBuffers(mEglDisplay, mEglSurface)) {
    // failed to swap buffers...
    LOGW("ColoEngine: eglSwapBuffers failed, EGL error %d", eglGetError());
    HandleEglError(eglGetError());
  }

  // print out GL errors, if any
  GLenum e;
  static int errorsPrinted = 0;
  while ((e = glGetError()) != GL_NO_ERROR) {
    if (errorsPrinted < MAX_GL_ERRORS) {
      _log_opengl_error(e);
      ++errorsPrinted;
      if (errorsPrinted >= MAX_GL_ERRORS) {
        LOGE("*** ColoEngine: TOO MANY OPENGL ERRORS. NO LONGER PRINTING.");
      }
    }
  }
}

android_app *ColoEngine::GetAndroidApp() { return mApp; }

bool ColoEngine::InitGLObjects() {
  if (!mHasGLObjects) {
    SceneManager *mgr = SceneManager::GetInstance();
    mgr->StartGraphics();
    _log_opengl_error(glGetError());
    mHasGLObjects = true;
  }
  return true;
}
