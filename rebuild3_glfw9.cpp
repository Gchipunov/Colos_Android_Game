// Generated and Fixed up By Georgiy Chipunov
// 3/25/2025
// build and link with
//compile with appropriate libraries:
//gcc tfbuild_text_renderer_grok.cpp -o tfbuild_text_renderer_grok -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lfreetype  -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2"
// g++ vao_multiple_text4.cpp grid_quad_generator.cpp engine/shader/shader.cpp   udpgame1/GameObjects.cpp -o vao_multiple_text4 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
// g++ stbgame_Box3.cpp UtilityCode/Utility.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o stbgame_Box3 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include" -L"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/lib" -lBox2D
// gcc tfbuild_text_renderer_grok2.cpp -o tfbuild_text_renderer_grok2 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lfreetype  -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2"

// gcc tfbuild_text_renderer_grok3.cpp -o tfbuild_text_renderer_grok3 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lfreetype  -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2"
//  coding a gui from scratch video1:
// 
// https://www.youtube.com/watch?v=Z6BWRcfnivo
// 
// 
// https://github.com/Chlumsky/msdfgen
// https://jcgt.org/published/0006/02/02/
// https://web.archive.org/web/20120505050133/https://www.valvesoftware.com/publications/2007/SIGGRAPH2007_AlphaTestedMagnification.pdf
// https://github.com/SebLague/Text-Rendering
/*
Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
CMake Warning at builds/cmake/FindHarfBuzz.cmake:99 (message):
  Required version (2.0.0) is higher than found version ()
Call Stack (most recent call first):
  CMakeLists.txt:248 (find_package)


Could NOT find ZLIB (missing: ZLIB_LIBRARY ZLIB_INCLUDE_DIR)
Could NOT find PNG (missing: PNG_LIBRARY PNG_PNG_INCLUDE_DIR)
Could NOT find ZLIB (missing: ZLIB_LIBRARY ZLIB_INCLUDE_DIR)
Could NOT find BZip2 (missing: BZIP2_LIBRARIES BZIP2_INCLUDE_DIR)
Could NOT find BrotliDec (missing: BROTLIDEC_INCLUDE_DIRS BROTLIDEC_LIBRARIES)
Configuring done (0.6s)
Generating done (0.1s)
*/

// outline shader
// https://shadered.org/view?s=TZ36yJeKSb
//
// sea water shader:
// https://shadered.org/view?s=yrLiDIeFRB
// https://shadered.org/view?s=yrLiDIeFRB
// https://www.shadertoy.com/view/Ms2SD1

//
//
// 

#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glext.h>
#include <GLFW/glfw3.h>


#include <ft2build.h>
#include <freetype/freetype.h>
// -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2"
#include <vector>
#include <string>
#include <sstream>


//OS//
#include <windows.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb\stb_image_write.h"

//#include "gosha_math.h"
//#include "gosha_objects.h"
#include "colo_engine\math\triangle_rotate.h"
// colo_engine\math\triangle_rotate.cpp

using namespace std;

// https://github.com/WhalesState/pixel-engine/tree/main/drivers
// https://github.com/Noesis/Tutorials


// Renderer structure Main Memory
// https://grok.com/share/bGVnYWN5_87ee02d1-f9b1-494d-be33-a70f88b7043f
// 
//VRAM Capacity: 256 MB = 256 × 1024 × 1024 bytes = 268,435,456 bytes.
// 
//$\frac{268,435,456 \text{ bytes}}{4 \text{ bytes/f
// loat}} = 67,108,864 \text{ floats}$
//
static GLfloat* vertices_dynamic = NULL;
static GLfloat* vertices_dynamic_original = NULL;
vector <objectlist> objectlists;
vector <BVHBox> bvhlists;       // merge with objectslist?



typedef struct stateEngineRender {
    float* global_vertices_dynamic;
    int iNumVertexes;
    GLuint elapsedTimeUniform; // = glGetUniformLocation(programId, "time");

    GLuint loopDurationUnf; //  = glGetUniformLocation(programId, "loopDuration");

int iTextStartQuadsRenderer;  // where CacheTextWillStoreText
int iNumTextAlloc; // where MaxAllowedTextonScreen


};
stateEngineRender StateEngineRender;


typedef struct stateEngineRenderTriangles {
    float* vertices_dynamic;
    int iNumVertexes;
    int iStart;
    int iEnd;
};
stateEngineRenderTriangles StateEngineRenderTriangles;

typedef struct stateEngineRenderLines {
    float* vertices_dynamic;
    int iNumVertexes;
    int iStart;
    int iEnd;

};

stateEngineRenderLines StateEngineRenderLines;


typedef struct stateEngineRenderPoints {
    float* vertices_dynamic;
    int iNumVertexes;
    int iStart;
    int iEnd;

};
stateEngineRenderPoints StateEngineRenderPoints;


// Shader structure


int initGraphicsVRam()
{
// 67108864 256MB
    // muldersoft.com
    // lets get the computers specs and see whats Free..
    // 33554432 128 MB
    
    
    int iVRamAmount = 33554432;
  //  int iVMax = GetVRamMAX();


    vertices_dynamic   = (GLfloat*)malloc((iVRamAmount) * sizeof(GLfloat));
    
    vertices_dynamic_original = vertices_dynamic;
    StateEngineRender.global_vertices_dynamic = vertices_dynamic;


        if (vertices_dynamic == NULL) {
            printf("Memory allocation failed!\n");
            return -1;
        }

        return 0;

}
// Function to retrieve VBO data
void getVBOData(GLuint vbo, GLsizeiptr size, void* outputBuffer) {
    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Get the data from the VBO
    glGetBufferSubData(GL_ARRAY_BUFFER, 0, size, outputBuffer);

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void init()
{

}


struct Shader {

    GLuint program;

};



// Character structure

struct Character {

    GLuint textureID;    // Texture ID for glyph
    float texCoords[4];

    int width, height;   // Size of glyph

    int bearingX, bearingY; // Offset from baseline

    unsigned int advance;   // Horizontal advance to next glyph

};



// Global variables

Character characters[128];

Shader textShader;

GLuint VAO, VBO;

vector <float> TextVertexes;



const char* vertexShaderSource =

"#version 330 core\n"

"layout (location = 0) in vec4 vertex;\n" //
"layout (location = 1) in vec4 vtype;\n" //

"out vec2 TexCoords;\n"
"out vec4 vvtype;\n"
"uniform float fragLoopDuration;\n"
"uniform float time;\n"
"uniform mat4 projection;\n"

"void main()\n"

"{\n"

// "    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
"    gl_Position =  vec4(vertex.xy, 0.0, 1.0);\n"
"    TexCoords = vertex.zw;\n"
"    vvtype = vtype;\n"

"}\n";

// https://threejs.org/examples/#webgl_animation_keyframes
// // https://threejs.org/docs/#api/en/core/Raycaster
// 
// https://registry.khronos.org/OpenGL/specs/gl/GLSLangSpec.3.30.pdf
const char* fragmentShaderSource =

"#version 330 core\n"

"in vec2 TexCoords;\n"
"in vec4 vvtype;\n"

"out vec4 color;\n"
"uniform float fragLoopDuration;\n"
"uniform float time;\n"
"uniform mat4 projection;\n"
"uniform sampler2D text;\n"

"uniform vec3 textColor;\n"

"void main()\n"

"{\n"

// " if(gl_PrimitiveID > time )\n"
// "  {  discard; }\n"

"    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
" if(vvtype.x == 1.0f)\n"
"  {  color = vec4(textColor, 1.0) * sampled; }\n"
" else if(vvtype.x == 3.0f)\n"
//"  {   sampled = texture(text, projection[1].y,projection[2].z); \n"
"  {   sampled = vec4( sin(time),projection[2].z, projection[0].x, 0.7); \n"
" color = vec4(1.0, 0.0, 0.0, 1.0) * sampled; }\n"
"  else \n"
"  {  color = vec4(1.0,0.0,0.0, 1.0) * sampled; }\n"
//"    color = vec4(textColor, 1.0) ;\n"
//" color = texture(text, TexCoords);"
"}\n";



// Function to compile shaders

Shader createShader() {

    Shader shader;



    printf("createShader2\n");
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    glCompileShader(vertexShader);



    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader);



    shader.program = glCreateProgram();

    glAttachShader(shader.program, vertexShader);

    glAttachShader(shader.program, fragmentShader);
    printf("glLinkProgram\n");
    glLinkProgram(shader.program);

    printf("glLinkProgram2\n");

    glDeleteShader(vertexShader);

    glDeleteShader(fragmentShader);



    return shader;

}





