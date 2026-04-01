
#ifndef colo_quad_shader_manager_renderer_hpp
#define colo_quad_shader_manager_renderer_hpp

#include <string>


#include "../common.hpp"
#include "asset_shader_loader.h"

class ColoQuadShaderManager
{
	public:
	ColoQuadShaderManager(AAssetManager* assetMgr);
	~ColoQuadShaderManager();
	
	AAssetManager* m_assetMgr = NULL;

	GLuint compile_shader(const char *source, GLenum type) ;
//	void init_shaders(EsContext *state);
	void init_shaders();
	// Hot Reloader
	//void load_or_reload_shaders(EsContext *state);  // Helper to safely reload without leaking memory
void load_or_reload_shaders(); 
	GLuint program;
	GLuint shaderid = 1; // Very Simple easy shader from asset file or raw embeded code
	
	
	// shader locations:
	
	GLuint uniform_uProjection = 0;
	GLuint attr_inPosition = 0;
	GLuint attr_inUV = 0;
	
	bool bShaderCompiled = false;

	GLuint GetShaderID() { return 	program; }
void Cleanup();

};


#endif