// CPP program to render a triangle using Shaders
//trianglegame8.cpp
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <iostream>
#include <string>

#include "movement/movement.h"
#include "grid_quad_generator.h"



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
/*
#include <vector>
#include <C:/mingw64/include/glm/glm.hpp>
#include <C:/mingw64/include/glm/gtc/matrix_transform.hpp>
*/


// Example usage:
//int main() {
    // Rotate the quad by 45 degrees (in radians)
   // rotateQuad(vertices, glm::radians(45.0f)); 

    // Now the vertices vector contains the rotated coordinates of the quad

 //   return 0;
//}


//line 805 addinng animation and custom shader fuctions for quad

// v3 - to compile your code with GCC in terminal you should define libhid for GCC by adding "-lhid" to your command : gcc test_libhid.c -lhid


using namespace std;

//main author = Georgiy Chipunov
//
//@MISC{coumans2021,
//lib bullet3 author =   {Erwin Coumans and Yunfei Bai},
//title =    {PyBullet, a Python module for physics simulation for games, robotics and machine learning},
//howpublished = {\url{http://pybullet.org}},
//year = {2016--2021}
//}
//

// *************************************************************

//             Defines

// *************************************************************
GLuint elapsedTimeUniform=0;
GLuint programId = 0;
GLuint vboId;
GLuint vboIdMain;
//GLuint programId
	GLuint m_texture = 0;
// *************************************************************

//             Logging

// *************************************************************
enum TextColor
{  
  TEXT_COLOR_BLACK,
  TEXT_COLOR_RED,
  TEXT_COLOR_GREEN,
  TEXT_COLOR_YELLOW,
  TEXT_COLOR_BLUE,
  TEXT_COLOR_MAGENTA,
  TEXT_COLOR_CYAN,
  TEXT_COLOR_WHITE,
  TEXT_COLOR_BRIGHT_BLACK,
  TEXT_COLOR_BRIGHT_RED,
  TEXT_COLOR_BRIGHT_GREEN,
  TEXT_COLOR_BRIGHT_YELLOW,
  TEXT_COLOR_BRIGHT_BLUE,
  TEXT_COLOR_BRIGHT_MAGENTA,
  TEXT_COLOR_BRIGHT_CYAN,
  TEXT_COLOR_BRIGHT_WHITE,
  TEXT_COLOR_COUNT
};

template <typename ...Args>
void _log(char* prefix, char* msg, TextColor textColor, Args... args)
{
  static char* TextColorTable[TEXT_COLOR_COUNT] = 
  {    
    "\x1b[30m", // TEXT_COLOR_BLACK
    "\x1b[31m", // TEXT_COLOR_RED
    "\x1b[32m", // TEXT_COLOR_GREEN
    "\x1b[33m", // TEXT_COLOR_YELLOW
    "\x1b[34m", // TEXT_COLOR_BLUE
    "\x1b[35m", // TEXT_COLOR_MAGENTA
    "\x1b[36m", // TEXT_COLOR_CYAN
    "\x1b[37m", // TEXT_COLOR_WHITE
    "\x1b[90m", // TEXT_COLOR_BRIGHT_BLACK
    "\x1b[91m", // TEXT_COLOR_BRIGHT_RED
    "\x1b[92m", // TEXT_COLOR_BRIGHT_GREEN
    "\x1b[93m", // TEXT_COLOR_BRIGHT_YELLOW
    "\x1b[94m", // TEXT_COLOR_BRIGHT_BLUE
    "\x1b[95m", // TEXT_COLOR_BRIGHT_MAGENTA
    "\x1b[96m", // TEXT_COLOR_BRIGHT_CYAN
    "\x1b[97m", // TEXT_COLOR_BRIGHT_WHITE
  };

  char formatBuffer[8192] = {};
  sprintf(formatBuffer, "%s %s %s \033[0m", TextColorTable[textColor], prefix, msg);

  char textBuffer[8912] = {};
  sprintf(textBuffer, formatBuffer, args...);

  puts(textBuffer);
}

#define SM_TRACE(msg, ...) _log("TRACE: ", msg, TEXT_COLOR_GREEN, ##__VA_ARGS__);
#define SM_WARN(msg, ...) _log("WARN: ", msg, TEXT_COLOR_YELLOW, ##__VA_ARGS__);
#define SM_ERROR(msg, ...) _log("ERROR: ", msg, TEXT_COLOR_RED, ##__VA_ARGS__);

#define SM_ASSERT(x, msg, ...)    \
{                                 \
  if(!(x))                        \
  {                               \
    SM_ERROR(msg, ##__VA_ARGS__); \
    DEBUG_BREAK();                \
    SM_ERROR("Assertion HIT!")    \
  }                               \
}


string vertexShader = R"(
    #version 430
    in vec3 pos;
    void main()
    {
        gl_Position = vec4(pos, 1);
    }
)";

string fragmentShader = R"(
    #version 330
    void main() 
    {
        gl_FragColor = vec4(1, 0, 1, 1); // white color
    }
)";


                                                 

string vertexShader2 = R"(
    #version 430
	uniform vec2 iResolution;
    in vec3 pos;
	in vec3 colour;
	
	
	out vec3 v_colour;
	out vec3 v_pos;
    void main()
    {
		v_colour = colour;
		
		v_pos = pos;
        gl_Position = vec4(pos, 1);
    }
)";

string fragmentShader2 = R"(
    #version 330
	
	uniform vec2 iResolution;
	
	in vec3 v_colour;
	in vec3 v_pos;
	out vec4 color;

	
    void main() 
    {
		float fResX = iResolution.x/12;
		fResX = 0.1;
		if(abs( v_pos.x )> fResX)
		{
			 fResX = iResolution.x/4;
			if(v_pos.x > 0.33)
			{
				color= vec4(0, abs(gl_FragCoord.x), 1, 1); // pinker color
			}
			else{
				
			color= vec4(1, v_pos.x, v_colour.b, 1); // alt color
			}
		}
		else
		{
        color = vec4(sin(v_colour.r), atan(v_colour.g), v_colour.b, 1); // white color
		}
    }
)";


