

#ifndef colo_quad_renderer_hpp
#define colo_quad_renderer_hpp

#include "quad_shader.h"
#include "../AndroidOut.h"
#include "../scene_manager.hpp"

class ClassRendererQuad
{
	public:
	
	//ClassRendererQuad();
	ClassRendererQuad(ColoQuadShaderManager *shader);
	~ClassRendererQuad();
	
	ColoQuadShaderManager *mShader = NULL;
	
	
  virtual void OnStartGraphics();
  virtual void OnKillGraphics();
  virtual void DoFrame();
  //virtual void OnPointerDown(int pointerId, const struct PointerCoords* coords);
 // virtual void OnPointerMove(int pointerId, const struct PointerCoords* coords);
 // virtual void OnPointerUp(int pointerId, const struct PointerCoords* coords);
 //virtual void OnKeyDown(int ourKeyCode);
  virtual void OnScreenResized(int width, int height);
  
	void RenderQuad(float x, float y, float width, float height) ;  // Test, Depciate;
	void RenderQuad2(float x, float y, float w, float h, float* viewMatrix);
	
	float x = 0.25;
	float y = 0.25;
	float width = 0.25;
	float height = 0.25;
	
	void SetPosition(float newX, float newY) {
        x = newX;
        y = newY;
    }
	void SetDimensions(float newX, float newY) {
        width = newX;
        height = newY;
    }
	
	
	// New Buffer Handles, refactor to be vectors for single pass draw call
    GLuint mVBO = 0;
    GLuint mEBO = 0;
    GLuint mVAO = 0;
	
};



#endif