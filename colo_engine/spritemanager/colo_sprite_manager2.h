#ifndef COLO_GAME_SPRITEMANAGER2_H
#define COLO_GAME_SPRITEMANAGER2_H

#include "../../colo_engine/shaders/colo_uber_Shader.h"
#include "../../colo_engine/math/gosha_math2.h"


class SpriteManager2
{
	public:
	SpriteManager2(Shader *pShader, GLuint gl_uintSpriteManager_texture, int width, int height);
	~SpriteManager2();
	

 
	Shader *ourShader;
	// temp
	 GLuint VBO;
	 #ifndef OPENGLES2
	 // OpenGLES 2.0 will use only 1 VAO and doesn't need this to be set
	 GLuint VAO;          
	 #endif
	 GLuint EBO;
	// temp

//final	
 GLuint spritesVAO;
 GLuint spritesVBO[6];
 GLuint spritesSHADER;
 GLuint SpriteManager_texture = 0;
 //final	
 
 // pixel particles;
 void AddSand();
 
    void     AddTriangle();
    void     AddTriangleEquilateral();
    void     AddQuad();
    void     AddRhombus();
    void     AddCube();
    void     AddCircle();
	void	 AddSphere();
	void	 AddHexagon();
    void     AddCone();
    void     AddPiramid();
 
 
 
 void InitStuff();
 
 
 int InitUniformsStuff();
 
 void SetupInitUniformsStuff();
 void SetupUniformsStuff();
 
 void DrawStuff();
 
 void DeleteStuff();
 
 
 int g_iWidth ; 
 int g_iHeight;
 int iIsFullScreen;
 void UpdateDeminsions(int width, int height);
 
 
};

#endif