int initTextRenderer5(const char* fontPath) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "ERROR: Could not init FreeType Library\n");
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face)) {
        fprintf(stderr, "ERROR: Failed to load font\n");
        FT_Done_FreeType(ft);
        return -2;
    }

    FT_Set_Pixel_Sizes(face, 0, 64);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Calculate atlas dimensions (assume 16x8 grid for 128 chars)
    const int glyphsPerRow = 16;
    const int numRows = 16;
    int atlasWidth = 0, atlasHeight = 0;
    int atlasWidth2 = 1024, atlasHeight2 = 1024;
    int maxGlyphWidth = 0, maxGlyphHeight = 0;

    // First pass: determine max glyph size
    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            fprintf(stderr, "WARNING: Failed to load glyph '%c'\n", c);
            continue;
        }
        maxGlyphWidth = face->glyph->bitmap.width > maxGlyphWidth ? face->glyph->bitmap.width : maxGlyphWidth;
        maxGlyphHeight = face->glyph->bitmap.rows > maxGlyphHeight ? face->glyph->bitmap.rows : maxGlyphHeight;
    }

    //  if (maxGlyphHeight > maxGlyphWidth)
    //  {
    //      maxGlyphWidth = maxGlyphHeight;
    //  }
    //  else
    //  {
   //       maxGlyphHeight=  maxGlyphWidth ;
   //   }


    atlasWidth = maxGlyphWidth * glyphsPerRow;
    atlasHeight = maxGlyphHeight * numRows;

    //  atlasWidth = maxGlyphWidth * glyphsPerRow;