string vertexShader3 = R"(
    #version 140
	uniform vec2 iResolution;
    in vec3 pos;
	in vec3 colour;
	
	
	out vec3 v_colour;
	out vec3 v_pos;
    void main()
    {
		v_colour = colour;
		
		v_pos = pos;
        gl_Position = vec4(pos, 1);
    }
)";

string fragmentShader3 = R"(
    #version 140
	
	uniform vec2 iResolution;
	
	in vec3 v_colour;
	in vec3 v_pos;
	out vec4 color;

	
    void main() 
    {
		float fResX = iResolution.x/12;
		fResX = 0.1;
		if(abs( v_pos.x )> fResX)
		{
			 fResX = iResolution.x/4;
			if(v_pos.x > 0.33)
			{
				color= vec4(0, abs(gl_FragCoord.x), 1, 1); // pinker color
			}
			else{
				
			color= vec4(1, v_pos.x, v_colour.b, 1); // alt color
			}
		}
		else
		{
        color = vec4(sin(v_colour.r), atan(v_colour.g), v_colour.b, 1); // white color
		}
    }
)";


string fragmentShader55 = R"(
    #version 140
	
	uniform vec2 iResolution;
	
	in vec3 v_colour;
	in vec3 v_pos;
	out vec4 color;

	
    void main() 
    {
		    float lerpValue = gl_FragCoord.y / 500.0f;

		
		
        color = vec4(v_colour.r, v_colour.g, v_colour.b, 1); // white color
		
    }
)";




string vertexShaderCool = R"(
    #version 140
	
	uniform float loopDuration;
uniform float time;
	uniform vec2 iResolution;
	
	
    in vec3 pos;
	in vec4 colour;
	
	
	out vec4 v_colour;
	out vec3 v_pos;
    void main()
    {
		v_colour = colour;
		
		v_pos = pos;
        gl_Position = vec4(pos, 1);
    }
)";

string fragmentShaderCool = R"(
    #version 140
	
	uniform float fragLoopDuration;
uniform float time;

	uniform vec2 iResolution;
	
	
	
	in vec4 v_colour;
	in vec3 v_pos;
	out vec4 color;

	
    

	const vec4 firstColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 secondColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
const float  minX = -2.5;
const float minY = -2.0;
const float maxX =  1.5;
const float maxY =  2.0 ;
    void main() 
    {
		float x = gl_FragCoord.x;
        float y = gl_FragCoord.y;

        vec2 c = vec2((x* (maxX-minX) / iResolution.x + minX), (y*(maxY-minY)/ iResolution.y + minY));
        vec2 z = c;

		
		    float lerpValue = gl_FragCoord.y / 500.0f;

		 float currTime = mod(time, fragLoopDuration);
    float currLerp = currTime / fragLoopDuration;
		
		vec4 thridColor = vec4(z.x, z.y, v_colour.b, 1.0f);
		
        color = vec4(v_colour.r, v_colour.g, v_colour.b, 1); // white color
		    color = mix(thridColor, secondColor, currLerp);

    
    }
)";



string vertexShaderCool2 = R"(
    #version 140
	
	uniform float loopDuration;
uniform float time;
	uniform vec2 iResolution;
	
	
    in vec3 pos;
	in vec4 colour;
	in vec2 aTexCoord;
	in float animationState;
	in float animationFrame;
	in float shaderType;
	
	
	out vec4 v_colour;		
	out vec3 v_pos;
	out vec2 TexCoord;
    out float v_animationState;
	out float v_animationFrame;
	out float v_shaderType;
	
   

    void main()
    {
		v_colour = colour;
		
		v_pos = pos;
		
			v_animationState = animationState;
	v_animationFrame = animationFrame;
	v_shaderType = shaderType;
		
		 TexCoord = aTexCoord;
        gl_Position = vec4(pos, 1);
    }
)";

string fragmentShaderCool2 = R"(
    #version 140
	
	uniform float fragLoopDuration;
uniform float time;

	uniform vec2 iResolution;
	
	uniform sampler2D ourTexture;

	
	in vec4 v_colour;
	in vec3 v_pos;
	in vec2 TexCoord;
    in float v_animationState;
	in float v_animationFrame;
	in float v_shaderType;

	out vec4 color;

	
    

	const vec4 firstColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 secondColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
const float  minX = -2.5;
const float minY = -2.0;
const float maxX =  1.5;
const float maxY =  2.0 ;
    void main() 
    {
		float x = gl_FragCoord.x;
        float y = gl_FragCoord.y;

        vec2 c = vec2((x* (maxX-minX) / iResolution.x + minX), (y*(maxY-minY)/ iResolution.y + minY));
        vec2 z = c;

		
		    float lerpValue = gl_FragCoord.y / 500.0f;

		 float currTime = mod(time, fragLoopDuration);
    float currLerp = currTime / fragLoopDuration;
		
		vec4 thridColor = vec4(z.x, z.y, v_colour.b, 1.0f);
		
        color = vec4(v_colour.r, v_colour.g, v_colour.b, 1); // white color
		    color = mix(thridColor, secondColor, currLerp);
			
			
			vec2 TexCoord2 = TexCoord;
	
color = texture(ourTexture, TexCoord2) * vec4(color);  


    
    }
)";

// Compile and create shader object and returns its id
GLuint compileShaders(string shader, GLenum type)
{

    const char *shaderCode = shader.c_str();
    GLuint shaderId = glCreateShader(type);

    if (shaderId == 0)
    { // Error: Cannot create shader object
        cout << "Error creating shaders!";
        return 0;
    }

    // Attach source code to this object
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId); // compile the shader object

    GLint compileStatus;

    // check for compilation status
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);

    if (!compileStatus)
    { // If compilation was not successfull
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
        char *cMessage = new char[length];

        // Get additional information
        glGetShaderInfoLog(shaderId, length, &length, cMessage);
        cout << "Cannot Compile Shader: " << cMessage;
        delete[] cMessage;
        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}

