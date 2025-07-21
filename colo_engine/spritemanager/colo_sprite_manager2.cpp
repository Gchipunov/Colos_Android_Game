// https://users.polytech.unice.fr/~buffa/cours/synthese_image/DOCS/Tutoriaux/Nehe/opengl.htm
// https://www.gamedev.net/articles/programming/general-and-gameplay-programming/general-collision-detection-for-games-using-ell-r1026/
// va_arg http://www.swin.edu.au/astronomy/pbourke/geometry/
// https://developer.arm.com/documentation/101655/0961/Cx51-User-s-Guide/Library-Reference/Reference/va-arg

#include "colo_sprite_manager2.h"

// Global sprite position and scale
gosha_vec2 spritePosition(0.0f, 0.0f);
gosha_vec2 spriteSize(1.0f, 1.0f); // Default size in NDC


SpriteManager2::SpriteManager2(Shader *pShader , GLuint gl_uintSpriteManager_texture, int width, int height)
{
	ourShader = pShader;
	SpriteManager_texture = gl_uintSpriteManager_texture;
	g_iWidth  = width;
	g_iHeight = height;
	iIsFullScreen = 0;
}


SpriteManager2::~SpriteManager2()
{
	
	
}
void SpriteManager2::UpdateDeminsions(int width, int height)
{
	g_iWidth  = width;
	g_iHeight = height;
}
void SpriteManager2::AddTriangle()
{
	GLfloat vertices[] = {
    -0.5f, -0.333333f, 0.0f, // Bottom-left
     0.5f, -0.333333f, 0.0f, // Bottom-right
     0.0f,  0.666667f, 0.0f  // Top
};
}
void SpriteManager2::AddTriangleEquilateral()
{
	GLfloat vertices[] = {
    // Left vertex
    -0.5f, -0.288675f, 0.0f,
    // Right vertex
     0.5f, -0.288675f, 0.0f,
    // Top vertex
     0.0f,  0.57735f, 0.0f
};
}
void SpriteManager2::AddQuad()
{
	
}

void SpriteManager2::AddRhombus()
{
	GLfloat rhombusVertices[] = {
    // Triangle 1 (Top)
     0.0f,  0.57735f, 0.0f, // Top vertex
    -0.5f, -0.288675f, 0.0f, // Bottom-left
     0.5f, -0.288675f, 0.0f, // Bottom-right
    
    // Triangle 2 (Bottom)
    -0.5f, -0.288675f, 0.0f, // Top-left of T2 (shared with T1)
     0.5f, -0.288675f, 0.0f, // Top-right of T2 (shared with T1)
     0.0f, -0.57735f, 0.0f  // Bottom vertex
};

}

void SpriteManager2::AddCube()
{
	
}

void SpriteManager2::AddCircle()
{
	
}

void SpriteManager2::AddSphere()
{
	
}

void SpriteManager2::AddHexagon()
{
	
}

void SpriteManager2::AddCone()
{
	
}
void SpriteManager2::AddPiramid()
{
	
}

void SpriteManager2::InitStuff()
{
  // Set up vertex data (and buffer(s)) and configure vertex attributes
    GLfloat vertices[] = {
        // Positions        // Texture Coords
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // Top-right
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Bottom-right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Bottom-left 
		
		-0.5f,-0.15f, 0.0f, 0.365f, 0.336f,
		
		-0.4f,-0.15f, 0.0f, 0.4825f, 0.336f,
		-0.4f,-0.25f, 0.0f,  0.4825f,  0.2185f,
		
		-0.5f,-0.25f, 0.0f, 0.365f, 0.2185f,
    };
	
	

    GLuint indices[] = {
        0, 1, 2, // First Triangle
        2, 3, 0,  // Second Triangle
		
		4 , 5 , 6,
		6 , 7 , 4
    };

  
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

}


