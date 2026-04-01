#ifndef colo_native_engine_hpp
#define colo_native_engine_hpp

#include "common.hpp"

#include "AndroidOut.h"


struct PointerState {
    float lastX = 0.0f;
    float lastY = 0.0f;
    bool isActive = false;
};


struct ColoEngineSavedState {
  bool mHasFocus;
  bool isInitialized; // NEW: Explicit flag for saved data
  // Add these:
    float camX, camY, camZ;
    float camYaw, camPitch;
	
	
};

class ColoEngine {
 public:
  // create an engine
  ColoEngine(struct android_app *app);
  ~ColoEngine();

  // runs application until it dies
  void GameLoop();

  // returns the JNI environment
  JNIEnv *GetJniEnv();

  // returns the Android app object
  android_app *GetAndroidApp();

  // returns the (singleton) instance
  static ColoEngine *GetInstance();

 private:
  // variables to track Android lifecycle:
  bool mHasFocus, mIsVisible, mHasWindow;

  // are our OpenGL objects (textures, etc) currently loaded?
  bool mHasGLObjects;

  // android API version (0 if not yet queried)
  int mApiVersion;

  // EGL stuff
  EGLDisplay mEglDisplay;
  EGLSurface mEglSurface;
  EGLContext mEglContext;
  EGLConfig mEglConfig;

  // known surface size
  int mSurfWidth, mSurfHeight;

  // android_app structure
  struct android_app *mApp;

  // additional saved state
  struct ColoEngineSavedState mState;

  // JNI environment
  JNIEnv *mJniEnv;

  // is this the first frame we're drawing?
  bool mIsFirstFrame;

  // initialize the display
  bool InitDisplay();

  // initialize surface. Requires display to have been initialized first.
  bool InitSurface();

  // initialize context. Requires display to have been initialized first.
  bool InitContext();

  // kill context
  void KillContext();
  void KillSurface();
  void KillDisplay();  // also causes context and surface to get killed

  bool HandleEglError(EGLint error);

  bool InitGLObjects();
  void KillGLObjects();

  void ConfigureOpenGL();

  bool PrepareToRender();

  void DoFrame();

  bool IsAnimating();

 public:
  // these are public for simplicity because we have internal static callbacks
  void HandleCommand(int32_t cmd);
  bool HandleInput(AInputEvent *event);
  virtual  void ColoHandleInput();
// Add this getter
    ColoEngineSavedState* GetState() { return &mState; }
// Add this to get the active scene
    //UiScene* GetCurrentScene() { return mCurrentScene; }
	
    // Static or class members
    int mFrameCount = 0;
    double mLastTime = 0.0;
};

extern ColoEngine *g_ColoEngine ;

#endif