//   atlasHeight = maxGlyphHeight * numRows;

   // Create atlas buffer
    unsigned char* atlasData = (unsigned char*)calloc(atlasWidth2 * atlasHeight2, sizeof(unsigned char));
    if (!atlasData) {
        fprintf(stderr, "ERROR: Failed to allocate atlas buffer\n");
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        return -3;
    }

    // Second pass: populate atlas and store character data
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            continue;
        }

        int xOffset = (c % glyphsPerRow) * maxGlyphWidth;
        int yOffset = (c / glyphsPerRow) * maxGlyphHeight;
        int LastatlasIdx = 0;
        // Copy glyph bitmap to atlas
        for (unsigned int y = 0; y < face->glyph->bitmap.rows; y++) {
            for (unsigned int x = 0; x < face->glyph->bitmap.width; x++) {
                int atlasIdx = (yOffset + y) * atlasWidth2 + (xOffset + x);
                atlasData[atlasIdx] = face->glyph->bitmap.buffer[y * face->glyph->bitmap.width + x];
                LastatlasIdx = atlasIdx;
            }
        }

        // Calculate texture coordinates
    //    float texXMin = (float)xOffset / atlasWidth2;
     //   float texYMin = (float)yOffset / atlasHeight2;
     //   float texXMax = texXMin +((float)face->glyph->bitmap.width / atlasWidth2);
  //      float texYMax = texYMin + ((float)face->glyph->bitmap.rows / atlasHeight2);
      //        float texXMax = texXMin +((float)maxGlyphWidth / atlasWidth2);
      //  float texYMax = texYMin + ((float)maxGlyphHeight / atlasHeight2);


        //  float texXMin = (float)xOffset;
        //  float texYMin = (float)yOffset ;
      //    float texXMax = texXMin + (float)face->glyph->bitmap.width;
       //   float texYMax = texYMin + (float)face->glyph->bitmap.rows ;


    //    float texXMin =( (float)(c % glyphsPerRow) * 64 )/ atlasWidth2;
   //     float texYMin = ( ( (float)c / glyphsPerRow) * 64) / atlasHeight2;
   //     float texXMax = texXMin + ((float)64/ atlasWidth2);
   //     float texYMax = texYMin + ((float)64/ atlasHeight2);


        // Box effect; 
    //    float texXMin = ((float)(c % glyphsPerRow) * 64) / atlasWidth2;
   //     float texYMin = ( (int)((float)c / glyphsPerRow) * 64) / atlasHeight2;
   //     float texXMax = texXMin + ((float)64 / atlasWidth2);
   //     float texYMax = texYMin + ((float)64 / atlasHeight2);


        // renderText("Hello, PC going to Android", 50.0f, 300.0f, 1.0f, color, 800, 600);
        //
        //H 484,245 ; 526,298
        // e 301,368 ; 347,421
        // l 727,370; 762,421
        // l
        // o 912,369; 961,415
        // 
        // ⌂ 913,432; 
        // 
        // 


        printf("char :%c LastatlasIdx:%d xOffset %d, yOffset %d, face->glyph->bitmap.width:%d , face->glyph->bitmap.rows:%d , face->glyph->bitmap.bitmap_left:%d , face->glyph->bitmap.bitmap_top:%d\n",
            c, LastatlasIdx, xOffset, yOffset, face->glyph->bitmap.width,
            face->glyph->bitmap.rows
            , face->glyph->bitmap_left,
            face->glyph->bitmap_top);
        printf("char :%c PosX: %f PosY: %f \n", c, (float)xOffset / (float)1024, (float)yOffset / (float)1024);
        printf("char :%c PosXEnd: %f PosYEnd: %f \n", c,
            ((float)xOffset / (float)1024) + ((float)64 / (float)atlasWidth2),
            ((float)yOffset / (float)1024) + ((float)64 / atlasHeight2)
        );
        printf("char :%c PosXEnd2: %f PosYEnd2: %f \n", c,
            (((float)xOffset) + ((float)face->glyph->bitmap.width)) / (float)atlasWidth2,
            ((float)yOffset + (float)face->glyph->bitmap.rows) / (float)atlasHeight2
        );

        float texXMin = (float)xOffset / (float)1024;
        float texYMin = (float)yOffset / (float)1024;
        float texXMax = (((float)xOffset) + ((float)face->glyph->bitmap.width)) / (float)atlasWidth2;
        float texYMax = ((float)yOffset + (float)face->glyph->bitmap.rows) / (float)atlasHeight2;
        //   char :H LastatlasIdx : 301579 xOffset 488, yOffset 248, face->glyph->bitmap.width : 36, face->glyph->bitmap.rows : 47, face->glyph->bitmap.bitmap_left : 6, face->glyph->bitmap.bitmap_top : 47
         //      char : H PosX : 0.476562 PosY : 0.242188

           //   face->glyph->bitmap_left,

             //     face->glyph->bitmap_top,
           // 
           // 
           // 
            // characters[c] = (Character) {
            //     .texture = texture,
            //     .texCoords = {texXMin, texYMin, texXMax, texYMax},
            //     .width = face->glyph->bitmap.width,
           //      .height = face->glyph->bitmap.rows,
           //      .bearingX = face->glyph->bitmap_left,
           //      .bearingY = face->glyph->bitmap_top,
           //      .advance = face->glyph->advance.x
         //   };

        characters[c].textureID = texture;
        characters[c].texCoords[0] = texXMin;
        characters[c].texCoords[1] = texYMin;
        characters[c].texCoords[2] = texXMax;
        characters[c].texCoords[3] = texYMax;

        characters[c].width = face->glyph->bitmap.width;
        characters[c].height = face->glyph->bitmap.rows;
        characters[c].bearingX = face->glyph->bitmap_left;
        characters[c].bearingY = face->glyph->bitmap_top;
        characters[c].advance = face->glyph->advance.x;



    }

    //  exit(0);

      // Upload atlas to GPU
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RED,
        atlasWidth2, atlasHeight2,
        0, GL_RED, GL_UNSIGNED_BYTE,
        atlasData
    );
	/*
    int c = 0;
    std::ostringstream filename;
    filename << "00AtextureMap_" << (int)c << ".png";
    int width = atlasWidth2;
    int height = atlasHeight2;
    int channels = 1; // Grayscale
    int stride = width * channels; // No padding in FreeType bitmap
    if (!stbi_write_png(filename.str().c_str(), width, height, channels, atlasData, stride)) {
        // Handle PNG write error (optional)
        printf("Handle PNG write error");
    }
*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(atlasData);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);



    
    return 0;

}

float vertices2[] =
{

    // LEVEL
         // PLAYER
     //     COORDINATES     /        COLORS,ALPHA      /   TexCoord  //
     -0.15f, -0.15f, 0.0f,     1.0f,// 0.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1STARTY,0.0f, 0.0f,0.0f, //0 Lower left corner
      0.15f,  0.15f, 0.0f,     0.0f,// 0.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1ENDY,0.0f, 0.0f,0.0f, //2 Upper right corner
      -0.15f,  0.15f, 0.0f,     0.0f,// 1.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1ENDY, 0.0f, 0.0f,0.0f,//1 Upper left corner

      -0.15f, -0.15f, 0.0f,     1.0f,// 0.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1STARTY, 0.0f, 0.0f,0.0f,//0 Lower left corner
      0.15f, -0.15f, 0.0f,     1.0f,// 1.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1STARTY,0.0f, 0.0f,0.0f,  //3 Lower right corner
       0.15f,  0.15f, 0.0f,     0.0f,// 0.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1ENDY, 0.0f, 0.0f,0.0f,//2 Upper right corner

       0.30f, 0.30f, 0.0f , 0.1f, //   0  
     0.60f, 0.60f, 0.0f , 0.0f, //  1
    0.30f, 0.60f, 0.0f , 0.0f, //     2

     0.30f, 0.30f, 0.0f , 1.0f, //     3
      0.60f, 0.30f, 0.0f , 1.0f, //     4
      0.60f, 0.60f, 0.0f , 0.0f, //     4

       -0.9f, -0.9f, 0.0f,     1.0f,// 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY,  0.0f, 0.0f, 1.0f, //0 Lower left corner
      0.9f,  0.9f, 0.0f,     0.0f, ///0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner
      -0.9f,  0.9f, 0.0f,     0.0f, //1.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //1 Upper left corner

      -0.9f, -0.9f, 0.0f,     1.0f, //0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f, //0 Lower left corner
      0.9f, -0.9f, 0.0f,     1.0f,// 1.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f,  //3 Lower right corner
       0.9f,  0.9f, 0.0f,     0.0f //0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner

  
};

void initPredefineVAO()
{
    // Configure VAO/VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_STREAM_DRAW);


}

void partOneAllocGraphics()
{

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}
void partTwoAllocGraphics(int iSize,void * vertices44)
{

   // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STREAM_DRAW);
    glBufferData(GL_ARRAY_BUFFER, iSize, vertices44, GL_STREAM_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void partTwoAllocGraphicsTest3(int iSize, void* vertices44)
{

     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STREAM_DRAW);
  //  glBufferData(GL_ARRAY_BUFFER, iSize, vertices2, GL_STREAM_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void partTwoAllocGraphicsVRAM(int iSize, void* vertices44)
{

    float* pTempFloatPTR = (float*)vertices44;

    for(int i = 0 ; i < iSize; i ++)
   {
    printf("vertices_dynamic V2 %d: %f\n\r",i,(float)pTempFloatPTR[i]);
    }

 //   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iSize  , vertices44, GL_STREAM_DRAW);
 
 
 glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iSize  , vertices44, GL_DYNAMIC_DRAW);
 //GL_DYNAMIC_DRAW 
 
  //  glBufferData(GL_ARRAY_BUFFER, iSize, pTempFloatPTR, GL_STREAM_DRAW);

  //  glBufferData(GL_ARRAY_BUFFER, iSize, vertices_dynamic_original, GL_STREAM_DRAW);
    //  glBufferData(GL_ARRAY_BUFFER, iSize, vertices2, GL_STREAM_DRAW);
   // glBufferSubData(GL_ARRAY_BUFFER, 0, iSize, vertices2);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
    // https://learnopengl.com/Advanced-OpenGL/Advanced-Data



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void  initPredefineVAO3() // CacheTextFake(const char* text, float x, float y, float scale, float color[3], int screenWidth, int screenHeight)
{
#define MASS_EXPAND 10
  const  char* text = "Hello Uber Text Super Render!";

    int iTextLength = strlen(text) + 1 + MASS_EXPAND;
    int iTextLengthInit = strlen(text) + 1;

   // glActiveTexture(GL_TEXTURE0);
    partOneAllocGraphics();
  //  glBindVertexArray(VAO);

    int iTextureIDGlobal = 0;
    int iIndexTextStartID = 0;
    int iIndexTextEndID = 0;

    iIndexTextEndID = iIndexTextStartID;




    vector <float> verticesText;



    float xpos = -0.5f;

    int iNumVertexes = 0;

    for (int i = 0; i < iTextLength; i++)
    {
        if (i < iTextLengthInit)
        {
            char characterIndexCurrent = text[i];

            //verticesText.push_back();
          //  float vertices[6][4] = {
         //   Character ch = characters[*c];
            Character ch = characters[characterIndexCurrent];


            //    float xpos = x + ch.bearingX * scale;

             //   float ypos = y - (ch.height - ch.bearingY) * scale;
             // float xpos =
            float ypos = 0.0f;

            // float w = ch.width * scale;
            float w = 0.30f;
            //  float h = ch.height * scale;
            float h = 0.30f;
         
            //    { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1]},
            verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[1]);
           
            //   { xpos,     ypos,        ch.texCoords[0],ch.texCoords[3] },
            verticesText.push_back(xpos);  verticesText.push_back(ypos);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[3]);
            //     { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },
            verticesText.push_back(xpos + w);  verticesText.push_back(ypos);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[3]);
            //     { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1] },
            verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[1]);
            //     { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },
            verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[3]);
            //      { xpos + w, ypos + h,    ch.texCoords[2],  ch.texCoords[1] }
            verticesText.push_back(xpos + w);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[1]);
            // };
            iTextureIDGlobal = ch.textureID;
            iIndexTextEndID++;

            // x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels
         //   x += w + 0.10f;
            xpos += w + 0.10f;
            iNumVertexes += 6;
        }


    }

  //  CachedTextTextureID.push_back(iTextureIDGlobal);
  //  CachedTextStart.push_back(iIndexTextStartID);
  //  CachedTextLength.push_back(iIndexTextEndID);

   // glUseProgram(textShader.program);

   // glBindBuffer(GL_ARRAY_BUFFER, VBO);

 //   glBufferSubData(GL_ARRAY_BUFFER, 0, verticesText.size() * 4, verticesText.data());

  //  glBindBuffer(GL_ARRAY_BUFFER, 0);
    partTwoAllocGraphicsTest3(iNumVertexes, verticesText.data());



}

int AllocCPUtoGPUBlock()
{
    float LevelBoxesY = -0.9f;
    float LevelBoxesX = -0.9f;
    float LevelBoxesUVX = 0.0f;
    float LevelBoxesUVY = 0.0f;
    *vertices_dynamic = LevelBoxesX; vertices_dynamic++; printf("vertices_dynamic 1: %d\n\r", vertices_dynamic); *vertices_dynamic = LevelBoxesY; vertices_dynamic++;   printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = 0.0f; vertices_dynamic++;  // end coordinates
    *vertices_dynamic = 1.0f; vertices_dynamic++; // color: red
    *vertices_dynamic = 0.0f; vertices_dynamic++; // color: green
    *vertices_dynamic = 0.0f; vertices_dynamic++; // color: blue
    *vertices_dynamic = 1.0f; vertices_dynamic++; // color: alpha
    *vertices_dynamic = LevelBoxesUVX; vertices_dynamic++; //UV X
    *vertices_dynamic = LevelBoxesUVY; vertices_dynamic++; // UV Y
    *vertices_dynamic = 0.0f; vertices_dynamic++; // animationState
    *vertices_dynamic = 0.0f; vertices_dynamic++;  printf("vertices_dynamic 11: %d\n\r", vertices_dynamic); // animationFrame
    *vertices_dynamic = 0.0f; vertices_dynamic++;  // shaderType

    return 0;


}

int AllocCPUtoGPUBlock(float QuadX, float QuadY, float QuadWidth, float QuadHeight,
    float UVX0, float UVY0, float UVX1, float UVY1
)
{
    float BoxesStartX = QuadX - (QuadWidth / 2);
    float BoxesStartY = QuadY - (QuadHeight / 2);
    float BoxesEndX = QuadX + (QuadWidth / 2);;
    float BoxesEndY = QuadY + (QuadHeight / 2);
    // wing CCW counter clock wise
 //   (-1,1)   5   ______ 4  (1,1)
 //  3| \          \    |
 //   |  \          \   |
 //   |   \          \  |
 //   |    \          \ |
//(-1,-1)1 |_____\ 2       \| 6   (1,-1)

    float vtype = 1.0f;
    // 1 Vertex
    *vertices_dynamic = BoxesStartX; printf("vertices_dynamic V 1: %f\n\r", *vertices_dynamic); vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);

    *vertices_dynamic = BoxesStartY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX0; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY0; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // 2 Vertex
    *vertices_dynamic = BoxesEndX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = BoxesStartY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX1; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY0; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // wing CCW counter clock wise
    //   (-1,1)   5   ______ 4  (1,1)
    //  3| \          \    |
    //   |  \          \   |
    //   |   \          \  |
    //   |    \          \ |
 //(-1,-1)1 |_____\ 2       \| 6   (1,-1)
    // https://www.youtube.com/watch?v=lPWfIq5DzqI&list=PLFD0EB975BA0CC1E0&index=57
    // https://learnopengl.com/Getting-started/Transformations
    // https://learnopengl.com/Advanced-OpenGL/Face-culling Triangle Winding order

    // 3 Vertex
    *vertices_dynamic = BoxesStartX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = BoxesEndY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX0; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY1; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

   // wing CCW counter clock wise
    //     (-1,1)   5   ______ 4  (1,1)
    //  3  | \          \    |
    //     |  \          \   |
    //     |   \          \  |
    //     |    \          \ |
//(-1,-1)1 |_____\ 2       \| 6   (1,-1)
    // 4 Vertex
    *vertices_dynamic = BoxesEndX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = BoxesEndY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX1; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY1; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // 5 Vertex
    *vertices_dynamic = BoxesStartX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = BoxesEndY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX0; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY1; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // 6 Vertex
    *vertices_dynamic = BoxesEndX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = BoxesStartY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX1; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY0; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;


    return 6;


}

int AllocCPUtoGPUBlockProtoType(int iIndexObjects, float QuadX, float QuadY, float QuadWidth, float QuadHeight,
    float UVX0, float UVY0, float UVX1, float UVY1
)
{
	int iNumObjectAttrVerticesWillReturn = 6;
	
		//--ADD This General Object List
			objectlist newobject;
			
			newobject.iDrawIndex = iIndexObjects;
			newobject.iType = 2; // Quad
			newobject.iNumVertices = iNumObjectAttrVerticesWillReturn;
			newobject.iSubType = 1; // General UI
			
			objectlists.push_back(newobject);
			//--ADD This General Object List
			
    float BoxesStartX = QuadX - (QuadWidth / 2);
    float BoxesStartY = QuadY - (QuadHeight / 2);
    float BoxesEndX = QuadX + (QuadWidth / 2);;
    float BoxesEndY = QuadY + (QuadHeight / 2);
    // wing CCW counter clock wise
 //   (-1,1)   5   ______ 4  (1,1)
 //  3| \          \    |
 //   |  \          \   |
 //   |   \          \  |
 //   |    \          \ |
//(-1,-1)1 |_____\ 2       \| 6   (1,-1)

    float vtype = 2.0f;
    // 1 Vertex
    *vertices_dynamic = BoxesStartX; printf("vertices_dynamic V 1: %f\n\r", *vertices_dynamic); vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);

    *vertices_dynamic = BoxesStartY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX0; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY0; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // 2 Vertex
    *vertices_dynamic = BoxesEndX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = BoxesStartY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX1; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY0; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // wing CCW counter clock wise
    //   (-1,1)   5   ______ 4  (1,1)
    //  3| \          \    |
    //   |  \          \   |
    //   |   \          \  |
    //   |    \          \ |
 //(-1,-1)1 |_____\ 2       \| 6   (1,-1)
    // https://www.youtube.com/watch?v=lPWfIq5DzqI&list=PLFD0EB975BA0CC1E0&index=57
    // https://learnopengl.com/Getting-started/Transformations
    // https://learnopengl.com/Advanced-OpenGL/Face-culling Triangle Winding order

    // 3 Vertex
    *vertices_dynamic = BoxesStartX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = BoxesEndY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX0; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY1; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // wing CCW counter clock wise
     //     (-1,1)   5   ______ 4  (1,1)
     //  3  | \          \    |
     //     |  \          \   |
     //     |   \          \  |
     //     |    \          \ |
 //(-1,-1)1 |_____\ 2       \| 6   (1,-1)
     // 4 Vertex
    *vertices_dynamic = BoxesEndX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = BoxesEndY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX1; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY1; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // 5 Vertex
    *vertices_dynamic = BoxesStartX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = BoxesEndY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX0; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY1; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // 6 Vertex
    *vertices_dynamic = BoxesEndX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = BoxesStartY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX1; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY0; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;


    return iNumObjectAttrVerticesWillReturn;


}

// D:\games_src\example_test_coded_by_AI\camera-mouse-click-ray-intersection-with-a-triangle_main-bard5.c
// // Triangle vertices (in world space)
// // vec3 triangleV0 = {-0.5f, -0.5f, 0.0f};
// // vec3 triangleV1 = { 0.5f, -0.5f, 0.0f};
// // vec3 triangleV2 = { 0.0f,  0.5f, 0.0f};

// 2D triangle, copy prototype to extend to 3D later
int AllocCPUtoGPUBlockProtoTriangle(vec3 triangleV0,
vec3 triangleV1,
vec3 triangleV2,
    float UVX0, float UVY0, 
	float UVX1, float UVY1,
	float UVX2, float UVY2
	//,
	// int iNumAllocated
)
{
   
    // wing CCW counter clock wise
 //   (-1,1)   5   ______ 4  (1,1)
 //  3| \          \    |
 //   |  \          \   |
 //   |   \          \  |
 //   |    \          \ |
//(-1,-1)1 |_____\ 2       \| 6   (1,-1)

    float vtype = 2.0f;
    // 1 Vertex
    *vertices_dynamic = triangleV0.x; printf("vertices_dynamic V 1: %f\n\r", *vertices_dynamic); vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);

    *vertices_dynamic = triangleV0.y; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX0; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY0; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // 2 Vertex
    *vertices_dynamic = triangleV1.x;  vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = triangleV1.y; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX1; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY1; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // wing CCW counter clock wise
    //   (-1,1)   5   ______ 4  (1,1)
    //  3| \          \    |
    //   |  \          \   |
    //   |   \          \  |
    //   |    \          \ |
 //(-1,-1)1 |_____\ 2       \| 6   (1,-1)
    // https://www.youtube.com/watch?v=lPWfIq5DzqI&list=PLFD0EB975BA0CC1E0&index=57
    // https://learnopengl.com/Getting-started/Transformations
    // https://learnopengl.com/Advanced-OpenGL/Face-culling Triangle Winding order

    // 3 Vertex
    *vertices_dynamic = triangleV2.x; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = triangleV2.y; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = UVX2; vertices_dynamic++; //UV X
    *vertices_dynamic = UVY2; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

  

    return 3;


}

//void GetTriangleCentroid(

int initPredefineVAOfromCPU()
{
    int iNumAttributes = 8;
	
	
	int iNumAllocated = 0;  // The Vertex Counter to keep track of objects to mod later
	
	   
    partOneAllocGraphics();

    float LevelBoxesX = -0.9f;
    float LevelBoxesY = -0.9f;
    float LevelBoxesUVX = 0.0f;
    float LevelBoxesUVY = 0.0f;

    float vtype = 3.0f; // vertex type

			//--ADD This General Object List
			objectlist newobject;
			
			newobject.iDrawIndex = iNumAllocated;
			newobject.iType = 0;
			newobject.iNumVertices = 6;
			newobject.iSubType = 1; // General UI
			
			objectlists.push_back(newobject);
			//--ADD This General Object List
			
    // 1 Vertex
    *vertices_dynamic = LevelBoxesX; printf("vertices_dynamic V 1: %f\n\r", *vertices_dynamic); vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic); 
    
    *vertices_dynamic = LevelBoxesY; vertices_dynamic++;   
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = LevelBoxesUVX; vertices_dynamic++; //UV X
    *vertices_dynamic = LevelBoxesUVY; vertices_dynamic++; // UV Y

    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;


     LevelBoxesX = -0.6f;
     LevelBoxesY = -0.9f;
   
     LevelBoxesUVX = 0.5f;
     LevelBoxesUVY = 0.0f;
     // 2 Vertex
    *vertices_dynamic = LevelBoxesX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = LevelBoxesY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = LevelBoxesUVX; vertices_dynamic++; //UV X
    *vertices_dynamic = LevelBoxesUVY; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;

    // wing CCW counter clock wise
    //   (-1,1)   5   ______ 4  (1,1)
    //  3| \          \    |
    //   |  \          \   |
    //   |   \          \  |
    //   |    \          \ |
 //(-1,-1)1 |_____\ 2       \| 6   (1,-1)
    // https://www.youtube.com/watch?v=lPWfIq5DzqI&list=PLFD0EB975BA0CC1E0&index=57
    // https://learnopengl.com/Getting-started/Transformations
    // https://learnopengl.com/Advanced-OpenGL/Face-culling Triangle Winding order

    LevelBoxesX = -0.9f;
    LevelBoxesY = -0.6f;
   
    LevelBoxesUVX = 0.0f;
    LevelBoxesUVY = 0.5f;
    // 3 Vertex
    *vertices_dynamic = LevelBoxesX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = LevelBoxesY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = LevelBoxesUVX; vertices_dynamic++; //UV X
    *vertices_dynamic = LevelBoxesUVY; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;





    // wing CCW counter clock wise
    //   (-1,1)   5   ______ 4  (1,1)
    //  3| \          \    |
    //   |  \          \   |
    //   |   \          \  |
    //   |    \          \ |
 //(-1,-1)1 |_____\ 2       \| 6   (1,-1)
    LevelBoxesX = -0.6f;
    LevelBoxesY = -0.6f;
    
    LevelBoxesUVX = 0.5f;
    LevelBoxesUVY = 0.5f;
    // 4 Vertex
    *vertices_dynamic = LevelBoxesX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = LevelBoxesY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = LevelBoxesUVX; vertices_dynamic++; //UV X
    *vertices_dynamic = LevelBoxesUVY; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;


    LevelBoxesX = -0.9f;
    LevelBoxesY = -0.6f;
   
    LevelBoxesUVX = 0.0f;
    LevelBoxesUVY = 0.5f;
    // 5 Vertex
    *vertices_dynamic = LevelBoxesX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = LevelBoxesY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = LevelBoxesUVX; vertices_dynamic++; //UV X
    *vertices_dynamic = LevelBoxesUVY; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;


    LevelBoxesX = -0.6f;
    LevelBoxesY = -0.9f;

    LevelBoxesUVX = 0.5f;
    LevelBoxesUVY = 0.0f;
    // 6 Vertex
    *vertices_dynamic = LevelBoxesX; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
    *vertices_dynamic = LevelBoxesY; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
    *vertices_dynamic = LevelBoxesUVX; vertices_dynamic++; //UV X
    *vertices_dynamic = LevelBoxesUVY; vertices_dynamic++; // UV Y
    *vertices_dynamic = vtype; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++; *vertices_dynamic = 0.0f; vertices_dynamic++;
 iNumAllocated += 6;

    float QuadX1 = -0.75f;
    float QuadY1 = -0.75f;

 
    for(int i = 0 ; i < 10; i ++)
    {
        float lQuadX = -0.55f + ((float)i * 0.05f) ;
        float lQuadY = -0.55f;
        float lQuadWidth  = 0.04f;
            float lQuadHeight = 0.04f;
            float lUVX0 = 0.0f;
            float lUVY0 = 0.0f;
            float lUVX1 = 1.0f;
            float lUVY1 = 1.0f;
			
			
		
			
            iNumAllocated += AllocCPUtoGPUBlockProtoType(iNumAllocated, lQuadX, lQuadY, lQuadWidth, lQuadHeight,
                lUVX0, lUVY0, lUVX1, lUVY1);
   
    }
	
	// Triangle vertices (in world space)
vec3 triangleV0 = {-0.5f, -0.5f, 0.0f};
vec3 triangleV1 = { 0.5f, -0.5f, 0.0f};
vec3 triangleV2 = { 0.0f,  0.5f, 0.0f};

float CenterX = 0.0f;
float CenterY = 0.0f;
float CenterZ = 0.0f;

    float UVX0 = 0.0f; 
    float UVY0  = 0.0f;
	float UVX1  = 1.0f;
	float UVY1  = 0.0f;
	float UVX2 = 0.5f; 
	float UVY2 = 1.0f;
	objectlist newobject_triangle;
			
			newobject_triangle.iDrawIndex = iNumAllocated;
			newobject_triangle.iType = 1;
			
			printf("(objectlists[i].iDrawIndex * sizeof(float): %d objectlists[i].iDrawIndex: %d", 
			newobject_triangle.iDrawIndex * sizeof(float), newobject_triangle.iDrawIndex);
			// exit(0);
			// (objectlists[i].iDrawIndex * sizeof(float): 264 objectlists[i].iDrawIndex: 66
			// 528 is pointer location, 528 / 8 = 66
			// newobject_triangle.iDrawIndex  * iNumAllocated
			
			newobject_triangle.iNumVertices = 3;
			newobject_triangle.iSubType = 1; // General UI
			
			objectlists.push_back(newobject_triangle);
		
	iNumAllocated += AllocCPUtoGPUBlockProtoTriangle(triangleV0, triangleV1, triangleV2,
	  UVX0,  UVY0, 
	 UVX1,  UVY1,
	 UVX2,  UVY2);
	 
	 


	// Triangle vertices (in world space)
vec3 triangleV0_2 = {0.15f, 0.1f, 0.0f};
vec3 triangleV1_2 = { 0.2f, 0.2f, 0.0f};
vec3 triangleV2_2 = { 0.1f,  0.2f, 0.0f};

float CenterX_2 = 0.0f;
float CenterY_2 = 0.0f;
float CenterZ_2 = 0.0f;


    float UVX0_2 = 0.0f; 
    float UVY0_2  = 0.0f;
	float UVX1_2  = 1.0f;
	float UVY1_2  = 0.0f;
	float UVX2_2 = 0.5f; 
	float UVY2_2 = 1.0f;
	objectlist newobject_triangle_2;
			
			newobject_triangle_2.iDrawIndex = iNumAllocated;
			newobject_triangle_2.iType = 1;
			newobject_triangle_2.iNumVertices = 3;
			newobject_triangle_2.iSubType = 1; // General UI
			
			objectlists.push_back(newobject_triangle_2);
		
	iNumAllocated += AllocCPUtoGPUBlockProtoTriangle(triangleV0_2, triangleV1_2, triangleV2_2,
	  UVX0_2,  UVY0_2, 
	 UVX1_2,  UVY1_2,
	 UVX2_2,  UVY2_2);




	// Triangle vertices (in world space)
vec3 triangleV0_3 = {0.85f, 0.1f, 0.0f};
vec3 triangleV1_3 = { 0.9f, 0.2f, 0.0f};
vec3 triangleV2_3 = { 0.8f,  0.2f, 0.0f};

float CenterX_3 = 0.0f;
float CenterY_3 = 0.0f;
float CenterZ_3 = 0.0f;


    float UVX0_3 = 0.0f; 
    float UVY0_3  = 0.0f;
	float UVX1_3  = 1.0f;
	float UVY1_3  = 0.0f;
	float UVX2_3 = 0.5f; 
	float UVY2_3 = 1.0f;
	
	
	objectlist newobject_triangle_3;
			
			newobject_triangle_3.iDrawIndex = iNumAllocated;
			newobject_triangle_3.iType = 1;
			newobject_triangle_3.iNumVertices = 3;
			newobject_triangle_3.iSubType = 1; // General UI
			
			objectlists.push_back(newobject_triangle_3);
		
	iNumAllocated += AllocCPUtoGPUBlockProtoTriangle(triangleV0_3, triangleV1_3, triangleV2_3,
	  UVX0_3,  UVY0_3, 
	 UVX1_3,  UVY1_3,
	 UVX2_3,  UVY2_3);
	 
	 // class ClassTriangleObject comment out and add class ClassTriangleObject colo_engine/ClassTriangleObject.cpp
	 
    for (int j = 0; j < 20; j++)
    {
        float lQuadX = -0.55f + ((float)j * 0.05f);
        float lQuadY = -0.15f;
        float lQuadWidth = 0.04f;
        float lQuadHeight = 0.04f;
        float lUVX0 = 0.0f;
        float lUVY0 = 0.0f;
        float lUVX1 = 1.0f;
        float lUVY1 = 1.0f;
		
					//--ADD This General Object List
			objectlist newobject;
			
			newobject.iDrawIndex = iNumAllocated;
			newobject.iType = 0;
			newobject.iNumVertices = 6;
			newobject.iSubType = 1; // General UI
			
			objectlists.push_back(newobject);
			//--ADD This General Object List
			
        iNumAllocated += AllocCPUtoGPUBlock(lQuadX, lQuadY, lQuadWidth, lQuadHeight,
            lUVX0, lUVY0, lUVX1, lUVY1);

    }

   int  iNumVertexes = ( iNumAllocated) * iNumAttributes  ;
   // 264 / 4 = 66 
   // 
   vertices_dynamic =  vertices_dynamic_original  ;

   StateEngineRender.iNumVertexes = iNumVertexes;

    // partTwoAllocGraphics(iNumVertexes, verticesText.data());
   partTwoAllocGraphicsVRAM(iNumVertexes, vertices_dynamic);


    return 0;
}

vector <float> verticesText; 

void  initPredefineVAO2() // CacheTextFake(const char* text, float x, float y, float scale, float color[3], int screenWidth, int screenHeight)
{
#define MASS_EXPAND 10
    const  char* text = "Hello Uber Text Super Render!";

    int iTextLength = strlen(text) + 1 + MASS_EXPAND;
    int iTextLengthInit = strlen(text) + 1;

    // glActiveTexture(GL_TEXTURE0);
    partOneAllocGraphics();
    //  glBindVertexArray(VAO);

    int iTextureIDGlobal = 0;
    int iIndexTextStartID = 0;
    int iIndexTextEndID = 0;

    iIndexTextEndID = iIndexTextStartID;








    float xpos = -0.5f;

    int iNumVertexes = 0;

   
 //  verticesText.push_back(xpos + w);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[1]);
  // -0.9f, -0.9f, 0.0f, 1.0f,// 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY,  0.0f, 0.0f, 1.0f, //0 Lower left corner
    verticesText.push_back(-0.5f);  verticesText.push_back(0.0f);   verticesText.push_back(0.0f); verticesText.push_back(1.0f);

    //0.9f, 0.9f, 0.0f, 0.0f, ///0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner
        verticesText.push_back(-0.2f);  verticesText.push_back(0.3f);   verticesText.push_back(0.0f); verticesText.push_back(0.0f);


     //  -0.9f, 0.9f, 0.0f, 0.0f, //1.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //1 Upper left corner
           verticesText.push_back(-0.5f);  verticesText.push_back(0.3f);   verticesText.push_back(0.0f); verticesText.push_back(0.0f);

      // -0.9f, -0.9f, 0.0f, 1.0f, //0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f, //0 Lower left corner
           verticesText.push_back(-0.5f);  verticesText.push_back(0.0f);   verticesText.push_back(0.0f); verticesText.push_back(1.0f);

       //    0.9f, -0.9f, 0.0f, 1.0f,// 1.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f,  //3 Lower right corner
           verticesText.push_back(-0.2f);  verticesText.push_back(0.0f);   verticesText.push_back(0.0f); verticesText.push_back(1.0f);

     //  0.9f, 0.9f, 0.0f, 0.0f, //0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner
           verticesText.push_back(-0.2f);  verticesText.push_back(0.3f);   verticesText.push_back(0.0f); verticesText.push_back(0.0f);

       // PLAYER
       //     COORDINATES     /        COLORS,ALPHA      /   TexCoord  //
    //  asd  -0.15f, -0.15f, 0.0f, 1.0f,// 0.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1STARTY,0.0f, 0.0f,0.0f, //0 Lower left corner
           verticesText.push_back(-0.15f);  verticesText.push_back(-0.15f);   verticesText.push_back(0.0f); verticesText.push_back(0.0f);

       //    0.15f, 0.15f, 0.0f, 0.0f,// 0.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1ENDY,0.0f, 0.0f,0.0f, //2 Upper right corner
       verticesText.push_back(0.15f);  verticesText.push_back(0.15f);   verticesText.push_back(0.0f); verticesText.push_back(0.0f);

    //   -0.15f, 0.15f, 0.0f, 0.0f,// 1.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1ENDY, 0.0f, 0.0f,0.0f,//1 Upper left corner
       verticesText.push_back(-0.15f);  verticesText.push_back(0.15f);   verticesText.push_back(0.0f); verticesText.push_back(0.0f);

   //    -0.15f, -0.15f, 0.0f, 1.0f,// 0.0f, 0.0f,0.0f,	PLAYER1STARTX, PLAYER1STARTY, 0.0f, 0.0f,0.0f,//0 Lower left corner
       verticesText.push_back(-0.15f);  verticesText.push_back(-0.15f);   verticesText.push_back(0.0f); verticesText.push_back(0.0f);

   //    0.15f, -0.15f, 0.0f, 1.0f,// 1.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1STARTY,0.0f, 0.0f,0.0f,  //3 Lower right corner
       verticesText.push_back(0.15f);  verticesText.push_back(-0.15f);   verticesText.push_back(0.0f); verticesText.push_back(0.0f);

     //  0.15f, 0.15f, 0.0f, 0.0f// 0.0f, 1.0f,0.0f,	PLAYER1ENDX, PLAYER1ENDY, 0.0f, 0.0f,0.0f,//2 Upper right corner
       verticesText.push_back(0.15f);  verticesText.push_back(0.15f);   verticesText.push_back(0.0f); verticesText.push_back(0.0f);


    //  CachedTextTextureID.push_back(iTextureIDGlobal);
    //  CachedTextStart.push_back(iIndexTextStartID);
    //  CachedTextLength.push_back(iIndexTextEndID);

     // glUseProgram(textShader.program);

     // glBindBuffer(GL_ARRAY_BUFFER, VBO);

   //   glBufferSubData(GL_ARRAY_BUFFER, 0, verticesText.size() * 4, verticesText.data());

    //  glBindBuffer(GL_ARRAY_BUFFER, 0);
       iNumVertexes = 12;
   // partTwoAllocGraphics(iNumVertexes, verticesText.data());
       partTwoAllocGraphicsTest3(iNumVertexes, verticesText.data());


}


// fixme use map
vector <int>CachedTextStart;
vector <int>CachedTextLength;
vector <int>CachedTextTextureID;

void CacheText(const char* text, float x, float y, float scale, float color[3], int screenWidth, int screenHeight)
{
#define MASS_EXPAND 10
    int iTextLength = strlen(text) + 1 + MASS_EXPAND;
    int iTextLengthInit = strlen(text) + 1;

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);

    int iTextureIDGlobal = 0;
    int iIndexTextStartID = 0;
    int iIndexTextEndID = 0;

    iIndexTextEndID = iIndexTextStartID;

    vector <float> verticesText;
    for (int i = 0; i < iTextLength; i++)
    {
        if (i < iTextLengthInit)
        {
            char characterIndexCurrent = text[i];

            //verticesText.push_back();
          //  float vertices[6][4] = {
         //   Character ch = characters[*c];
            Character ch = characters[characterIndexCurrent];


            float xpos = x + ch.bearingX * scale;

            float ypos = y - (ch.height - ch.bearingY) * scale;



            float w = ch.width * scale;

            float h = ch.height * scale;

            //    { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1]},
            verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[1]);
            //   { xpos,     ypos,        ch.texCoords[0],ch.texCoords[3] },
            verticesText.push_back(xpos);  verticesText.push_back(ypos);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[3]);
            //     { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },
            verticesText.push_back(xpos + w);  verticesText.push_back(ypos);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[3]);
            //     { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1] },
            verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[1]);
            //     { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },
            verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[3]);
            //      { xpos + w, ypos + h,    ch.texCoords[2],  ch.texCoords[1] }
            verticesText.push_back(xpos + w);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[1]);
            // };
            iTextureIDGlobal = ch.textureID;
            iIndexTextEndID++;

            x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels
        }


    }

    CachedTextTextureID.push_back(iTextureIDGlobal);
    CachedTextStart.push_back(iIndexTextStartID);
    CachedTextLength.push_back(iIndexTextEndID);

    glUseProgram(textShader.program);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferSubData(GL_ARRAY_BUFFER, 0, verticesText.size() * 4, verticesText.data());

}

void RenderCachedTextID(int textCachedID)
{
    int iTextureTextID = CachedTextTextureID[textCachedID];
    int iStartDrawIndex = CachedTextStart[textCachedID];
    int iLengthTextTriangles = CachedTextLength[textCachedID];

    glBindTexture(GL_TEXTURE_2D, iTextureTextID);

    glDrawArrays(GL_TRIANGLES, iStartDrawIndex, iStartDrawIndex + iLengthTextTriangles);



}

void CacheTextFake(const char* text, float x, float y, float scale, float color[3], int screenWidth, int screenHeight)
{
#define MASS_EXPAND 10
    int iTextLength = strlen(text) + 1 + MASS_EXPAND;
    int iTextLengthInit = strlen(text) + 1;

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);

    int iTextureIDGlobal = 0;
    int iIndexTextStartID = 0;
    int iIndexTextEndID = 0;

    iIndexTextEndID = iIndexTextStartID;




    vector <float> verticesText;
    
    
    
    float xpos = -0.5f;

    for (int i = 0; i < iTextLength; i++)
    {
        if (i < iTextLengthInit)
        {
            char characterIndexCurrent = text[i];

            //verticesText.push_back();
          //  float vertices[6][4] = {
         //   Character ch = characters[*c];
            Character ch = characters[characterIndexCurrent];


        //    float xpos = x + ch.bearingX * scale;

         //   float ypos = y - (ch.height - ch.bearingY) * scale;
         // float xpos =
                float ypos = 0.0f;

           // float w = ch.width * scale;
                float w = 0.30f;
          //  float h = ch.height * scale;
                float h = 0.30f;

            //    { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1]},
            verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[1]);
            //   { xpos,     ypos,        ch.texCoords[0],ch.texCoords[3] },
            verticesText.push_back(xpos);  verticesText.push_back(ypos);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[3]);
            //     { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },
            verticesText.push_back(xpos + w);  verticesText.push_back(ypos);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[3]);
            //     { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1] },
            verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[1]);
            //     { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },
            verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[3]);
            //      { xpos + w, ypos + h,    ch.texCoords[2],  ch.texCoords[1] }
            verticesText.push_back(xpos + w);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[1]);
            // };
            iTextureIDGlobal = ch.textureID;
            iIndexTextEndID++;

           // x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels
            x += w + 0.10f;
            xpos += w + 0.10f;

        }


    }

    CachedTextTextureID.push_back(iTextureIDGlobal);
    CachedTextStart.push_back(iIndexTextStartID);
    CachedTextLength.push_back(iIndexTextEndID);

    glUseProgram(textShader.program);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferSubData(GL_ARRAY_BUFFER, 0, verticesText.size() * 4, verticesText.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void CacheTextFake2(const char* text, float x, float y, float scale, float color[3], int screenWidth, int screenHeight)
{
#define MASS_EXPAND 10
    int iTextLength = strlen(text) + 1 + MASS_EXPAND;
    int iTextLengthInit = strlen(text) + 1;

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);

    int iTextureIDGlobal = 0;
    int iIndexTextStartID = 0;
    int iIndexTextEndID = 0;

    iIndexTextEndID = iIndexTextStartID;




    vector <float> verticesText;



    float xpos = -0.5f;
    float ypos = 0.0f;

    // float w = ch.width * scale;
    float w = 0.30f;
    //  float h = ch.height * scale;
    float h = 0.30f;
    int characterIndexCurrent = 65;
    Character ch = characters[characterIndexCurrent];
    //    { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1]},
    verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[1]);
    //   { xpos,     ypos,        ch.texCoords[0],ch.texCoords[3] },
    verticesText.push_back(xpos);  verticesText.push_back(ypos);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[3]);
    //     { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },
    verticesText.push_back(xpos + w);  verticesText.push_back(ypos);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[3]);
    //     { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1] },
    verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[1]);
    //     { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },
    verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[3]);
    //      { xpos + w, ypos + h,    ch.texCoords[2],  ch.texCoords[1] }
    verticesText.push_back(xpos + w);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[1]);
    // };
    iTextureIDGlobal = ch.textureID;
    iIndexTextEndID++;

    // x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels
    x += w + 0.10f;
    xpos += w + 0.10f;

    verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[1]);
    //   { xpos,     ypos,        ch.texCoords[0],ch.texCoords[3] },
    verticesText.push_back(xpos);  verticesText.push_back(ypos);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[3]);
    //     { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },
    verticesText.push_back(xpos + w);  verticesText.push_back(ypos);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[3]);
    //     { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1] },
    verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[0]); verticesText.push_back(ch.texCoords[1]);
    //     { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },
    verticesText.push_back(xpos);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[3]);
    //      { xpos + w, ypos + h,    ch.texCoords[2],  ch.texCoords[1] }
    verticesText.push_back(xpos + w);  verticesText.push_back(ypos + h);   verticesText.push_back(ch.texCoords[2]); verticesText.push_back(ch.texCoords[1]);




    CachedTextTextureID.push_back(iTextureIDGlobal);
    CachedTextStart.push_back(iIndexTextStartID);
    CachedTextLength.push_back(iIndexTextEndID);

    glUseProgram(textShader.program);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferSubData(GL_ARRAY_BUFFER, 0, verticesText.size(), verticesText.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}



void RenderCachedQuads(int screenWidth, int screenHeight)
{
    // Set up orthographic projection

    float projection[16] = {

        2.0f / screenWidth, 0.0f, 0.0f, 0.0f,

        0.0f, 2.0f / screenHeight, 0.0f, 0.0f,

        0.0f, 0.0f, -1.0f, 0.0f,

        -1.0f, -1.0f, 0.0f, 1.0f

    };



    glUseProgram(textShader.program);
    float color[3] = { 0.0f, 1.0f, 1.0f }; // White text
    glUniform3f(glGetUniformLocation(textShader.program, "textColor"), color[0], color[1], color[2]);

    glUniformMatrix4fv(glGetUniformLocation(textShader.program, "projection"), 1, GL_FALSE, projection);


    glBindVertexArray(VAO);


    glDrawArrays(GL_TRIANGLES, 0,18);

}


int frame = 0; float timebase = 0; float timeNow = 0; float fps = 0;


void UpdateInitTextShaderUniforms(int screenWidth, int screenHeight) // TextShader will be initbut there can be a 2nd uber shader for in-game
{
    glUseProgram(textShader.program);
    frame++;
   // time = glutGet(GLUT_ELAPSED_TIME);
     //  double time = glfwGetTime();
    timeNow = glfwGetTime();

    if (timeNow - timebase > 16.66666666666667) // 16.66666666666667
    {

        fps = frame * 1000.0 / (timeNow - timebase);
        timebase = timeNow; frame = 0;
    }

  
    GLfloat loopduration = (timeNow - timebase);
    // https://github.com/freneticmonkey/quel_solaar/blob/2eedecc2b9794dcfde1c0b266d03971157f04989/Betray/b_win32_main.c
    glUniform1f(StateEngineRender.elapsedTimeUniform, timeNow);
    glUniform1f(StateEngineRender.loopDurationUnf, loopduration);



    // Set up orthographic projection

    float projectionGlobal[16] = {

        2.0f / screenWidth, 0.0f, 0.0f, 0.0f,

        0.0f, 2.0f / screenHeight, 0.0f, 0.0f,

        0.0f, 0.0f, -1.0f, 0.0f,

        -1.0f, -1.0f, 0.0f, 1.0f

    };




   
    float color[3] = { 0.0f, 1.0f, 1.0f }; // White text
    glUniform3f(glGetUniformLocation(textShader.program, "textColor"), color[0], color[1], color[2]);

    glUniformMatrix4fv(glGetUniformLocation(textShader.program, "projection"), 1, GL_FALSE, projectionGlobal);


}
/*
 0   *vertices_dynamic = triangleV0.x; printf("vertices_dynamic V 1: %f\n\r", *vertices_dynamic); vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);

 1   *vertices_dynamic = triangleV0.y; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
 2   *vertices_dynamic = UVX0; vertices_dynamic++; //UV X
 3   *vertices_dynamic = UVY0; vertices_dynamic++; // UV Y
 4   *vertices_dynamic = vtype; vertices_dynamic++; 
 5 *vertices_dynamic = 0.0f; vertices_dynamic++; 
 6 *vertices_dynamic = 0.0f; vertices_dynamic++; 
 7 *vertices_dynamic = 0.0f; vertices_dynamic++;

    // 2 Vertex
  8  *vertices_dynamic = triangleV1.x;  vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
  9  *vertices_dynamic = triangleV1.y; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
  10  *vertices_dynamic = UVX1; vertices_dynamic++; //UV X
  11  *vertices_dynamic = UVY1; vertices_dynamic++; // UV Y
  12  *vertices_dynamic = vtype; vertices_dynamic++; 
  13 *vertices_dynamic = 0.0f; vertices_dynamic++; 
  14 *vertices_dynamic = 0.0f; vertices_dynamic++; 
  15 *vertices_dynamic = 0.0f; vertices_dynamic++;

    // wing CCW counter clock wise
    //   (-1,1)   5   ______ 4  (1,1)
    //  3| \          \    |
    //   |  \          \   |
    //   |   \          \  |
    //   |    \          \ |
 //(-1,-1)1 |_____\ 2       \| 6   (1,-1)
    // https://www.youtube.com/watch?v=lPWfIq5DzqI&list=PLFD0EB975BA0CC1E0&index=57
    // https://learnopengl.com/Getting-started/Transformations
    // https://learnopengl.com/Advanced-OpenGL/Face-culling Triangle Winding order

    // 3 Vertex
   16 *vertices_dynamic = triangleV2.x; vertices_dynamic++;
    printf("vertices_dynamic 1: %d\n\r", vertices_dynamic);
   17 *vertices_dynamic = triangleV2.y; vertices_dynamic++;
    printf("vertices_dynamic 2: %d\n\r", vertices_dynamic);
   18 *vertices_dynamic = UVX2; vertices_dynamic++; //UV X
   19 *vertices_dynamic = UVY2; vertices_dynamic++; // UV Y
   20 *vertices_dynamic = vtype; vertices_dynamic++; 
   21 *vertices_dynamic = 0.0f; vertices_dynamic++; 
   22 *vertices_dynamic = 0.0f; vertices_dynamic++; 
   23 *vertices_dynamic = 0.0f; vertices_dynamic++;
*/
void updateTriangle1()
{
	   int iNumAttributes = 8;
	     
	// 
	//static GLfloat* vertices_dynamic_original = NULL;
	GLfloat* vertices_dynamic_temp = vertices_dynamic_original;
	
	for(int i =0 ; i < objectlists.size(); i++)
	{
		if(objectlists[i].iType == 1 ) //&& i == 12)  //;// && i == 11)
		{
			vec3 triangleV0 ; 
			
		triangleV0.x  = vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) + 0 ] ;;
		triangleV0.y  = vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes)  +1 ] ;;
		triangleV0.z  = 0;
			
			vec3 triangleV1 ;
			
		triangleV1.x  = vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) +8 ] ;;
		triangleV1.y  = vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes)+9 ] ;;
		triangleV1.z  = 0;
				
			
			vec3 triangleV2 ; 
			
		triangleV2.x  = vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) +16 ] ;;
		triangleV2.y  = vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) +17 ] ;;
		triangleV2.z  = 0;			
			
		//	float rotationAngleDegrees = (float)glfwGetTime() % 180.0f;
		float rotationAngleDegrees = fmod((float)glfwGetTime(), 180.0f);
		
		
			rotateTriangle( triangleV0  ,  triangleV1 , triangleV2 ,
			objectlists[i],
			rotationAngleDegrees
			);