int SpriteManager2::InitUniformsStuff()
{
	 // get uniforms
	 if(ourShader)
	 {
	  int projectionLoc = glGetUniformLocation(ourShader->ID, "projection");
	  
	  return 0;
	  
	 }
	 else
	 {
		 return -1;
	 }
}

void SpriteManager2::SetupUniformsStuff()
{
    // set uniforms
	
}

void SpriteManager2::DrawStuff()
{
	 // Render
        // Clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, SpriteManager_texture);

        // Activate shader
        ourShader->use();
        ourShader->setInt("ourTexture", 0);

         // Create transformations
		 /*
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(spritePosition, 0.0f));
        model = glm::scale(model, glm::vec3(spriteSize, 1.0f));

        // Create the view matrix (camera)
        glm::mat4 view = glm::mat4(1.0f);
        // For a 2D game, the view matrix is typically a translation matrix.
        // Let's create a "camera" at a fixed position looking at the origin.
        // In this case, we'll just keep it as the identity matrix since we're not
        // moving the camera, but this is where you would add camera movement.
        // view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
*/
Mat4 model; // Starts as identity
    model = model.translate(Vec3(spritePosition.x, spritePosition.y, 0.0f));
    model = model.scale(Vec3(spriteSize.x, spriteSize.y, 1.0f));

    // Create the view matrix (camera)
    Mat4 view; // Starts as identity
    // For a 2D game, the view matrix is typically a translation matrix.
    // Let's create a "camera" at a fixed position looking at the origin.
    // In this case, we'll just keep it as the identity matrix since we're not
    // moving the camera, but this is where you would add camera movement.
    // If you wanted a moving camera, you would translate the view matrix
    // in the opposite direction of the camera's movement.
    // Example: view = view.translate(Vec3(-camera_x, -camera_y, -camera_z));
    // Or use lookAt if you have a more complex camera setup:
    // view = Mat4::lookAt(Vec3(0.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));


    // Create the projection matrix
  //  Mat4 projection = Mat4::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    // --- Aspect Ratio Logic ---
    float aspectRatio = (float)g_iWidth / (float)g_iHeight;
    float quadAspectRatio = 1.0f; // The quad is a square, so its ratio is 1:1

    // Get the location of the projection uniform in the shader
   // int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    
    // Create an orthographic projection matrix
    // The quad will be drawn within the [-1, 1] range of the longest side.
    if (aspectRatio > quadAspectRatio) {
        // Window is wider than the quad's aspect ratio
        // We'll scale the width to match the window, and keep height at [-1, 1]
        float orthoWidth = aspectRatio / quadAspectRatio;
       // glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, Mat4::ortho(-orthoWidth, orthoWidth, -1.0f, 1.0f) );
 // Mat4 projection =  Mat4::ortho(-orthoWidth, orthoWidth, -1.0f, 1.0f) ;
 Mat4 projection = Mat4::ortho(-orthoWidth, orthoWidth, -1.0f, 1.0f, -1.0f, 1.0f);
       ourShader->setMat4("projection", projection.value_ptr() );
  } else {
        // Window is taller than the quad's aspect ratio
        // We'll scale the height to match the window, and keep width at [-1, 1]
        float orthoHeight = quadAspectRatio / aspectRatio;
    //    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, Mat4::ortho(-1.0f, 1.0f, -orthoHeight, orthoHeight) );
    // Mat4 projection =  Mat4::ortho(-1.0f, 1.0f, -orthoHeight, orthoHeight) ;
	  Mat4 projection =  Mat4::ortho(-1.0f, 1.0f, -orthoHeight, orthoHeight, -1.0f, 1.0f);
	      ourShader->setMat4("projection", projection.value_ptr() );
	
   }
	

        ourShader->setMat4("model", model.value_ptr() );
		ourShader->setMat4("view", view.value_ptr() );
       // ourShader->setMat4("projection", projection.value_ptr() );


       // Draw quad
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
}

void SpriteManager2::DeleteStuff()
{
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}