// Creates a program containing vertex and fragment shader
// links it and returns its ID
GLuint linkProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
{
     programId = glCreateProgram(); // crate a program

    if (programId == 0)
    {
        cout << "Error Creating Shader Program";
        return 0;
    }

    // Attach both the shaders to it
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
glBindAttribLocation(programId, 0, "pos");
glBindAttribLocation(programId, 1, "colour");
glBindAttribLocation(programId, 2, "aTexCoord");

glBindAttribLocation(programId, 3, "animationState");
glBindAttribLocation(programId, 4, "animationFrame");
glBindAttribLocation(programId, 5, "shaderType");

	
    // Create executable of this program
    glLinkProgram(programId);

    GLint linkStatus;

    // Get the link status for this program
    glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);

    if (!linkStatus)
    { // If the linking failed
        cout << "Error Linking program";
        glDetachShader(programId, vertexShaderId);
        glDetachShader(programId, fragmentShaderId);
        glDeleteProgram(programId);

        return 0;
    }

    return programId;
}
 
GLuint loadDataInBufferscolors()
{
   GLfloat verticescolors[] = {// triangle vertex coordinates
                          1.0, 1.0, 0, 1,
                          0.5, 0.25, 0, 1,
                          0.25, 0.5, 0, 1,
0.95, 0.15, 0, 1,
                          0.5, 0.15, 0, 1,
                          0.15, 0.5, 0, 1

};

  

    GLuint vboId;

    // allocate buffer sapce and pass data to it
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticescolors), verticescolors, GL_STATIC_DRAW);

    // unbind the active buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vboId;
}
GLuint loadDataInBufferstexCoords()
{
float texCoords2[] = {
    0.0f, 0.0f,  // lower-left corner  
    0.0f, 0.015625,  // lower-right corner
    0.015625, 0.015625,   // top-center corner
	
	 0.015625, 0.015625,  // lower-left corner  
    0.015625 , 0.0f ,   // lower-right corner
   0.0f, 0.0f   // top-center corner
};

float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    0.0f, 10.015625,  // lower-right corner
    10.015625, 10.015625,   // top-center corner
	
	 0.015625, 10.015625,  // lower-left corner  
    10.015625 , 0.5f ,   // lower-right corner
   0.0f, 0.0f   // top-center corner
};
   GLuint vboId;

    // allocate buffer sapce and pass data to it
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

    // unbind the active buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vboId;
}

// GLOBAL Sprites Controller
	/*
	// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};
[0] 3          0 [3]
 +-----+  +
 |   /  / |
 | /  /   |
 +  +-----+
[1] 2          1 [2]
	*/
	#define PLAYER1STARTX 0.0078125f
	#define PLAYER1STARTY -0.125f
	
	#define PLAYER1ENDX 0.125f
	#define PLAYER1ENDY 0.0f
	
	

	//   -0.9f, -0.9f
	//   0.9f, 0.9f
	#define LEVEL1STARTX 0.5f
	#define LEVEL1STARTY 0.0f
	
	#define LEVEL1ENDX 1.0f
	#define LEVEL1ENDY 0.5f


//ENEMY
//
#define ENEMY1STARTX 0.3848125f
	#define ENEMY1ENDX 0.480f
	
	#define ENEMY1STARTY 0.90f
	#define ENEMY1ENDY  1.0f
