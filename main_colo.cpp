#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "colo_engine/loadtexture/loadtexture.h"
#include "colo_engine/spritemanager/colo_sprite_manager2.h"


// The GLM library is a good practice for matrix math.
// You will need to install it separately.
// For this example, we'll use a simple 4x4 matrix for demonstration.
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//compile command:
// g++ main_colo.cpp colo_engine/shaders/colo_uber_Shader.cpp colo_engine/loadtexture/loadtexture.cpp colo_engine/math/triangle_rotate.cpp colo_engine/loadtexture/stb_image_impl.cpp  colo_engine/spritemanager/colo_sprite_manager2.cpp -o main_colo -I"C:/android_pc_game/scenecode" -I"D:/glfw-3.4-cmake/build-glfw3-static-install/include/" -I"D:/games_src/example_test_coded_by_AI/freetype/include/freetype2" -L"D:/glfw-3.4-cmake/build-glfw3-static-install/lib" -L"C:/mingw64/x86_64-w64-mingw32/lib" -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lopengl32 -lglu32 -lglew32 -lglfw3 -lgdi32 -lfreetype -lws2_32


// Settings
//const GLuint WIDTH = 800, HEIGHT = 600;
int g_iWidth = 1024;
int g_iHeight = 768;
GLFWcursor* cursor = NULL;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

SpriteManager2 *pSpriteManager2 = NULL;



int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 //   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(g_iWidth, g_iHeight, "Colo Game", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    cursor = CreateCursor(window);

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);



    // Set up OpenGL options
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Build and compile our shader program
    Shader ourShader("sprite.vs", "sprite.fs");
	
	 GLuint texture = loadTexture("assets/texture_map.png");
	 
	SpriteManager2 spitemanager(&ourShader, texture, width, height );
pSpriteManager2 = &spitemanager;



	
	ourShader.InitShader();

	spitemanager.InitStuff();
  
    // Load and create a texture
   

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

// pPlayer->HandleInputs();

/*
        // Handle sprite movement
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            spritePosition.x += 0.005f;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            spritePosition.x -= 0.005f;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            spritePosition.y += 0.005f;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            spritePosition.y -= 0.005f;
*/
       
		spitemanager.DrawStuff();

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.

	spitemanager.DeleteStuff();
	
	glfwDestroyCursor(cursor);
	
    glfwTerminate();
    
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	
	g_iWidth = width;
	g_iHeight = height;
 
    glViewport(0, 0, width, height);
	
	if(pSpriteManager2)
	{
		pSpriteManager2->UpdateDeminsions(width, height);
		
	}
}
