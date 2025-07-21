#ifndef COLO_GAME_LOADTEXTURE_H
#define COLO_GAME_LOADTEXTURE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h> // for cursor
#include <cstring> // for memset

#include "../../stb/stb_image.h"  // for load png

GLuint loadTexture(const char* path);

GLFWcursor* LoadCursor(GLFWwindow* window);
GLFWcursor* CreateCursor(GLFWwindow* window);


#endif