GLfloat vertices[] =
{

   // LEVEL
	  
	  -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY,  0.0f, 0.0f, 1.0f, //0 Lower left corner
	 0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner
	 -0.9f,  0.9f, 0.0f,     0.0f, 1.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //1 Upper left corner
	 
	 -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f, //0 Lower left corner
	 0.9f, -0.9f, 0.0f,     1.0f, 1.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f,  //3 Lower right corner
	  0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner

      // PLAYER
	//     COORDINATES     /        COLORS,ALPHA      /   TexCoord  //
	-0.15f, -0.15f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1STARTY,0.0f, 0.0f,0.0f, //0 Lower left corner
	 0.15f,  0.15f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1ENDY,0.0f, 0.0f,0.0f, //2 Upper right corner
	 -0.15f,  0.15f, 0.0f,     0.0f, 1.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1ENDY, 0.0f, 0.0f,0.0f,//1 Upper left corner
	 
	 -0.15f, -0.15f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1STARTY, 0.0f, 0.0f,0.0f,//0 Lower left corner
	 0.15f, -0.15f, 0.0f,     1.0f, 1.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1STARTY,0.0f, 0.0f,0.0f,  //3 Lower right corner
	  0.15f,  0.15f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1ENDY, 0.0f, 0.0f,0.0f,//2 Upper right corner
	  
	  // PLAYER
	//     COORDINATES     /        COLORS,ALPHA      /   TexCoord  //
	-0.15f+0.6f, -0.15f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	ENEMY1STARTX, ENEMY1STARTY,0.0f, 0.0f,0.0f, //0 Lower left corner
	 0.15f+0.6f,  0.15f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	ENEMY1ENDX, ENEMY1ENDY,0.0f, 0.0f,0.0f, //2 Upper right corner
	 -0.15f+0.6f,  0.15f, 0.0f,     0.0f, 1.0f, 0.0f,0.0f,	ENEMY1STARTX, ENEMY1ENDY, 0.0f, 0.0f,0.0f,//1 Upper left corner
	 
	 -0.15f+0.6f, -0.15f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	ENEMY1STARTX, ENEMY1STARTY, 0.0f, 0.0f,0.0f,//0 Lower left corner
	 0.15f+0.6f, -0.15f, 0.0f,     1.0f, 1.0f, 1.0f,0.0f,	ENEMY1ENDX, ENEMY1STARTY,0.0f, 0.0f,0.0f,  //3 Lower right corner
	  0.15f+0.6f,  0.15f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	ENEMY1ENDX, ENEMY1ENDY, 0.0f, 0.0f,0.0f//2 Upper right corner
	  
	
	  
};
// Load data in VBO (Vertex Buffer Object) and return the vbo's id
GLuint loadDataInBuffers()
{
	
	/*
	GLfloat vertices[] =
{

  // LEVEL
	  
	  -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY,  0.0f, 0.0f, 1.0f, //0 Lower left corner
	 0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner
	 -0.9f,  0.9f, 0.0f,     0.0f, 1.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //1 Upper left corner
	 
	 -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f, //0 Lower left corner
	 0.9f, -0.9f, 0.0f,     1.0f, 1.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f,  //3 Lower right corner
	  0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner

      // PLAYER
	//     COORDINATES     /        COLORS,ALPHA      /   TexCoord  //
	-0.15f, -0.15f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1STARTY,0.0f, 0.0f,0.0f, //0 Lower left corner
	 0.15f,  0.15f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1ENDY,0.0f, 0.0f,0.0f, //2 Upper right corner
	 -0.15f,  0.15f, 0.0f,     0.0f, 1.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1ENDY, 0.0f, 0.0f,0.0f,//1 Upper left corner
	 
	 -0.15f, -0.15f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1STARTY, 0.0f, 0.0f,0.0f,//0 Lower left corner
	 0.15f, -0.15f, 0.0f,     1.0f, 1.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1STARTY,0.0f, 0.0f,0.0f,  //3 Lower right corner
	  0.15f,  0.15f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1ENDY, 0.0f, 0.0f,0.0f//2 Upper right corner
	  
	
	  
};

	
	// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};


// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

    GLfloat vertices[] = {// triangle vertex coordinates
                          -0.5, -0.5, 0,
                          0.5, -0.5, 0,
                          -0.5, 0.5, 0,
0.5, 0.5, 0,
                          0.5, -0.5, 0,
                          -0.5, 0.5, 0
};

 GLfloat vertices[] = {
0.250000,0.250000,-0.750000
,0.250000,-0.050000,-0.750000
,0.250000,0.250000,-0.250000
,0.250000,-0.050000,-0.250000
,-0.250000,0.250000,-0.750000
,-0.250000,-0.050000,-0.750000
,-0.250000,0.250000,-0.250000
,-0.250000,-0.050000,-0.250000
,0.087500,0.644355,-0.412500
,-0.087500,0.644355,-0.412500
,0.087500,0.644355,-0.587500
,-0.087500,0.644355,-0.587500
,0.087500,0.869355,-0.412500
,-0.087500,0.869355,-0.412500
,0.087500,0.869355,-0.587500
,-0.087500,0.869355,-0.587500
,0.087500,0.994355,-0.412500
,-0.087500,0.994355,-0.412500
,0.087500,0.994355,-0.587500
,-0.087500,0.994355,-0.587500
,-0.087500,0.869355,-0.712500
,0.087500,0.869355,-0.712500
,-0.087500,0.994355,-0.712500
,0.087500,0.994355,-0.712500
,0.087500,0.869355,-0.287500
,-0.087500,0.869355,-0.287500
,0.087500,0.994355,-0.287500
,-0.087500,0.994355,-0.287500

};


n = 0;
triangles[n++] = [values[0], values[1], values[2]];
for(i = 3; i < count(values); ++i)
  triangles[n++] = [
    values[i - 3],
    values[i - 1],
    values[i]
  ];
  */

    

    // allocate buffer sapce and pass data to it
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
   // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   // GL_STREAM_DRAW
//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

// sprite system needs append feature
    // unbind the active buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vboId;
}
// GLOBAL - vectorial physics
struct sCharacter
{
		float PlayerXPos  ; // for center position , ?convert to points?
float PlayerYPos ;

	float PlayerX  ; //  for drawing
float PlayerY ;

	float PlayerXEnd  ;
float PlayerYEnd ;

float PlayerXVel  ;  // for physics
float PlayerYVel ;

float PlayerXAcc  ; // for physics
float PlayerYAcc ;

float texCoordPLAYER1STARTX;    // for drawing texture map
float texCoordPLAYER1STARTXEND;   // for drawing texture map

float texCoordPLAYER1STARTY;    // for drawing texture map
float texCoordPLAYER1STARTYEND;   // for drawing texture map

float Health; // implement
float Icons;  // do to FIXME continued

float AngleRotation; // add matrixes for concurrent rendering
float AngleRotationVel;
float AngleRotationAcc;
float AngleRotationDefault; // gravity towards
};

//	sCharacter GBLCharacter;
	struct Global
	{
	struct sCharacter Player1;
	struct sCharacter Enemy1;
	struct sCharacter Tree;     // make end level for pooping stop level
	
	struct sCharacter *enemies;
	
	float map_xcoorOffset ;   // where we are on map in the background
	float map_ycoorOffset ;
	float map_xcoorOffset2 ;   // this texture doesn't go on and on so will have to just add props somehow
	float map_ycoorOffset2 ;
	
	};
	
	struct Global GBL;

	//   -0.9f, -0.9f  , cut off edge camera by 0.1
	//   0.9f, 0.9f
	//#define LEVEL1STARTX 0.5f
	//#define LEVEL1STARTY 0.0f
	
	//#define LEVEL1ENDX 1.0f
	//#define LEVEL1ENDY 0.5f


float g_PlayerX  = -0.30f;
float g_PlayerY  = -0.15f;

float g_EnemyY  = -0.15f;
float g_EnemyYEnd  = 0.15f;

	float GBL_character_width =  0.30f;//64;
float GBL_character_height =  0.30f; //64;

	float character_groundy = 0.0f;
	
int g_PlayerJumpKeyUp  = 0 ;
int g_PlayerJumpKeyDown  = 0 ;

int g_PlayerForwardKeyUp  = 0 ; // D
int g_PlayerForwardKeyDown  = 0 ;

int g_PlayerDownKeyUp  = 0 ; // S
int g_PlayerDownKeyDown  = 0 ;

int g_PlayerBackwardKeyUp  = 0 ;  // A  //g_PlayerForwardKeyUp, g_PlayerBackwardKeyUp,g_PlayerDownKeyUp,g_PlayerUpKeyUp
int g_PlayerBackwardKeyDown  = 0 ;

int g_PlayerUpKeyUp  = 0 ;   // W
int g_PlayerUpKeyDown  = 0 ;