printf("rotationAngleDegrees: %f i: %d %f,%f  %f,%f   %f,%f  =?= %f,%f  %f,%f   %f,%f \n(objectlists[i].iDrawIndex * sizeof(float)): %d\n(objectlists[i].iDrawIndex * iNumAttributes): %d \n\n",rotationAngleDegrees, i,
		vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) + 0 ],
		vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) + 1 ],
		vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) +8 ],
		vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) +9 ],
		vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) +16 ],
		vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) +17 ],
		
		triangleV0.x,
		triangleV0.y,
		triangleV1.x,
		triangleV1.y,
		triangleV2.x,
		triangleV2.y
		, (objectlists[i].iDrawIndex * sizeof(float)),
		(objectlists[i].iDrawIndex * iNumAttributes)
		);


 vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) + 0 ] =triangleV0.x   ;;
		  vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes)+1 ] = triangleV0.y ;;
		triangleV0.z  = 0;
		
			
		  vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) +8 ] = triangleV1.x ;;
		  vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) +9 ] = triangleV1.y  ;;
		triangleV1.z  = 0;
		
			
		 vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) +16 ] =  triangleV2.x  ;;
		   vertices_dynamic_temp [(objectlists[i].iDrawIndex  * iNumAttributes) +17 ] = triangleV2.y ;;
		triangleV2.z  = 0;		


