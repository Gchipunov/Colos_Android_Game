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
#include "ui_scene.hpp"



// transition duration
#define TRANSITION_DURATION 0.3f


UiScene::UiScene() {
 // mWidgetCount = 0;
 // memset(mWidgets, 0, sizeof(mWidgets));
 // mFocusWidget = -1;
 // mTrivialShader = NULL;
 // mTextRenderer = NULL;
 // mShapeRenderer = NULL;
// mDefaultButton = -1;
 // mPointerDown = false;
  mWaitScreen = false;
 mTransitionStart = 0.0f;
}

UiScene::~UiScene() {
  // note: cleanup for graphics-related stuff goes in OnKillGraphics

  //int i;
 // for (i = 0; i < mWidgetCount; ++i) {
  //  CleanUp(&mWidgets[i]);
 // }
 // mWidgetCount = 0;
}


void UiScene::OnStartGraphics() {
  //mTrivialShader = new TrivialShader();
  //mTrivialShader->Compile();
 //mTextRenderer = new TextRenderer(mTrivialShader);
//  mShapeRenderer = new ShapeRenderer(mTrivialShader);

 // for (int i = 0; i < mWidgetCount; ++i) {
 //   mWidgets[i]->StartGraphics();
 // }
  mTransitionStart = Clock();

// Initialize Camera: Position at origin, looking down -Z
    mCamera = PerspectiveCamera({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, -90.0f, 0.0f);
	
	// Pull saved state from the engine singleton
    ColoEngine* engine = ColoEngine::GetInstance();
    ColoEngineSavedState* saved = engine->GetState(); 

    // 3. Check the initialization flag we added to the struct
    if (saved != nullptr && saved->isInitialized) { 
        mCamera.Position.x = saved->camX;
        mCamera.Position.y = saved->camY;
        mCamera.Position.z = saved->camZ;
        mCamera.Yaw        = saved->camYaw;
        mCamera.Pitch      = saved->camPitch;
        LOGD("Camera Restored: Yaw %.2f, Pitch %.2f", mCamera.Yaw, mCamera.Pitch);
    }
	
    mCamera.UpdateVectors();
	
 // if (mWidgetCount <= 0) {
    // time to create our widgets
 //   OnCreateWidgets();
//  }

// 1. Get the Asset Manager (Common in NDK samples)
    SceneManager *mgr = SceneManager::GetInstance();
    AAssetManager* assetMgr = mgr->GetAssetManager(); 

    // 2. Load the shader code or text
   // ColoShaderLoader loader;
 //   std::string vertexShaderSource = loader.loadTextAsset(assetMgr, "shaders/tri_vs.glsl");
   // std::string fragmentShaderSource = loader.loadTextAsset(assetMgr, "shaders/tri_fs.glsl");

    // 3. Pass to your Quad Renderer
   // if (!vertexShaderSource.empty() && !fragmentShaderSource.empty()) {
   //     mQuadRenderer = new ClassRendererQuad();
   //     mQuadRenderer->InitShaders(vertexShaderSource, fragmentShaderSource);
   //     mQuadRenderer->OnStartGraphics();
   // }
	
	
	// 1. Initialize the Shader Manager
    mShaderMgr = new ColoQuadShaderManager(assetMgr);
    mShaderMgr->init_shaders(); // This calls your code that loads files or fallback string

    // 2. Initialize the Renderer with the Shader Manager
   // mQuadRenderer = new ClassRendererQuad(mShaderMgr);
   // mQuadRenderer->OnStartGraphics();
	
	   Quad1 = new ClassRendererQuad(mShaderMgr);
	    float qSize = 0.2f; // Make them 20% of the screen height

    // Top Left: x=-0.5, y=0.5. 
    // Remember, the quad grows UP and RIGHT from its origin.
    Quad1->SetPosition(-0.3f,  0.1f);
	Quad1->SetDimensions(	qSize, qSize); 
	
    Quad1->OnStartGraphics();
	
	

	   Quad2 = new ClassRendererQuad(mShaderMgr);
	   Quad2->SetPosition(-0.075f,  0.1f);
	   Quad2->SetDimensions(	qSize, qSize); 
	   Quad2->OnStartGraphics();
	
	   Quad3 = new ClassRendererQuad(mShaderMgr);
	   Quad3->SetPosition( -0.3f, -0.3f);
	   Quad3->SetDimensions(	qSize, qSize);
       Quad3->OnStartGraphics();
	
	   Quad4 = new ClassRendererQuad(mShaderMgr);
	    Quad4->SetPosition( -0.075f, -0.3f);
	   Quad4->SetDimensions(	qSize, qSize);
    Quad4->OnStartGraphics();
    LOGD("UiScene::OnStartGraphics() %x %x %x %x",Quad1,Quad2,Quad3,Quad4);
}

void UiScene::OnKillGraphics() {
  

  // remove all widgets
  //DeleteWidgets();
}

void UiScene::OnScreenResized(int width, int height) {
  // screen got resized; if we have widgets and graphics, we have to recreate
  // them
  //SceneManager *mgr = SceneManager::GetInstance();
  //if (mgr->HasGraphics() && mWidgetCount > 0) {
   // DeleteWidgets();
  //  OnCreateWidgets();
  //}
}



void UiScene::DoFrame() {
//   LOGD(" void UiScene::DoFrame()  ");
  SceneManager *mgr = SceneManager::GetInstance();

glDisable(GL_CULL_FACE);

  // clear screen
  glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);

  // render background
 // RenderBackground();
 // Render(); // LOL Acutally Calls WelcomeScene::Render();
 UiScene::Render();
 
  // if we're in wait screen mode, render the "Please Wait" sign and do nothing
  // else
 // if (mWaitScreen) {
  //  mTextRenderer->SetFontScale(WAIT_SIGN_SCALE);
  //  mTextRenderer->SetColor(1.0f, 1.0f, 1.0f);
  //  mTextRenderer->RenderText(S_PLEASE_WAIT, mgr->GetScreenAspect() * 0.5f,
       //                       0.5f);
  //  glEnable(GL_DEPTH_TEST);
  //  return;
  //}

  // if the currently focused widget is not a clickable button, get out of focus
  // mode
  //if (mFocusWidget >= 0 && !mWidgets[mFocusWidget]->IsClickableButton()) {
  //  mFocusWidget = -1;
  //}

  // calculate transition factor, which is 0 when we're starting the transition
  // and 1 when we've finished the transition
  float tf =
      Clamp((Clock() - mTransitionStart) / TRANSITION_DURATION, 0.0f, 1.0f);

  // render ALL the widgets!
  //int i;
 // for (i = 0; i < mWidgetCount; ++i) {
 //   mWidgets[i]->Render(mTrivialShader, mTextRenderer, mShapeRenderer,
  //                      (mFocusWidget < 0)    ? UiWidget::FOCUS_NOT_APPLICABLE
  //                      : (mFocusWidget == i) ? UiWidget::FOCUS_YES
   //                                           : UiWidget::FOCUS_NO,
   //                     tf);
  //}

  glEnable(GL_DEPTH_TEST);
}
/*
void UiScene::Render() {
  // base classes override this to draw background
 // Try positioning them manually to see if they appear in different corners
  // Assuming your Quad class has a SetPosition or similar method:
  Quad1->SetPosition(-0.5f,  0.5f); // Top Left
  Quad2->SetPosition( 0.5f,  0.5f); // Top Right
  Quad3->SetPosition(-0.5f, -0.5f); // Bottom Left
  Quad4->SetPosition( 0.5f, -0.5f); // Bottom Right

  Quad1->DoFrame();
  Quad2->DoFrame();
  Quad3->DoFrame();
  Quad4->DoFrame();
  
}
*/