//joystick controller gamepad button x
int g_PlayerFireKeyUp  = 0 ;
int g_PlayerFireKeyDown  = 0 ;
//joystick controller gamepad button y
int g_PlayerFartKeyUp  = 0 ;
int g_PlayerFartKeyDown  = 0 ;

//joystick controller gamepad button a
int g_PlayerUseKeyUp  = 0 ;
int g_PlayerUseKeyDown  = 0 ;

//joystick controller gamepad button b
int g_PlayerKickKeyUp  = 0 ;
int g_PlayerKickKeyDown  = 0 ;
// joystick controller gamepad button menu/inventory
//int g_PlayerMenuKeyUp  = 0 ;
//int g_PlayerMenuKeyDown  = 0 ;

int iCanJump = 1;

void MoveCharacterUpdateInterval(void)
{
	//g_PlayerForwardKeyUp, g_PlayerBackwardKeyUp,g_PlayerDownKeyUp,g_PlayerUpKeyUp
	
	if(g_PlayerForwardKeyDown > 0) //  d 
{
//GBL.character.x = GBL.character.x + 1;
//console.log('FORWARD d GBL.character.x = GBL.character.x + 1;');
g_PlayerX = g_PlayerX + 0.01f;
}
else if(g_PlayerBackwardKeyDown  > 0)   //  a
{
//GBL.character.x = GBL.character.x - 1;
//console.log('BACKAWRD d GBL.character.x = GBL.character.x - 1;');
g_PlayerX = g_PlayerX - 0.01f;
}

if(g_PlayerJumpKeyDown > 0 && g_PlayerJumpKeyUp == 0 && iCanJump == 1)
{ 
printf("JUMP INIT1\n");
iCanJump = 0;

// g_PlayerJumpKeyDown = 0;} // anti-key: g_PlayerJumpKeyUp
	g_PlayerY = g_PlayerY + 0.3f;
	
	
	
	//g_PlayerYEnd = g_PlayerY + 0.30f;

// character_groundy
//g_PlayerY
}
else 
{
if(g_PlayerY + 0.15f > character_groundy) // ground can be a collision pixel array
{
	g_PlayerY = g_PlayerY - 0.01f;
}
else
{
	iCanJump = 1;
}

	
}

//GBL.PlayerVELX += GBL.PlayerACCX;
//GBL.PlayerVELY += GBL.PlayerACCY;


}
/*
glm::mat4 vec2ToMat4(const glm::vec2& vec) {
    // Create an identity matrix
    glm::mat4 mat = glm::mat4(1.0f);

    // Use the vec2 components for translation
    mat = glm::translate(mat, glm::vec3(vec.x, vec.y, 0.0f)); 

    return mat;
}
glm::vec2 mat4ToVec2(const glm::mat4& mat) {
    // Extract the translation components from the matrix
    return glm::vec2(mat[3][0], mat[3][1]);
}
*/
void UpdateVertices(void)
{
	MoveCharacterUpdateInterval();
	float angle =(float)	(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;

	  //      glm::mat2 rotationMatrix = glm::rotate(glm::mat2(1.0f), angle);
	//g_PlayerForwardKeyUp, g_PlayerBackwardKeyUp,g_PlayerDownKeyUp,g_PlayerUpKeyUp
/*
//--------------------------glm
	 glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	 
	 glm::vec2 translation = glm::vec2(g_PlayerX, g_PlayerY); 
//glm::mat4 transform = vec2ToMat4(translation); 
transform = vec2ToMat4(translation); 

        transform = glm::rotate(transform, angle, glm::vec3(1.0f, 0.0f, 0.0f)); 
		//glm::vec2 translation = mat4ToVec2(transform); 
		 translation = mat4ToVec2(transform); 
g_PlayerX = translation.x;
g_PlayerY = translation.y;
*/
		
//-------------------------------end glm


//----------------------------
  // float s = sinf(mAngles[i]);
  //    float c = cosf(mAngles[i]);
  //    transforms[4 * i + 0] = c * mScale[0];
  //    transforms[4 * i + 1] = s * mScale[1];
  //    transforms[4 * i + 2] = -s * mScale[0];
  //    transforms[4 * i + 3] = c * mScale[1];

//-------------------------------
	float PlayerX = g_PlayerX; //-0.15f    0.30f x 0.30f
	float PlayerY = g_PlayerY; // -0.15f
	
	float PlayerXEnd = PlayerX + 0.30f;
	
	float PlayerYEnd = PlayerY + 0.30f;
	
	if(g_PlayerDownKeyDown ) //
	{
		PlayerYEnd = PlayerY + 0.15f; // FIXME swamp texture instead
	}
	
	
	float EnemyX=0.15f+0.6f;        //   <--- |
		float EnemyXEnd=-0.15f+0.6f;//   <--- | flip facing direction
		float EnemyY=g_EnemyY;
		float EnemyYEnd=g_EnemyYEnd;
	float LevelX;
	float LevelY;
	
GLfloat	 vertices2[] =
{

  // LEVEL
	  
	  -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY,  0.0f, 0.0f, 1.0f, //0 Lower left corner
	 0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner
	 -0.9f,  0.9f, 0.0f,     0.0f, 1.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //1 Upper left corner
	 
	 -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f, //0 Lower left corner
	 0.9f, -0.9f, 0.0f,     1.0f, 1.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f,  //3 Lower right corner
	  0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner

      // PLAYER
	//     COORDINATES     /        COLORS,ALPHA      /   TexCoord  //
	PlayerX, PlayerY, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1STARTY,0.0f, 0.0f,0.0f, //0 Lower left corner
	 PlayerXEnd,  PlayerYEnd, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1ENDY,0.0f, 0.0f,0.0f, //2 Upper right corner
	 PlayerX, PlayerYEnd, 0.0f,     0.0f, 1.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1ENDY, 0.0f, 0.0f,0.0f,//1 Upper left corner
	 
	 PlayerX, PlayerY, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1STARTY, 0.0f, 0.0f,0.0f,//0 Lower left corner
	 PlayerXEnd, PlayerY, 0.0f,     1.0f, 1.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1STARTY,0.0f, 0.0f,0.0f,  //3 Lower right corner
	  PlayerXEnd,  PlayerYEnd, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1ENDY, 0.0f, 0.0f,0.0f,//2 Upper right corner
	  
	    // ENEMY
	//     COORDINATES     /        COLORS,ALPHA      /   TexCoord  //
	EnemyX, EnemyY, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	ENEMY1STARTX, ENEMY1STARTY,0.0f, 0.0f,0.0f, //0 Lower left corner
	 EnemyXEnd,  EnemyYEnd, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	ENEMY1ENDX, ENEMY1ENDY,0.0f, 0.0f,0.0f, //2 Upper right corner
	 EnemyX, EnemyYEnd, 0.0f,     0.0f, 1.0f, 0.0f,0.0f,	ENEMY1STARTX, ENEMY1ENDY, 0.0f, 0.0f,0.0f,//1 Upper left corner
	 
	 EnemyX, EnemyY, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	ENEMY1STARTX, ENEMY1STARTY, 0.0f, 0.0f,0.0f,//0 Lower left corner
	 EnemyXEnd, EnemyY, 0.0f,     1.0f, 1.0f, 1.0f,0.0f,	ENEMY1ENDX, ENEMY1STARTY,0.0f, 0.0f,0.0f,  //3 Lower right corner
	  EnemyXEnd,  EnemyYEnd, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	ENEMY1ENDX, ENEMY1ENDY, 0.0f, 0.0f,0.0f//2 Upper right corner
	  
	
	  
};

memcpy(vertices, vertices2, sizeof(vertices2));

    glBindBuffer(GL_ARRAY_BUFFER, vboIdMain);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
//brb
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
	/*
vertices 12*6

memcpy(&fNewData[0] 12*6, vertexPositions, sizeof(vertexPositions));
	
	*/
/*  
Example 3.2. Adjusting the Vertex Data

void AdjustVertexData(float fXOffset, float fYOffset)
{
    std::vector<float> fNewData(ARRAY_COUNT(vertexPositions));
    memcpy(&fNewData[0], vertexPositions, sizeof(vertexPositions));
    
    for(int iVertex = 0; iVertex < ARRAY_COUNT(vertexPositions); iVertex += 4)
    {
        fNewData[iVertex] += fXOffset;
        fNewData[iVertex + 1] += fYOffset;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), &fNewData[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
*/



//}

 unsigned char *image;
 int w, h, comp;//original_no_channels
void loadImageMaterial()
{
	 
      int desired_no_channels = 4;
	  stbi_set_flip_vertically_on_load(true);
	  
      image = stbi_load("assets/texture_map.png", &w, &h, &comp, desired_no_channels);
      if(image == NULL) {
          printf("Error in loading the image\n");
          exit(1);
     }
     printf("Loaded image with a width of %dpx, a height of %dpx. The original image had %d channels, the loaded image has %d channels.\n", w, h, comp, desired_no_channels);
 
     // ...
}

void initGBL()
{
	
GBL.map_xcoorOffset = 0.5f;
GBL.map_xcoorOffset2 = 1.0f;

GBL.map_ycoorOffset = 0.0f;
GBL.map_ycoorOffset2 = 0.5f;

//Vector Quantities – Force, Electric field, Angular Momentum, Magnetic Moment, Linear Momentum, Average Velocity.



GBL.Player1.PlayerX =  -0.30f;
GBL.Player1.PlayerY =  -0.15f;


GBL.Player1.PlayerXVel =  0.0f;
GBL.Player1.PlayerYVel =  0.0f;

GBL.Player1.PlayerXAcc =  0.0f;
GBL.Player1.PlayerYAcc =  0.0f;





// 	float EnemyX=0.15f+0.6f;        //   <--- |
		//float EnemyXEnd=-0.15f+0.6f;//   <--- | flip facing direction
		
GBL.Enemy1.PlayerX = -0.15f+0.6f;
GBL.Enemy1.PlayerXEnd = 0.15f+0.6f;

GBL.Enemy1.PlayerXVel =  0.0f;
GBL.Enemy1.PlayerYVel =  0.0f;

GBL.Enemy1.PlayerXAcc =  0.0f;
GBL.Enemy1.PlayerYAcc =  0.0f;

}

// Initialize and put everything together
void init()
{
	initGBL();
	
	
	loadImageMaterial();
	makeQuads();
	
    // clear the framebuffer each frame with black color
    glClearColor(0, 0, 0, 0);

 
//GLuint vboId = loadDataInBuffers();

    GLuint vShaderId = compileShaders(vertexShaderCool2, GL_VERTEX_SHADER);
    GLuint fShaderId = compileShaders(fragmentShaderCool2, GL_FRAGMENT_SHADER);
	
	
	
	glGenTextures(1, &m_texture);
//int comp = 4;

glBindTexture(GL_TEXTURE_2D, m_texture);

//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

if(comp == 3)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
else if(comp == 4)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);



stbi_image_free(image);

// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, 0);

SM_TRACE((char*)vertexShader3.c_str(),TEXT_COLOR_GREEN)
SM_WARN((char*)fragmentShader3.c_str(),TEXT_COLOR_BLUE)
// insert location binding code here



     programId = linkProgram(vShaderId, fShaderId);

    // Get the 'pos' variable location inside this program
    GLuint posAttributePosition = glGetAttribLocation(programId, "pos");
 GLuint posAttributePosition2 = glGetAttribLocation(programId, "colour");
GLuint posAttributePosition3 = glGetAttribLocation(programId, "aTexCoord");

    GLuint vaoId;
    glGenVertexArrays(1, &vaoId); // Generate VAO  (Vertex Array Object)

    // Bind it so that rest of vao operations affect this vao
    glBindVertexArray(vaoId);
	
    vboIdMain = loadDataInBuffers();
	 GLuint vboId2 = loadDataInBufferscolors();
	 GLuint vboId3 =  loadDataInBufferstexCoords();
	 
    // buffer from which 'pos' will receive its data and the format of that data
    glBindBuffer(GL_ARRAY_BUFFER, vboIdMain);
  //  glVertexAttribPointer(posAttributePosition, 3, GL_FLOAT, false, 0, 0);
  // Enable this attribute array linked to 'pos'
  //  glEnableVertexAttribArray(posAttributePosition);
   


 //GLuint vaoId2;
 //  glGenVertexArrays(1, &vaoId2); // Generate VAO  (Color Array Object)

    // Bind it so that rest of vao operations affect this vao
    glBindVertexArray(vaoId);
	
	glBindBuffer(GL_ARRAY_BUFFER, vboIdMain);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  12 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);// Unbinds the VBO void VBO::Unbind()

glBindBuffer(GL_ARRAY_BUFFER, vboIdMain);
glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,  12 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER, 0);// Unbinds the VBO void VBO::Unbind()