// newobject_triangle.iDrawIndex
		//glSubBuffer
		//  void glBufferSubData(GLenum target​, GLintptr offset​, GLsizeiptr size​, const GLvoid * data​);
// https://www.khronos.org/opengl/wiki/GLAPI/glBufferSubData
// https://stackoverflow.com/questions/73404182/glbuffersubdata-and-glbindarray
// glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(vertex), &vertices[0]);
  // glBufferSubData(GL_ARRAY_BUFFER,objectlists[i].iDrawIndex,objectlists[i].iNumVertices * iNumAttributes,(void*) *(vertices_dynamic_temp [objectlists[i].iDrawIndex + 0 ]));
  //glBufferSubData(GL_ARRAY_BUFFER,objectlists[i].iDrawIndex,objectlists[i].iNumVertices * iNumAttributes,(void*) &vertices_dynamic_temp + objectlists[i].iDrawIndex  );
 // glBufferSubData(GL_ARRAY_BUFFER,objectlists[i].iDrawIndex * iNumAttributes * sizeof(float),objectlists[i].iNumVertices * iNumAttributes * sizeof(float),(void*) (vertices_dynamic_temp + (objectlists[i].iDrawIndex * iNumAttributes * sizeof(float) ))  );
 glBindVertexArray(VAO);
		   glBindBuffer(GL_ARRAY_BUFFER, VBO);