void UiScene::Render() {
	
	// 1. Get the current View Matrix from the camera
    float viewMatrix[16];
    mCamera.GetViewMatrix(viewMatrix);
	
    float qSize = 0.2f; // Make them 20% of the screen height

    // Top Left: x=-0.5, y=0.5. 
    // Remember, the quad grows UP and RIGHT from its origin.
    //Quad1->RenderQuad(-0.8f,  0.6f, qSize, qSize); 

    // Top Right
   // Quad2->RenderQuad( 0.4f,  0.6f, qSize, qSize); 

    // Bottom Left
    //Quad3->RenderQuad(-0.8f, -0.8f, qSize, qSize); 

    // Bottom Right
  //  Quad4->RenderQuad( 0.4f, -0.8f, qSize, qSize); 
  // Top Left
    Quad1->RenderQuad2(-0.8f,  0.6f, qSize, qSize, viewMatrix); 

    // Top Right
    Quad2->RenderQuad2( 0.4f,  0.6f, qSize, qSize, viewMatrix); 

    // Bottom Left
    Quad3->RenderQuad2(-0.8f, -0.8f, qSize, qSize, viewMatrix); 

    // Bottom Right
    Quad4->RenderQuad2( 0.4f, -0.8f, qSize, qSize, viewMatrix);
	
}


// void UiScene::OnCreateWidgets() {}

void UiScene::OnCreateQuads() {
	
	
	
}



// Add these to ui_scene.cpp if they are declared in ui_scene.hpp

void UiScene::OnInstall() {
    // Default implementation
}

void UiScene::OnUninstall() {
    // Default implementation
}

void UiScene::OnPointerDown(int pointerId, const struct PointerCoords *coords) {
    // Default implementation
}

void UiScene::OnPointerUp(int pointerId, const struct PointerCoords *coords) {
    // Default implementation
}

//void UiScene::OnPointerMove(int pointerId, const struct PointerCoords *coords) {
    // Default implementation
//}


// void LevelScene::OnPointerMove(int pointerId, float x, float y, float dx, float dy) {
	void UiScene::OnPointerMove(int pointerId, float x, float y, float dx, float dy) {
    // Sensitivity factor: lower = more precise, higher = faster
    const float sensitivity = 0.15f; 

    // dx moves the camera left/right (Yaw)
    // dy moves the camera up/down (Pitch)
    mCamera.Yaw   += dx * sensitivity;
    mCamera.Pitch -= dy * sensitivity; // Inverted usually feels more natural for touch

    // Constrain Pitch so the camera doesn't flip upside down
    if (mCamera.Pitch > 89.0f)  mCamera.Pitch = 89.0f;
    if (mCamera.Pitch < -89.0f) mCamera.Pitch = -89.0f;

    // After updating angles, you must rebuild the View Matrix 
    // using your sin/cos logic to find the new "LookAt" vector.
    mCamera.UpdateVectors(); 
}

bool UiScene::OnBackKeyPressed() {
    return false;
}

void UiScene::OnKeyDown(int ourKeyCode) {}
void UiScene::OnKeyUp(int ourKeyCode) {}
void UiScene::OnJoy(float joyX, float joyY) {}
void UiScene::OnPause() {}
void UiScene::OnResume() {}


void UiScene::OnButtonClicked(int buttonId) {
    // Default implementation (can be empty)
}