glBindBuffer(GL_ARRAY_BUFFER, vboIdMain);
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,  12 * sizeof(float), (void*)(7 * sizeof(float)));
glEnableVertexAttribArray(2); 
glBindBuffer(GL_ARRAY_BUFFER, 0);// Unbinds the VBO void VBO::Unbind()
// animation state
glBindBuffer(GL_ARRAY_BUFFER, vboIdMain);
glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE,  12 * sizeof(float), (void*)(8 * sizeof(float)));
glEnableVertexAttribArray(3); 
glBindBuffer(GL_ARRAY_BUFFER, 0);// Unbinds the VBO void VBO::Unbind()
// animation frame
glBindBuffer(GL_ARRAY_BUFFER, vboIdMain);
glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE,  12 * sizeof(float), (void*)(9 * sizeof(float)));
glEnableVertexAttribArray(4); 
glBindBuffer(GL_ARRAY_BUFFER, 0);// Unbinds the VBO void VBO::Unbind()
//shader type
glBindBuffer(GL_ARRAY_BUFFER, vboIdMain);
glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE,  12 * sizeof(float), (void*)(10 * sizeof(float)));
glEnableVertexAttribArray(4); 
glBindBuffer(GL_ARRAY_BUFFER, 0);// Unbinds the VBO void VBO::Unbind()



