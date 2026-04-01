/*
 * Copyright (C) Intmain in.
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
#ifndef colo_ui_scene_hpp
#define colo_ui_scene_hpp


#include "engine.hpp"
//#include "shape_renderer.hpp"
#include "colo_context\quad_renderer.h"
#include "util.hpp"

#include "colo_engine3\perpective_camera\perpective_camera.h"
/* UI scene. This is a base class for all scenes that present menus, etc. */
class UiScene : public Scene {
 protected:
  // the widgets we currently have

  //UiQuads * mQuads[64];
  ClassRendererQuad *Quad1 = NULL;
  ClassRendererQuad *Quad2 = NULL;
  ClassRendererQuad *Quad3 = NULL;
  ClassRendererQuad *Quad4 = NULL;
  ColoQuadShaderManager *mShaderMgr = NULL;
  
  
  // is a touch pointer (a.k.a. finger) down at the moment?
  bool mPointerDown;

  // what is the default button? The default widget is the one that we assume
  // was clicked if the user presses ENTER on the DPAD when not in focus mode.
  
  // renderers and shaders we need
  //TrivialShader* mTrivialShader;
  //MainShader *mMainShader;
  

  //ShapeRenderer* mShapeRenderer;

  // if true, shows a "please wait" screen instead of the interface
  bool mWaitScreen;

  // must be implemented by subclass
  virtual void OnButtonClicked(int buttonId);
  //virtual void RenderBackground();
virtual void Render();

  // transition start time
  float mTransitionStart;

  // add a new widget
 // UiWidget* NewWidget();

  // set default button -- the button that is assumed to be clicked when the
  // user presses the the "confirm" button (usually DPAD_CENTER or the ENTER key
  // on a keyboard).
 // void SetDefaultButton(int id) { mDefaultButton = id; }

  void SetWaitScreen(bool b) {
    mWaitScreen = b;
    if (mWaitScreen) {
      mTransitionStart = Clock();
    }
  }

  // add a navigation rule
  //void AddNav(int fromWidgetId, int dir, int toWidgetId);

  // subclasses must override these to create their widgets
  //virtual void OnCreateWidgets();

virtual void OnCreateQuads();

 public:
  UiScene();
  virtual ~UiScene();

  virtual void OnStartGraphics();
  virtual void OnKillGraphics();
  virtual void DoFrame();
  //virtual void OnPointerDown(int pointerId, const struct PointerCoords* coords);
 // virtual void OnPointerMove(int pointerId, const struct PointerCoords* coords);
 // virtual void OnPointerUp(int pointerId, const struct PointerCoords* coords);
 //virtual void OnKeyDown(int ourKeyCode);
  virtual void OnScreenResized(int width, int height);

 // UiWidget* GetWidgetById(int id);

 private:
  //void UpdateTouchFocus(const struct PointerCoords* coords);
  //void DispatchButtonClick(int id);
 // int FindDefaultButton();

  //void DeleteWidgets() { mWidgetCount = 0; }

    virtual void OnInstall();
    // Called when this scene is about to be uninstalled as the active scene.
    virtual void OnUninstall();

    // Called when a pointer goes down (e.g. touch, touchpad, etc)
    virtual void OnPointerDown(int pointerId, const struct PointerCoords *coords);

    // Called when a pointer goes up (e.g. touch, touchpad, etc)
    virtual void OnPointerUp(int pointerId, const struct PointerCoords *coords);

    // Called when a pointer moves (e.g. touch, touchpad, etc)
 //   virtual void OnPointerMove(int pointerId, const struct PointerCoords *coords);
virtual void OnPointerMove(int pointerId, float x, float y, float dx, float dy) ;

    // Called when the device's back key is pressed
    virtual bool OnBackKeyPressed();

    // Called when a key goes down
    virtual void OnKeyDown(int ourKeyCode);

    // Called when a key goes up
    virtual void OnKeyUp(int ourKeyCode);

    // Called when there is joystick input. joyX and joyY are in the range
    // [-1.0,1.0].
    virtual void OnJoy(float joyX, float joyY);

    // Called when screen gets resized
    //virtual void OnScreenResized(int width, int height);

    // Called when game is paused (e.g. onPause())
    virtual void OnPause();

    // Called when game is resumed (e.g. onResumed())
    virtual void OnResume();

PerspectiveCamera mCamera;
// Inside ui_scene.hpp
 public:
PerspectiveCamera* GetCamera() { return &mCamera; }

};



#endif
