


#include "quad_renderer.h"


ClassRendererQuad::ClassRendererQuad(ColoQuadShaderManager *shader) //ClassRendererQuad()
{
	mShader = shader; // Store the reference
}


ClassRendererQuad::~ClassRendererQuad()
{
	
	mShader = nullptr;
	
}


//void ClassRendererQuad::OnStartGraphics() {
  //mTrivialShader = new TrivialShader();
  //mTrivialShader->Compile();
 //mTextRenderer = new TextRenderer(mTrivialShader);
 // Ensure shaders are compiled if not already
 //   if (mShader) {
  //      mShader->init_shaders();
 //   }
 

//}
void ClassRendererQuad::OnStartGraphics() {
    // 1. Define a simple unit quad (0,0 to 1,1)
    // Layout: Pos(X, Y, Z), UV(U, V)
	
	float zDepth = -5.0f; // was 0.0f with orthogal
	
    GLfloat vertices[] = {
        x, y, 					zDepth,  0.0f, 0.0f, // Bottom Left
        x +width, y, 			zDepth,  1.0f, 0.0f, // Bottom Right
        x, y + height, 			zDepth,  0.0f, 1.0f, // Top Left
        x +width, y + height, 	zDepth,  1.0f, 1.0f  // Top Right
    };

    GLuint indices[] = { 0, 1, 2, 1, 2, 3 };

    // 2. Generate and Bind VAO (GLES 3.0+)
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // 3. VBO
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 4. EBO
    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 5. Attributes (Using the locations cached in your ShaderManager)
    // Position
    glVertexAttribPointer(mShader->attr_inPosition, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(mShader->attr_inPosition);

    // UV
    glVertexAttribPointer(mShader->attr_inUV, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(mShader->attr_inUV);

    glBindVertexArray(0); 
    LOGD("ClassRendererQuad::OnStartGraphics %x Created VBO:%d EBO:%d VAO:%d ",this, mVBO, mEBO, mVAO);
}


void ClassRendererQuad::OnKillGraphics() {
    // remove all widgets
  //DeleteWidgets();
  if (mVAO) glDeleteVertexArrays(1, &mVAO);
    if (mVBO) glDeleteBuffers(1, &mVBO);
    if (mEBO) glDeleteBuffers(1, &mEBO);
    
    mVAO = mVBO = mEBO = 0;
		
		// We do NOT delete mShader here because it is shared, 
    // but we should null it if the manager is being destroyed.
    mShader = nullptr;
}

void ClassRendererQuad::OnScreenResized(int width, int height) {
  // screen got resized; if we have widgets and graphics, we have to recreate
  // them
  //SceneManager *mgr = SceneManager::GetInstance();
  //if (mgr->HasGraphics() && mWidgetCount > 0) {
   // DeleteWidgets();
  //  OnCreateWidgets();
  //}
}



void ClassRendererQuad::DoFrame() {
	//if (!mShader || !mShader->bShaderCompiled) return;

   // glUseProgram(mShader->program);
	
	LOGD("ClassRendererQuad::DoFrame()  %f, %f with Program: %d", x, y, mShader->program);
	RenderQuad( x,  y,  width,  height) ;
	
}
	/*
	float *
buildOrthographicMatrix(float *outMatrix, float halfHeight, float aspect, float near,
                                 float far) {
    float halfWidth = halfHeight * aspect;

    // column 1
    outMatrix[0] = 1.f / halfWidth;
    outMatrix[1] = 0.f;
    outMatrix[2] = 0.f;
    outMatrix[3] = 0.f;

    // column 2
    outMatrix[4] = 0.f;
    outMatrix[5] = 1.f / halfHeight;
    outMatrix[6] = 0.f;
    outMatrix[7] = 0.f;

    // column 3
    outMatrix[8] = 0.f;
    outMatrix[9] = 0.f;
    outMatrix[10] = -2.f / (far - near);
    outMatrix[11] = -(far + near) / (far - near);

    // column 4
    outMatrix[12] = 0.f;
    outMatrix[13] = 0.f;
    outMatrix[14] = 0.f;
    outMatrix[15] = 1.f;

    return outMatrix;
}
*/
/*
	void ClassRendererQuad::RenderQuad(float x, float y, float width, float height) {
  // if (!mShader || !mShader->bShaderCompiled) return;
  
   if (!mShader || !mShader->bShaderCompiled) {
	   aout<<" ClassRendererQuad::RenderQuad if (!mShader || !mShader->bShaderCompiled)"<<std::endl;
	
	   
	   return;
	   
   }

   // glUseProgram(mShader->program);


glUseProgram(mShader->program);
float aspect = 0.5f;

float virtualHeight = 1080.0f;
    float halfHeight = virtualHeight / 2.0f;
    float halfWidth = (virtualHeight * aspect) / 2.0f;
//	float mProjectionMatrix[4][4];
	
	//buildOrthographicMatrix(mProjectionMatrix , .. cide this);
	float mProjectionMatrix[16]; // Use a flat array for OpenGL compatibility
    buildOrthographicMatrix(mProjectionMatrix, halfHeight, aspect, -1.0f, 1.0f);
	
   // glUniformMatrix4fv(mShader->uniform_uProjection, 1, GL_FALSE, &mProjectionMatrix);
        glUniformMatrix4fv(mShader->uniform_uProjection, 1, GL_FALSE, mProjectionMatrix);
    // 1. Set Uniforms (Example: projection and time)
    // Assuming you have a projection matrix ready
    // glUniformMatrix4fv(mShader->uniform_uProjection, 1, GL_FALSE, &projMatrix[0][0]);

    // 2. Define geometry (a simple quad)
    GLfloat vertices[] = {
        x,         y,          0.0f,  0.0f, 0.0f, // pos, uv
        x + width, y,          0.0f,  1.0f, 0.0f,
        x,         y + height, 0.0f,  0.0f, 1.0f,
        x + width, y + height, 0.0f,  1.0f, 1.0f
    };

    // 3. Set Attributes
    glVertexAttribPointer(mShader->attr_inPosition, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), vertices);
    glEnableVertexAttribArray(mShader->attr_inPosition);

    glVertexAttribPointer(mShader->attr_inUV, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), &vertices[3]);
    glEnableVertexAttribArray(mShader->attr_inUV);

    // 4. Draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    aout<<"ClassRendererQuad::RenderQuad glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);"<<std::endl;
	
    glDisableVertexAttribArray(mShader->attr_inPosition);
    glDisableVertexAttribArray(mShader->attr_inUV);
}
*/

float * buildOrthographicMatrix(float *outMatrix, float halfHeight, float aspect, float near, float far) {
    float halfWidth = halfHeight * aspect;

    // Column 1: Scale X
    outMatrix[0] = 1.0f / halfWidth;
    outMatrix[1] = 0.0f;
    outMatrix[2] = 0.0f;
    outMatrix[3] = 0.0f;

    // Column 2: Scale Y
    outMatrix[4] = 0.0f;
    outMatrix[5] = 1.0f / halfHeight;
    outMatrix[6] = 0.0f;
    outMatrix[7] = 0.0f;

    // Column 3: Scale Z
    outMatrix[8] = 0.0f;
    outMatrix[9] = 0.0f;
    outMatrix[10] = -2.0f / (far - near);
    outMatrix[11] = 0.0f; // This was your bug! 11 is part of the column, not the translation.

    // Column 4: Translation (W)
    outMatrix[12] = 0.0f;
    outMatrix[13] = 0.0f;
    outMatrix[14] = -(far + near) / (far - near); // Translation for Z goes here
    outMatrix[15] = 1.0f;

    return outMatrix;
}

float * buildPerspectiveMatrix(float *outMatrix, float fovDegrees, float aspect, float near, float far) {
    float fovRadians = fovDegrees * (3.1415926535f / 180.0f);
    float f = 1.0f / tanf(fovRadians / 2.0f);

    // Column 1
    outMatrix[0] = f / aspect;
    outMatrix[1] = 0.0f;
    outMatrix[2] = 0.0f;
    outMatrix[3] = 0.0f;

    // Column 2
    outMatrix[4] = 0.0f;
    outMatrix[5] = f;
    outMatrix[6] = 0.0f;
    outMatrix[7] = 0.0f;

    // Column 3
    outMatrix[8] = 0.0f;
    outMatrix[9] = 0.0f;
    outMatrix[10] = (far + near) / (near - far);
    outMatrix[11] = -1.0f; // W-divide component

    // Column 4
    outMatrix[12] = 0.0f;
    outMatrix[13] = 0.0f;
    outMatrix[14] = (2.0f * far * near) / (near - far);
    outMatrix[15] = 0.0f;

    return outMatrix;
}

void ClassRendererQuad::RenderQuad(float x, float y, float width, float height) {
    if (!mShader || !mShader->bShaderCompiled) 
	{
	LOGD("Error Drawing Quad at %f, %f with Program: %d", x, y, mShader->program);
	
		return;

	}
    glUseProgram(mShader->program);
//LOGD("Drawing Quad at %f, %f with Program: %d", x, y, mShader->program);

    // --- 1. Matrix Logic ---
    // You should probably pass 'aspect' from SceneManager
  //  float aspect = 1.0f; 
  //  float mProjectionMatrix[16];
    // Note: Use your buildOrthographicMatrix here
  //  buildOrthographicMatrix(mProjectionMatrix, 540.0f, aspect, -1.0f, 1.0f);
  // Change halfHeight to 1.0f and aspect to 1.0f to match your -0.5f positions
////buildOrthographicMatrix(mProjectionMatrix, 1.0f, 1.0f, -1.0f, 1.0f);
  ////  glUniformMatrix4fv(mShader->uniform_uProjection, 1, GL_FALSE, mProjectionMatrix);

// Get the real aspect from your SceneManager/Screen
 SceneManager *mgr = SceneManager::GetInstance();
float aspect = (float)mgr->GetScreenWidth() / (float)mgr->GetScreenHeight();

float mProjectionMatrix[16];
//buildOrthographicMatrix(mProjectionMatrix, 1.0f, aspect, -1.0f, 1.0f);
buildPerspectiveMatrix(mProjectionMatrix, 45.0f, aspect, 0.1f, 1000.0f);

glUniformMatrix4fv(mShader->uniform_uProjection, 1, GL_FALSE, mProjectionMatrix);

    // --- 2. Draw using the VAO ---
    glBindVertexArray(mVAO);
    
    // Using glDrawElements instead of glDrawArrays because we have an EBO
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void ClassRendererQuad::RenderQuad2(float x, float y, float w, float h, float* viewMatrix) {
    glUseProgram(mShader->program);


// Get the real aspect from your SceneManager/Screen
 SceneManager *mgr = SceneManager::GetInstance();
float aspect = (float)mgr->GetScreenWidth() / (float)mgr->GetScreenHeight();

float mProjectionMatrix[16];
//buildOrthographicMatrix(mProjectionMatrix, 1.0f, aspect, -1.0f, 1.0f);
buildPerspectiveMatrix(mProjectionMatrix, 45.0f, aspect, 0.1f, 1000.0f);

    // Upload Projection (Static for the screen)
    glUniformMatrix4fv(mShader->uniform_uProjection, 1, GL_FALSE, mProjectionMatrix);

    // Upload View (Dynamic from Camera)
    GLint uViewLoc = glGetUniformLocation(mShader->program, "uView");
    glUniformMatrix4fv(uViewLoc, 1, GL_FALSE, viewMatrix);


    // ... Bind VAO and glDrawElements ...
	
	  // --- 2. Draw using the VAO ---
    glBindVertexArray(mVAO);
    
    // Using glDrawElements instead of glDrawArrays because we have an EBO
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
	
}