/*
    // buffer from which 'colour' will receive its data and the format of that data
    glBindBuffer(GL_ARRAY_BUFFER, vboId2);
    glVertexAttribPointer(posAttributePosition2, 4, GL_FLOAT, false, 0, 0);

   // Enable this attribute array linked to 'colour'
    glEnableVertexAttribArray(posAttributePosition2);
	
	 glBindBuffer(GL_ARRAY_BUFFER, vboId3);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
glEnableVertexAttribArray(2); 

*/

    // Use this program for rendering.
    glUseProgram(programId);
	
	    elapsedTimeUniform = glGetUniformLocation(programId, "time");
    
    GLuint loopDurationUnf = glGetUniformLocation(programId, "loopDuration");
	    glUniform1f(loopDurationUnf, 5.0f);
		    GLuint fragLoopDurUnf = glGetUniformLocation(programId, "fragLoopDuration");
    glUniform1f(fragLoopDurUnf, 10.0f);

		
GLint loc = glGetUniformLocation(programId, "iResolution");
// glUniform2f(loc, width, height);
//glUniform2f(loc, 500, 500);
glUniform2f(loc, 500, 500);
  glUseProgram(0);
//brb
}
void modImage()
{
	char image2[2000];
	/*
for	(int i=64; i <512;i++)
	{
		for	(int i=64; i <512;i++)
	{
		
		
	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	 } 
}
*/
for	(int i=0; i <2000;i++)
	{
	//	for	(int i=64; i <512;i++)
	{
		image2[i]= (char) (int)(glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
		 } 
}
memcpy(image,image2,2000);
	
	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);


}

// Function that does the drawing
// glut calls this function whenever it needs to redraw
void display()
{
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(programId);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glUniform1f(elapsedTimeUniform, glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboIdMain);
    glEnableVertexAttribArray(0);
	    glEnableVertexAttribArray(1);
		    glEnableVertexAttribArray(2);
			
			glEnableVertexAttribArray(3);
			glEnableVertexAttribArray(4);
			glEnableVertexAttribArray(5);
   // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  //  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
//glEnableVertexAttribArray(2); 

//num * sprites * 6 = triangles draw
    glDrawArrays(GL_TRIANGLES, 0, 18);
//static	int counter= 0;

//counter++;
//static	float fcounter= 0;
//static	float fps= 0;

//if(fcounter > 100)
//{
   // modImage();
 //  UpdateVertices();
	//counter = 0;
//	fcounter= glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	
	
//}
    glDisableVertexAttribArray(0);
    glUseProgram(0);
    
    glutSwapBuffers();
    glutPostRedisplay();
}


//glut can also handle joysticks with the glutJoystickFunc which has the following constants: GLUT_HAS_JOYSTICK:0x0264, GLUT_OWNS_JOYSTICK:0x0265, GLUT_JOYSTICK_BUTTONS:0x0266, GLUT_JOYSTICK_AXES:0x0267, GLUT_JOYSTICK_POLL_RATE:0x0268, GLUT_JOYSTICK_BUTTON_A:0x0001, GLUT_JOYSTICK_BUTTON_B:0x0002, GLUT_JOYSTICK_BUTTON_C:0x0004, GLUT_JOYSTICK_BUTTON_D:0x0008.
//processGamepad

// 
// void glutForceJoystickFunc	
void processGamepad(unsigned int buttonMask, int xaxis, int yaxis, int zaxis) {
	
	if(buttonMask & GLUT_JOYSTICK_BUTTON_A) {
    printf("button A is pressed \n");
}
if(buttonMask & GLUT_JOYSTICK_BUTTON_B) {
    printf("button B is pressed \n");
}
if(buttonMask & GLUT_JOYSTICK_BUTTON_C) { //X
    printf("button C is pressed \n");
}
if(buttonMask & GLUT_JOYSTICK_BUTTON_D) { //Y
    printf("button D is pressed \n");
}
/// axises
if(xaxis ) {
	    printf("-------------------------------------\n");
    printf("button xaxis is pressed %d\n",xaxis);
	if(xaxis > 100)
	{
		g_PlayerX = g_PlayerX + 0.01f;
		// UpdateVertices();
	}
	if(xaxis < -100)
	{
			g_PlayerX = g_PlayerX - 0.01f;
		//	 UpdateVertices();// FIXME after remove move to physicss/gamemovement fuctions
	}
}
if(yaxis) {
     printf("button yaxis is pressed %d\n",yaxis);
	 if(yaxis > 100)
	{
		g_PlayerJumpKeyDown = 1;
	}
	if(xaxis < -100)
	{
			g_PlayerJumpKeyDown = 0;
	}
}
if(zaxis) {
    printf("button zaxis is pressed %d\n",zaxis);
	 printf("-------------------------------------\n\n");
}



}


