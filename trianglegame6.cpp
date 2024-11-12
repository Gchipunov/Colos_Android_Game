// CPP program to render a triangle using Shaders
//trianglegame6.cpp
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <iostream>
#include <string>

using namespace std;

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
	uniform vec3 iResolution;
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
	
	uniform vec3 iResolution;
	
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
				color= vec4(0, gl_FragCoord.x, 1, 1); // pinker color
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
    GLuint programId = glCreateProgram(); // crate a program

    if (programId == 0)
    {
        cout << "Error Creating Shader Program";
        return 0;
    }

    // Attach both the shaders to it
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

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
                          0.5, 0.5, 0,
                          0.5, 0.25, 0,
                          0.25, 0.5, 0,
0.15, 0.15, 0,
                          0.5, 0.15, 0,
                          0.15, 0.5, 0

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
// Load data in VBO (Vertex Buffer Object) and return the vbo's id
GLuint loadDataInBuffers()
{
    GLfloat vertices[] = {// triangle vertex coordinates
                          -0.5, -0.5, 0,
                          0.5, -0.5, 0,
                          -0.5, 0.5, 0,
0.5, 0.5, 0,
                          0.5, -0.5, 0,
                          -0.5, 0.5, 0

};

  

    GLuint vboId;

    // allocate buffer sapce and pass data to it
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // unbind the active buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vboId;
}

// Initialize and put everything together
void init()
{
    // clear the framebuffer each frame with black color
    glClearColor(0, 0, 0, 0);

    GLuint vboId = loadDataInBuffers();
	 GLuint vboId2 = loadDataInBufferscolors();
//GLuint vboId = loadDataInBuffers();

    GLuint vShaderId = compileShaders(vertexShader2, GL_VERTEX_SHADER);
    GLuint fShaderId = compileShaders(fragmentShader2, GL_FRAGMENT_SHADER);

    GLuint programId = linkProgram(vShaderId, fShaderId);

GLint loc = glGetUniformLocation(programId, "iResolution");
// glUniform2f(loc, width, height);
//glUniform2f(loc, 500, 500);
glUniform2i(loc, 500, 500);
    // Get the 'pos' variable location inside this program
    GLuint posAttributePosition = glGetAttribLocation(programId, "pos");
 GLuint posAttributePosition2 = glGetAttribLocation(programId, "colour");

    GLuint vaoId;
    glGenVertexArrays(1, &vaoId); // Generate VAO  (Vertex Array Object)

    // Bind it so that rest of vao operations affect this vao
    glBindVertexArray(vaoId);

    // buffer from which 'pos' will receive its data and the format of that data
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexAttribPointer(posAttributePosition, 3, GL_FLOAT, false, 0, 0);

    // Enable this attribute array linked to 'pos'
    glEnableVertexAttribArray(posAttributePosition);


 GLuint vaoId2;
    glGenVertexArrays(1, &vaoId2); // Generate VAO  (Vertex Array Object)

    // Bind it so that rest of vao operations affect this vao
    glBindVertexArray(vaoId);

    // buffer from which 'pos' will receive its data and the format of that data
    glBindBuffer(GL_ARRAY_BUFFER, vboId2);
    glVertexAttribPointer(posAttributePosition2, 3, GL_FLOAT, false, 0, 0);

    // Enable this attribute array linked to 'pos'
    glEnableVertexAttribArray(posAttributePosition2);



    // Use this program for rendering.
    glUseProgram(programId);
}

// Function that does the drawing
// glut calls this function whenever it needs to redraw
void display()
{
    // clear the color buffer before each drawing
    glClear(GL_COLOR_BUFFER_BIT);

    // draw triangles starting from index 0 and
    // using 3 indices
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // swap the buffers and hence show the buffers
    // content to the screen
    glutSwapBuffers();
}

// main function
// sets up window to which we'll draw
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Triangle Using OpenGL");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