glBufferSubData(GL_ARRAY_BUFFER,objectlists[i].iDrawIndex  * iNumAttributes * sizeof(float),objectlists[i].iNumVertices * iNumAttributes * sizeof(float),(void*) (vertices_dynamic_temp + (objectlists[i].iDrawIndex * iNumAttributes))  );
// debug parameters for copy to GPU
		// printf("\n\nglBufferSubData(GL_ARRAY_BUFFER,%d,%d,%d);\n\n", 

		// objectlists[i].iDrawIndex  * iNumAttributes * sizeof(float),
		// objectlists[i].iNumVertices * iNumAttributes * sizeof(float),
		// (void*) (vertices_dynamic_temp + (objectlists[i].iDrawIndex * iNumAttributes))  );

   glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		
		
	}
	//exit(0);
	
	

	
}
void RenderCachedQuadsVRAM(int screenWidth, int screenHeight)
{
  
    UpdateInitTextShaderUniforms( screenWidth,  screenHeight);

 

    // Get elapsed time
  //  double time = glfwGetTime();
    int iStartTriangle = 24;
    if (StateEngineRender.iNumVertexes <= iStartTriangle)
    {
        iStartTriangle = 0;

    }
   
updateTriangle1();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
   glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
 //   glDrawArrays(GL_TRIANGLES, iStartTriangle, StateEngineRender.iNumVertexes);
    glDrawArrays(GL_TRIANGLES, 0, StateEngineRender.iNumVertexes);
    //iStartTriangle++;
   // glDrawArrays(GL_LINES, 0, 6);
   glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
// Render text function

void renderText(const char* text, float x, float y, float scale, float color[3], int screenWidth, int screenHeight) {

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



    // Set up orthographic projection

    float projection[16] = {

        2.0f / screenWidth, 0.0f, 0.0f, 0.0f,

        0.0f, 2.0f / screenHeight, 0.0f, 0.0f,

        0.0f, 0.0f, -1.0f, 0.0f,

        -1.0f, -1.0f, 0.0f, 1.0f

    };



    glUseProgram(textShader.program);

    glUniform3f(glGetUniformLocation(textShader.program, "textColor"), color[0], color[1], color[2]);

    glUniformMatrix4fv(glGetUniformLocation(textShader.program, "projection"), 1, GL_FALSE, projection);

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);



    // Iterate through all characters

    for (const char* c = text; *c; c++) {

        Character ch = characters[*c];



        float xpos = x + ch.bearingX * scale;

        float ypos = y - (ch.height - ch.bearingY) * scale;



        float w = ch.width * scale;

        float h = ch.height * scale;


        /*

        float vertices[6][4] = {

            { xpos,     ypos + h,   0.0f, 0.0f },

            { xpos,     ypos,       0.0f, 1.0f },

            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },

            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos + w, ypos + h,   1.0f, 0.0f }

        };
             characters[c].texCoords[0] = texXMin;
        characters[c].texCoords[1] = texYMin;
        characters[c].texCoords[2] = texXMax;
        characters[c].texCoords[3] = texYMax;
        */

        float vertices[6][4] = {

            { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1]},

            { xpos,     ypos,        ch.texCoords[0],ch.texCoords[3] },

            { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },

            { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1] },

            { xpos + w, ypos,        ch.texCoords[2], ch.texCoords[3] },

            { xpos + w, ypos + h,    ch.texCoords[2],  ch.texCoords[1] }

        };

        float verticesAlt[6][4] = {

           { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1]},

           { xpos,     ypos,        ch.texCoords[0],ch.texCoords[3] },

           { xpos + w, ypos,        ch.texCoords[1], ch.texCoords[3] },

           { xpos,     ypos + h,   ch.texCoords[0], ch.texCoords[1] },

           { xpos + w, ypos,        ch.texCoords[1], ch.texCoords[3] },

           { xpos + w, ypos + h,    ch.texCoords[1],  ch.texCoords[1] }

        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);



        x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels

    }



    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* window = NULL;