void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
	
if (key == 65 || key == 97) //key a,A
{
g_PlayerBackwardKeyDown =1;
}
else {g_PlayerBackwardKeyDown =0;}
	//g_PlayerX = g_PlayerX - 0.01f;
		//exit(0);
		
	if (key == 68 || key == 100)//key D,d
	{
g_PlayerForwardKeyDown =1;
}
else {g_PlayerForwardKeyDown =0;}

	//g_PlayerX = g_PlayerX + 0.01f;// g_PlayerBackwardKeyUp,g_PlayerDownKeyUp,g_PlayerUpKeyUp
	
		if (key == 83 || key == 115)//key s,S, fire?
		{
			g_PlayerDownKeyDown =1;
	//g_PlayerY = g_PlayerY + 0.01f;
		}
		else
		{
			g_PlayerDownKeyDown =0;
		}
		
		if (key == 87 || key == 119)//key w,W
		{
			g_PlayerUpKeyDown =1;
	//g_PlayerY = g_PlayerY + 0.01f;
		}
		else
		{
			g_PlayerUpKeyDown =0;
		}
	//g_PlayerJumpKeyUp//
		
		if (key == 32)//key SPACEBAR
			{g_PlayerJumpKeyDown = 1;
			printf("JUMP INIT0\n");

			}//g_PlayerY = g_PlayerY + 0.01f;
		else
		    { g_PlayerJumpKeyDown = 0;} // anti-key: g_PlayerJumpKeyUp
	
	
	 // UpdateVertices();
}
// adb shell "cmd package resolve-activity --brief com.google.android.calculator | tail -n 1"


void KeyboardDown(unsigned char key, int x, int y){ 
                  //key - The ascii value of the key that's pressed
                  //x - The x coordinate of the mouse when it was pressed
                  //y - The y coordinate of the mouse when it was pressed
		if (key == 32)//key SPACEBAR
			{g_PlayerJumpKeyUp = 1; 	printf("JUMP INIT2\n");}//g_PlayerY = g_PlayerY + 0.01f;
		else
		    { g_PlayerJumpKeyUp = 0;}
	
	
    //Handle what will happen when a key is pressed down
}

void KeyboardUp(unsigned char key, int x, int y){ 
                  //key - The ascii value of the key that's pressed
                  //x - The x coordinate of the mouse when it was pressed
                  //y - The y coordinate of the mouse when it was pressed

    //Handle what will happen when a key is released
	
	
if (key == 65 || key == 97) //key a,A
{
g_PlayerBackwardKeyUp =1;
g_PlayerBackwardKeyDown =0;
}
	//g_PlayerX = g_PlayerX - 0.01f;
		//exit(0);
		
	if (key == 68 || key == 100)//key D,d
	{
	g_PlayerForwardKeyUp =1;//g_PlayerX = g_PlayerX + 0.01f;  // g_PlayerBackwardKeyUp,g_PlayerDownKeyUp,g_PlayerUpKeyUp
	g_PlayerForwardKeyDown =0;
	}
		if (key == 83 || key == 115)//key s,S, fire?
		{
	g_PlayerDownKeyUp =1;//g_PlayerY = g_PlayerY + 0.01f;
		g_PlayerDownKeyDown =0;
		}
		
		if (key == 87 || key == 119)//key w,W
		g_PlayerUpKeyUp =0;//g_PlayerY = g_PlayerY + 0.01f;
	
	//g_PlayerJumpKeyUp//
		
		if (key == 32)//key SPACEBAR
			{g_PlayerJumpKeyUp = 1;}//g_PlayerY = g_PlayerY + 0.01f;
		else
		    { g_PlayerJumpKeyUp = 0;}
		
}

float red,green,blue = 0.0f;

void processSpecialKeys(int key, int x, int y) {

	switch(key) {
		case GLUT_KEY_F1 :
				red = 1.0;
				green = 0.0;
				blue = 0.0; break;
		case GLUT_KEY_F2 :
				red = 0.0;
				green = 1.0;
				blue = 0.0; break;
		case GLUT_KEY_F3 :
				red = 0.0;
				green = 0.0;
				blue = 1.0; break;
	}
}
int frame = 0; float timebase = 0; float time = 0; float fps = 0;
void updateFPS() {
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 16.66666666666667) // 16.66666666666667
		{ 
	
	fps = frame * 1000.0 / (time - timebase);
	timebase = time; frame = 0; }
 UpdateVertices();
	}
	
	void idle() {
		updateFPS();
		glutPostRedisplay(); 
		}

// main function
// sets up window to which we'll draw
int main(int argc, char **argv)
{
	 puts("main\n");
	
	//printf("main\n");
	
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Colo Game Using OpenGL");
    glewInit();
    init();
    glutDisplayFunc(display);
	glutIdleFunc(idle);
//	glutReshapeFunc(changeSize);
//	glutIdleFunc(renderScene);

	// here are the new entries
	//glutJoystickFunc(processGamepad,300);
	
	glutKeyboardFunc(processNormalKeys);
//	glutSpecialFunc(processSpecialKeys);
	
	//    glutKeyboardFunc(KeyboardDown); //Telling glut what function to call when the event occurs
//    glutKeyboardUpFunc(KeyboardUp); //Telling glut what function to call when the event occurs

	    glutKeyboardUpFunc(KeyboardUp); //Telling glut what function to call when the event occurs

    glutMainLoop();
    return 0;
}