int initGLFW3()
{

    //  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   //   glutInitWindowSize(800, 600);
    //  glutCreateWindow("Grok ft2build fonts");
    if (!glfwInit()) {
        //  std::cerr << "Failed to initialize GLFW" << std::endl;
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFWwindow* 
    window = glfwCreateWindow(800, 600, "Grok ft2build fonts GLFW3", nullptr, nullptr);
    if (!window) {
        //  std::cerr << "Failed to create GLFW window" << std::endl;
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


}


void render() {
    printf("color\n\n");
    float color[3] = { 0.0f, 1.0f, 1.0f }; // White text
    printf("while\n\n");
 //   renderText("Hello, PC going to Android", 50.0f, 300.0f, 1.0f, color, 800, 600);

    //    glBindVertexArray(0);

   // RenderCachedTextID(0);
  //  RenderCachedQuads(800, 600);
    RenderCachedQuadsVRAM(800, 600);

   // glutSwapBuffers();
    glfwSwapBuffers(window);
    glfwPollEvents();
}
// Usage example
void idle() {

    //  glutPostRedisplay();
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void     setupTextRenderShaderUniforms()
{


    glUseProgram(textShader.program);

   // glUniform3f(glGetUniformLocation(textShader.program, "textColor"), color[0], color[1], color[2]);
    StateEngineRender.elapsedTimeUniform = glGetUniformLocation(textShader.program, "time");
    StateEngineRender.loopDurationUnf = glGetUniformLocation(textShader.program, "loopDuration");
}
int main(int argc, char** argv) {

    // Initialize OpenGL context with GLEW here
    //glutInit(&argc, argv);
    initGLFW3();
    printf("glewInit\n\n");
    glewInit();

    //  initTextRenderer5("clacon2.ttf");

    //  initTextRenderer5("MorePerfectDOSVGA.ttf");

    //  initTextRenderer5("LessPerfectDOSVGA.ttf");
    //  initTextRenderer5("VT220-mod.ttf");

      // 
    //  initTextRenderer5("glass_tty_vt220.ttf");



    char systemPath[MAX_PATH];

    // Get system directory path
  //  if (GetSystemDirectoryA(systemPath, MAX_PATH)) {
    // GetWindowsDirectoryA

    // list system languages.. ;;
	// verdana.ttf
	textShader = createShader();
	

    if (GetWindowsDirectoryA(systemPath, MAX_PATH)) {
        char systemPath2[MAX_PATH];
        sprintf_s(systemPath2, "%s\\fonts\\%s", systemPath, "arial.ttf");

        // if (FT_New_Face(ft, systemPath2, 0, &face)) {
             // Handle error
        //     return;
         //}
        printf("initTextRenderer\n\n");
        if (initTextRenderer5(systemPath2) != 0) {
            // Handle error
            return -1;

        }

    }
    else

    {
        return -1;
    }
	

    // initPredefineVAO();
    
 int iRTSGFX =   initGraphicsVRam();
 if (iRTSGFX == -1) // ⚠️
 {
     return -1;
 }

  //  initPredefineVAO2();
    initPredefineVAOfromCPU();


    float colorCached[3] = { 0.0f, 0.0f, 1.0f }; // Green text
    float colorText1[3] = { 1.0f, 0.0f, 1.0f }; // Green text
  //    CacheText("Hello, PC going to Android", 50.0f, 300.0f, 1.0f, colorText1, 800, 600);
    //  CacheTextFake("Hello, PC going to Android", 50.0f, 300.0f, 1.0f, colorText1, 800, 600);

      // while (1 ) {

    glClear(GL_COLOR_BUFFER_BIT);



    // Render text at position (100, 100) with scale 1.0

  //  renderText("Hello, OpenGL!", 100.0f, 100.0f, 1.0f, color, 800, 600);



    // Swap buffers and poll events

// }
  //  glutIdleFunc(idle);
    int size = sizeof(float) * 264;
    // Get VBO data

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
  

    // Buffer to store retrieved data
    GLfloat* retrievedData = (GLfloat*)malloc(size);
    if (!retrievedData) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    getVBOData(VBO, size , retrievedData);

    // Print retrieved data
    printf("Retrieved VBO data:\n");
    for (int i = 0; i < size / sizeof(float) ; i++) {
        printf("VBO[%d]: %f \n",i,  retrievedData[i]);
    }
    printf("\n");
    free(retrievedData);

    int iTextureTextID = characters[36].textureID;
    
    setupTextRenderShaderUniforms();


    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, iTextureTextID);

    while (!glfwWindowShouldClose(window)) {


        processInput(window);
        render();

    }
    //   glutDisplayFunc(render);
     //  glutMainLoop();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //   glDeleteBuffers(1, &EBO);
    glDeleteProgram(textShader.program);
    
    free(vertices_dynamic_original);

    glfwTerminate();


    return 0;

}
// https://steamcommunity.com/id/bm_killer10/myworkshopfiles/
// 
// Generated and Fixed up By Georgiy Chipunov
// 3/25/2025
// build and link with
//compile with appropriate libraries:
//gcc tfbuild_text_renderer_grok.cpp -o tfbuild_text_renderer_grok -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lfreetype  -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2"
// g++ vao_multiple_text4.cpp grid_quad_generator.cpp engine/shader/shader.cpp   udpgame1/GameObjects.cpp -o vao_multiple_text4 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32
// g++ stbgame_Box3.cpp UtilityCode/Utility.cpp grid_quad_generator.cpp audioengine.c udpgame1/GameObjects.cpp -o stbgame_Box3 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -lalut -lpthread -L"D:/OpenAL_1-1_SDK/libs/Win64" -lOpenAL32 -I"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/include" -L"D:/games_src/Box2D_v2.3.0/Box2D_v2.3.0/Box2D-install2/lib" -lBox2D
// gcc tfbuild_text_renderer_grok2.cpp -o tfbuild_text_renderer_grok2 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lfreetype  -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2"

// gcc tfbuild_text_renderer_grok3.cpp -o tfbuild_text_renderer_grok3 -lopengl32 -lglew32 -lfreeglut -lglu32 -l ws2_32 -L"D:/games_src/example_test_coded_by_AI/freetype/lib" -lfreetype  -I "D:/games_src/example_test_coded_by_AI/freetype/include/freetype2"

