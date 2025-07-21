//7 https://github.com/linusmossberg/fluid-simulator/blob/629301987fff9e82cf1f1cc99b010b5f8619136b/source/gl-util/arrow.cpp
// https://therealmjp.github.io/posts/sss-intro/
// https://developer.apple.com/metal/sample-code/



#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

//#include <GL/glut.h>
//#include <GL/glew.h>


#include  "scenecode/scene_manager.h"
//#include "scenecode/demo_scene.h"
#include "scenecode/loader_scene.h"

#include "UtilityCode/Utility.h"
#include "engine/shader/shader.h"


//#include "spritecode/Sprite.h"
//#include "spritecode/SpriteMaps.h"

// #include "spritecode/SpriteManager.h"

#include "spritecode/shaders_game1.h"
//#include "spritecode/save_texture.h"

#include "grid_quad_generator.h"

#include "spritecode/hindi_text.h"


#include "engine/player/player_game.h"

#include  "spritecode/MapManager.h"



 int mSurfWidth = 0;
 int mSurfHeight = 0;
   SceneManager *mgr = nullptr;
   bool mIsFirstFrame = true;
   
// class MapManager;

extern TextRendererHindi rendererSTBTextHindi;


//#define STB_TRUETYPE_IMPLEMENTATION
//#include "stb/stb_truetype.h"
 //#define STBTT_STATIC
 //#define STB_IMAGE_STATIC
 //#define STB_IMAGE_WRITE_STATIC
 
 
#include "spritecode/hindi_text.h"




int g_Width  = 500;
int g_Height = 500;

HWND hwndGetForegroundWindow = 0;

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


// Shader sources
const char* vertexShaderSource140 = R"(
    #version 140
    in vec2 aPos;
    in vec2 aTexCoord;
    out vec2 TexCoord;
    uniform mat4 projection;
    void main() {
		TexCoord = aTexCoord;
        gl_Position = projection * vec4(aPos, 0.0, 1.0);

    }
)";

const char* fragmentShaderSourceold140 = R"(
    #version 140

   
    uniform sampler2D textTexture;
    uniform vec3 textColor;
	
	    in vec2 TexCoord;
	out vec4 color;
	
    void main() {
        float alpha = texture(textTexture, TexCoord).r;
		
        color = vec4(textColor, alpha);
    }
)";
const char* fragmentShaderSource2140 = R"(
#version 140

uniform sampler2D textTexture;
uniform vec3 textColor;
uniform vec2 texSize; // Add texture size uniform for proper sampling

in vec2 TexCoord;
out vec4 color;

void main() {
    float alpha = texture(textTexture, TexCoord).r;
    
    // Outline parameters
    float outlineDist = 0.005; // Adjust for outline thickness
    vec3 outlineColor = vec3(0.0); // Black outline
    
    // Sample neighboring pixels for outline
    vec2 offset = outlineDist / texSize;
    float outlineAlpha = 0.0;
    
    // Check 4 surrounding pixels
    outlineAlpha += texture(textTexture, TexCoord + vec2(offset.x, 0.0)).r;
    outlineAlpha += texture(textTexture, TexCoord + vec2(-offset.x, 0.0)).r;
    outlineAlpha += texture(textTexture, TexCoord + vec2(0.0, offset.y)).r;
    outlineAlpha += texture(textTexture, TexCoord + vec2(0.0, -offset.y)).r;
    
    // Average and clamp outline alpha
    outlineAlpha = min(outlineAlpha * 0.25, 1.0);
    
    // Combine outline and text
    float finalAlpha = max(alpha, outlineAlpha);
    vec3 finalColor = mix(outlineColor, textColor, alpha / finalAlpha);
    
    color = vec4(finalColor, finalAlpha);
}
)";
const char* fragmentShaderSource140_grokGarbage = R"(
#version 140

uniform sampler2D textTexture;
uniform vec3 textColor;

in vec2 TexCoord;
out vec4 color;

void main() {
    float alpha = texture(textTexture, TexCoord).r;
    
    // Outline parameters
    float outlineDist = 0.005; // Adjust for outline thickness
    vec3 outlineColor = vec3(0.0); // Black outline
    const vec2 texSize = vec2(0.02); // Constant texture size
    
    // Sample neighboring pixels for outline
    vec2 offset = outlineDist / texSize;
    float outlineAlpha = 0.0;
    
    // Check 4 surrounding pixels
    outlineAlpha += texture(textTexture, TexCoord + vec2(offset.x, 0.0)).r;
    outlineAlpha += texture(textTexture, TexCoord + vec2(-offset.x, 0.0)).r;
    outlineAlpha += texture(textTexture, TexCoord + vec2(0.0, offset.y)).r;
    outlineAlpha += texture(textTexture, TexCoord + vec2(0.0, -offset.y)).r;
    
    // Average and clamp outline alpha
    outlineAlpha = min(outlineAlpha * 0.25, 1.0);
    
    // Combine outline and text
    float finalAlpha = max(alpha, outlineAlpha);
    vec3 finalColor = mix(outlineColor, textColor, alpha / finalAlpha);
    
    color = vec4(finalColor, finalAlpha);
}
)";
// https://github.com/justinmeiners/stb-truetype-example/blob/master/main.c
// 
// basic text effcts:
// https://www.shadertoy.com/view/Md23DV

// super shaders:
// https://www.shadertoy.com/view/4sSfzK
// https://www.bing.com/images/search?view=detailV2&ccid=SB70Koaz&id=213B6153F63BCF065903F1D90D64F63A875EBD6A&thid=OIP.SB70Koazz4tAtqIB05Q8NAHaEK&mediaurl=https%3a%2f%2froystan.net%2fmedia%2ftutorials%2foutline-demo.png&cdnurl=https%3a%2f%2fth.bing.com%2fth%2fid%2fR.481ef42a86b3cf8b40b6a201d3943c34%3frik%3dar1ehzr2ZA3Z8Q%26pid%3dImgRaw%26r%3d0%26sres%3d1%26sresct%3d1%26srh%3d731%26srw%3d1300&exph=405&expw=720&q=Outline+Shader&simid=608009525863656242&FORM=IRPRST&ck=11578196E8A406910FD3806B5F624D8F&selectedIndex=0&itb=0
// https://www.bing.com/images/search?view=detailV2&ccid=SB70Koaz&id=213B6153F63BCF065903F1D90D64F63A875EBD6A&thid=OIP.SB70Koazz4tAtqIB05Q8NAHaEK&mediaurl=https%3a%2f%2froystan.net%2fmedia%2ftutorials%2foutline-demo.png&cdnurl=https%3a%2f%2fth.bing.com%2fth%2fid%2fR.481ef42a86b3cf8b40b6a201d3943c34%3frik%3dar1ehzr2ZA3Z8Q%26pid%3dImgRaw%26r%3d0%26sres%3d1%26sresct%3d1%26srh%3d731%26srw%3d1300&exph=405&expw=720&q=Outline+Shader&simid=608009525863656242&FORM=IRPRST&ck=11578196E8A406910FD3806B5F624D8F&selectedIndex=0&itb=0
// https://www.bing.com/images/search?view=detailV2&ccid=B1Z9zq6F&id=91481FCD9C84F225210B9DFC841DA6AA317629DE&thid=OIP.B1Z9zq6FIGFWsVwM7xyIZgHaHa&mediaurl=https%3a%2f%2fwww.videopoetics.com%2ftutorials%2fpixel-perfect-outline-shaders-unity%2fclassic-sphere.png&cdnurl=https%3a%2f%2fth.bing.com%2fth%2fid%2fR.07567dceae85206156b15c0cef1c8866%3frik%3d3il2MaqmHYT8nQ%26pid%3dImgRaw%26r%3d0&exph=512&expw=512&q=Outline+Shader&simid=608025150959008148&FORM=IRPRST&ck=743A2A7191470921B29A54C7F230CD51&selectedIndex=2&itb=0
// 


// outline effects:
// https://www.bing.com/images/search?q=Outline+Shader&mmreqh=XoHqB99nVXX9qAt2RBbfN0kLJthBCt3IphyJpqRwBBE%3d&form=INLIRS&cw=1417&ch=782&first=1
// https://www.bing.com/images/search?view=detailV2&ccid=ChFrSDv%2f&id=DE9D6D51F7D078EC5E70D1CD57FA110BD6DFF44D&thid=OIP.ChFrSDv_hAfcDrASwXiF-gHaEI&mediaurl=https%3a%2f%2fwww.codinblack.com%2fwp-content%2fuploads%2f2020%2f03%2fCombining-two-images-to-create-an-outline-shader.jpg&cdnurl=https%3a%2f%2fth.bing.com%2fth%2fid%2fR.0a116b483bff8407dc0eb012c17885fa%3frik%3dTfTf1gsR%252blfN0Q%26pid%3dImgRaw%26r%3d0&exph=479&expw=857&q=Outline+Shader&simid=607999991022047139&FORM=IRPRST&ck=5ECCE8931BDE725AA52481A4879FCDCF&selectedIndex=4&itb=0
/// https://www.bing.com/images/search?view=detailV2&ccid=rcby7jA0&id=7C8900E3A7CF5A0801D36EB251536D232E83A9D0&thid=OIP.rcby7jA0avRwnLtmCtwjzAAAAA&mediaurl=https%3A%2F%2Fgodotshaders.com%2Fwp-content%2Fuploads%2F2021%2F01%2FCube_glow_1.87.1.jpg&cdnurl=https%3A%2F%2Fth.bing.com%2Fth%2Fid%2FR.adc6f2ee30346af4709cbb660adc23cc%3Frik%3D0KmDLiNtU1Gybg%26pid%3DImgRaw%26r%3D0&exph=266&expw=474&q=Outline+Shader&simid=608048597170137096&form=IRPRST&ck=A08F5774AF774EF2DCFD9EEC9EF0F5B0&selectedindex=2&itb=0&pivotparams=insightsToken%3Dccid_ChFrSDv%252F*cp_5ECCE8931BDE725AA52481A4879FCDCF*mid_DE9D6D51F7D078EC5E70D1CD57FA110BD6DFF44D*simid_607999991022047139*thid_OIP.ChFrSDv!_hAfcDrASwXiF-gHaEI&vt=0&sim=11&iss=VSI
// https://www.bing.com/images/search?view=detailV2&ccid=G1J1jL7n&id=213B6153F63BCF0659031AD551120CB2D6B5F15E&thid=OIP.G1J1jL7nr3SEc_VFEXxq2gHaEK&mediaurl=https%3a%2f%2froystan.net%2fmedia%2ftutorials%2foutline-bloom.png&cdnurl=https%3a%2f%2fth.bing.com%2fth%2fid%2fR.1b52758cbee7af748473f545117c6ada%3frik%3dXvG11rIMElHVGg%26pid%3dImgRaw%26r%3d0&exph=304&expw=540&q=Outline+Shader&simid=608031069447722763&FORM=IRPRST&ck=9190427A5533E81C2D5091174423AA7D&selectedIndex=5&itb=0
// 


// text shaders:
// https://catlikecoding.com/unity/documentation/text-shaders/
// https://catlikecoding.com/
// https://github.com/Gchipunov/ShadertoyText
// https://www.shadertoy.com/view/XtfyRS embbed 

// https://en.wikipedia.org/wiki/Text_shaping
const char* fragmentShaderSource140 = R"(
#version 140

uniform sampler2D textTexture;
uniform vec3 textColor;

in vec2 TexCoord;
out vec4 color;

void main() {
    float alpha = texture(textTexture, TexCoord).r;
    
    // Outline parameters
    float outlineDist = 0.005; // Adjust for outline thickness
    vec3 outlineColor = vec3(0.0); // Black outline
  //  const vec2 texSize = vec2(0.02); // Constant texture size
    
    // Sample neighboring pixels for outline
   // vec2 offset = outlineDist / texSize;
    float outlineAlpha = 0.0;
    
    // Check 4 surrounding pixels
    outlineAlpha += texture(textTexture, TexCoord + vec2(outlineDist, 0.0)).r;
    outlineAlpha += texture(textTexture, TexCoord + vec2(-outlineDist, 0.0)).r;
    outlineAlpha += texture(textTexture, TexCoord + vec2(0.0, outlineDist)).r;
    outlineAlpha += texture(textTexture, TexCoord + vec2(0.0, -outlineDist)).r;
    
    // Average and clamp outline alpha
    outlineAlpha = min(outlineAlpha * 0.25, 1.0);
    
    // Combine outline and text
    float finalAlpha = max(alpha, outlineAlpha);
    vec3 finalColor = mix(outlineColor, textColor, alpha / finalAlpha);
    
    color = vec4(finalColor, finalAlpha);
}
)";


 struct TextRendererInline {
    GLuint VAO, VBO[2], EBO;
    GLuint shaderProgram;
    GLuint texture;
    stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
} ;

struct PrintTextString {
	char * szText;
	int iLength;
	int iID;
	
};
static int iShaderOK = 0;
// file:///D:/games_src/DGregorius_GDC2013/Gregorius_Dirk_TheSeparatingAxisTest.pdf

void checkShaderCompilation(GLuint shader) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Shader compilation failed: %s\n", infoLog);
    }
	else
	{
		iShaderOK++;
		  printf("Shader compilation OK!: %d\n", iShaderOK);
	}
}


TextRendererInline rendererSTBText;

int g_iTextDebug = 0;;

TextRendererInline initTextrendererSTBText(const char* fontPath, float fontSize) {
   // TextrendererSTBText rendererSTBText;
    
    // Load font file
   // unsigned char* ttf_buffer = (unsigned char*)malloc(1<<20);
   unsigned char ttf_buffer[1<<20];
    unsigned char temp_bitmap[512*512];
    printf("initTextrendererSTBText");
	
    FILE* f = fopen(fontPath, "rb");
    if (!f) {
        printf("Failed to open font file\n");
        exit(1);
    }
    fread(ttf_buffer, 1, 1<<20, f);
    fclose(f);
    printf("stbtt_BakeFontBitmap");
    // Bake font atlas
    stbtt_BakeFontBitmap(ttf_buffer, 0, fontSize, temp_bitmap, 512, 512, 32, 95, rendererSTBText.cdata);
	// 96 characters = about 3 lines thats 0.162109375 * 100 %
	// 6.1686746987951807228915662650602
	// can fit 96* 6 in a 512x512 texture
	
    //free(ttf_buffer);
	if(g_iTextDebug)
	{
for(int l = 0 ; l < 95; l++)
{
	/*
	typedef struct
{
   unsigned short x0,y0,x1,y1; // coordinates of bbox in bitmap
   float xoff,yoff,xadvance;
} stbtt_bakedchar;

	*/
	
	printf("l: %d rendererSTBText.cdata.x0: %d, rendererSTBText.cdata.x1 %d , rendererSTBText.cdata.y0 %d, rendererSTBText.cdata.y1 %d , rendererSTBText.cdata.xoff %f , rendererSTBText.cdata.yoff %f , rendererSTBText.cdata.xadvance %f\n\n", l, 
	rendererSTBText.cdata[l].x0 , rendererSTBText.cdata[l].x1 , rendererSTBText.cdata[l].y0 , rendererSTBText.cdata[l].y1 , rendererSTBText.cdata[l].xoff, rendererSTBText.cdata[l].yoff,  rendererSTBText.cdata[l].xadvance );
	
}
}
    // Create texture
    glGenTextures(1, &rendererSTBText.texture);
    glBindTexture(GL_TEXTURE_2D, rendererSTBText.texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    printf("Setup Text shaders");
    // Setup shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource140, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilation(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource140, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader);

 rendererSTBText.shaderProgram = linkProgramTextTemp(vertexShader, fragmentShader);




saveTexture(rendererSTBText.texture, 512,512 , "fonttexture.png");
	// Enable blending
   // glEnable(GL_BLEND);

    // Set the blending function
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 //  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

}

PrintTextString *newPrintObjectSomeText = NULL;
int iIndexSetup = 0;

PrintTextString *newPrintObjectSomeText2 = NULL;
int iIndexSetup2 = 0;


void makeText(const char* text, float x, float y, float scale, float r, float g, float b )
{
//	PrintTextString newPrintObject;
	PrintTextString *newPrintObject;
	// sizeof(struct Person)
	newPrintObject = (PrintTextString*) malloc(sizeof( struct PrintTextString));
	newPrintObject->iLength =  strlen(text);
	newPrintObject->iID = 0;
	int textLength = strlen(text) + 1;
	
	newPrintObject->szText = (char*)malloc( textLength);
	
	strcpy(newPrintObject->szText,text);
	
	
	newPrintObjectSomeText = newPrintObject;
	
	// float Text_Vertices2[16];
std::vector<float> Text_Vertices3;
std::vector<float> Text_Vertices4;	
    unsigned int indices[] = {0, 1, 3, 1, 2, 3};
int tcounter =0;
float xOffSet = 0.0f;
float yOffSet = 0.0f;
//    xOffSet += spaceWidth;

  float spaceWidth = 10.0f * scale;  // Define space width as per your requirements
            
			
xOffSet += x;
yOffSet += y;
int iCounter =0;
int iLengthStr =  strlen(text) ;

    while (*text && iCounter < iLengthStr) {
		iCounter++;
		
	  //  while (tcounter < 4) {
       // if (*text >= 32 && *text < 128) {
		if (*text > 32 && *text < 127) {
            stbtt_aligned_quad q;
		///	Details of ASCII Value for Space

//Decimal: 32
		
float xpos = x;
            stbtt_GetBakedQuad(rendererSTBText.cdata, 512, 512, *text-32, &xpos, &y, &q, 1);
	//	printf("renderText4\n\n");	
	if(g_iTextDebug)
	{
	printf("stbtt_GetBakedQuad *text: %c xpos: %d y: %d, q.s0: %d\n\n", *text, xpos,y,q.s0);
	}
			
		//	Text_Vertices2[0] = q.x0 * scale; Text_Vertices2[1] = q.y0 * scale; Text_Vertices2[2] = q.s0; Text_Vertices2[3] = q.t0;
		//	Text_Vertices2[4] = q.x1 * scale; Text_Vertices2[5] = q.y0 * scale; Text_Vertices2[6] = q.s1; Text_Vertices2[7] = q.t0;
		//	Text_Vertices2[8] = q.x1 * scale; Text_Vertices2[9] = q.y1 * scale; Text_Vertices2[10] = q.s1; Text_Vertices2[11] = q.t1;
		//	Text_Vertices2[12] = q.x0 * scale; Text_Vertices2[13] = q.y1 * scale; Text_Vertices2[14] = q.s0; Text_Vertices2[15] = q.t1;
		
	// /	 Text_Vertices3.push_back(q.x0 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
	// /	 Text_Vertices3.push_back(q.x1 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t0);
	// /	 Text_Vertices3.push_back(q.x1 * scale);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
	// /	 Text_Vertices3.push_back(q.x0 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t1);
		 
	//	 if(iIndexSetup == 0)
	//	 {
		/*
Setup shadersShader compilation OK!: 1
Shader compilation OK!: 2
stbtt_GetBakedQuad *text: H xpos: 1610612736 y: 0, q.s0: 0                                                       0.052734375     
                                                                                    0.12890625     0.16015625     0.05859375   0.095703125
Text_Vertices3  q.x0 2.000000, q.x1 18.000000, q.y0 -20.000000, q.y1 0.000000, q.s0 0.130859, q.s1 0.162109, q.t0 0.056641, q.t1 0.095703
Text_Vertices3scale  q.x0 0.040000, q.x1 0.360000, q.y0 -0.400000, q.y1 0.000000, q.s0 0.130859, q.s1 0.162109, q.t0 0.056641, q.t1 0.095703

stbtt_GetBakedQuad *text: e xpos: 1073741824 y: 0, q.s0: 0

Text_Vertices3  q.x0 1.000000, q.x1 15.000000, q.y0 -15.000000, q.y1 1.000000, q.s0 0.031250, q.s1 0.058594, q.t0 0.111328, q.t1 0.142578
Text_Vertices3scale  q.x0 0.020000, q.x1 0.300000, q.y0 -0.300000, q.y1 0.020000, q.s0 0.031250, q.s1 0.058594, q.t0 0.111328, q.t1 0.142578

stbtt_GetBakedQuad *text: l xpos: 536870912 y: 0, q.s0: 0

Text_Vertices3  q.x0 2.000000, q.x1 5.000000, q.y0 -21.000000, q.y1 0.000000, q.s0 0.195312, q.s1 0.201172, q.t0 0.111328, q.t1 0.152344
Text_Vertices3scale  q.x0 0.040000, q.x1 0.100000, q.y0 -0.420000, q.y1 0.000000, q.s0 0.195312, q.s1 0.201172, q.t0 0.111328, q.t1 0.152344

stbtt_GetBakedQuad *text: l xpos: 536870912 y: 0, q.s0: 0

Text_Vertices3  q.x0 2.000000, q.x1 5.000000, q.y0 -21.000000, q.y1 0.000000, q.s0 0.195312, q.s1 0.201172, q.t0 0.111328, q.t1 0.152344
Text_Vertices3scale  q.x0 0.040000, q.x1 0.100000, q.y0 -0.420000, q.y1 0.000000, q.s0 0.195312, q.s1 0.201172, q.t0 0.111328, q.t1 0.152344

stbtt_GetBakedQuad *text: o xpos: 1610612736 y: 0, q.s0: 0

Text_Vertices3  q.x0 1.000000, q.x1 15.000000, q.y0 -15.000000, q.y1 1.000000, q.s0 0.275391, q.s1 0.302734, q.t0 0.111328, q.t1 0.142578
Text_Vertices3scale  q.x0 0.020000, q.x1 0.300000, q.y0 -0.300000, q.y1 0.020000, q.s0 0.275391, q.s1 0.302734, q.t0 0.111328, q.t1 0.142578

stbtt_GetBakedQuad *text: L xpos: 1073741824 y: 0, q.s0: 0

Text_Vertices3  q.x0 2.000000, q.x1 15.000000, q.y0 -20.000000, q.y1 0.000000, q.s0 0.238281, q.s1 0.263672, q.t0 0.056641, q.t1 0.095703
Text_Vertices3scale  q.x0 0.040000, q.x1 0.300000, q.y0 -0.400000, q.y1 0.000000, q.s0 0.238281, q.s1 0.263672, q.t0 0.056641, q.t1 0.095703

*/
/*
std::vector<float> vertices1 = {                                            //3 _____2
    -0.5f, -0.5f, 0.0f,  // Bottom-left  (Vertex 1) 0  Lower left corner       |   /
     0.6f,  0.6f, 0.0f,  // Bottom-right (Vertex 2) 2 Upper right corner       |  / 
    -0.5f,  0.5f, 0.0f,  // Top-left     (Vertex 3) 1 Upper left corner        |1/
	                                                                        //    /|6
     -0.5f,  -0.5f, 0.0f,   // Top-right    (Vertex 4)  //0 Lower left corner    / |
	  0.5f,  -0.5f, 0.0f ,  // Top-right    (Vertex 5)  //3 Lower right corner  /  |
	   0.6f,  0.6f, 0.0f   // Top-right    (Vertex 6)  //2 Upper right corner  /4__|5
};
*/

//q.x0 += xOffSet;
//q.x1 += xOffSet;
/*
		 Text_Vertices3.push_back(q.x0 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back(q.x1 * scale);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
		 Text_Vertices3.push_back(q.x0 * scale);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t1);
		

		Text_Vertices3.push_back(q.x0 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		
		 Text_Vertices3.push_back(q.x1 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back(q.x1 * scale);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
	*/
	
	// OLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLD
	/*
	Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
		 Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t1);
		

		Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
	*/
	// OLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLD
	/*
	Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t0);
		

		Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
		
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t1);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
	*/
	float yEnglishDraw = (q.y1 * scale) - (q.y0 * scale);
	
		Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back( yEnglishDraw + yOffSet);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(0 + yOffSet);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
		 Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(0 + yOffSet);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t1);
		

		Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back( yEnglishDraw + yOffSet);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back( yEnglishDraw + yOffSet);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(0 + yOffSet);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
	
	float xTotalDifference = (q.x1 * scale) - (q.x0 * scale );
		
		xOffSet += xTotalDifference;
		 
		 
	/*
	  // LEVEL
	  
	  -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY,  0.0f, 0.0f, 1.0f, //0 Lower left corner
	 0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner
	 -0.9f,  0.9f, 0.0f,     0.0f, 1.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //1 Upper left corner
	
	
	 -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f, //0 Lower left corner
	
	0.9f, -0.9f, 0.0f,     1.0f, 1.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f,  //3 Lower right corner
	  0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner

	*/
	//-0.9f, -0.9f,	LEVEL1STARTX, LEVEL1STARTY,   //0 Lower left corner
	// 0.9f,  0.9f, 	LEVEL1ENDX, LEVEL1ENDY, //2 Upper right corner
	// -0.9f,  0.9f, 	LEVEL1STARTX, LEVEL1ENDY,//1 Upper left corner
//	 -0.9f, -0.9f, 	LEVEL1STARTX, LEVEL1STARTY, //0 Lower left corner
	 
	// 0.9f, -0.9f, 	LEVEL1ENDX, LEVEL1STARTY,  //3 Lower right corner
	 // 0.9f,  0.9f, 	LEVEL1ENDX, LEVEL1ENDY, //2 Upper right corner
		/*
		typedef struct
{
   float x0,y0,s0,t0; // top-left
   float x1,y1,s1,t1; // bottom-right
} stbtt_aligned_quad;*/

		
		
	//	 }
		 if(g_iTextDebug)
	{
		 printf("Text_Vertices3  q.x0 %f, q.x1 %f, q.y0 %f, q.y1 %f, q.s0 %f, q.s1 %f, q.t0 %f, q.t1 %f\n", q.x0, q.x1, q.y0, q.y1, q.s0, q.s1, q.t0, q.t1);
     printf("Text_Vertices3scale  q.x0 %f, q.x1 %f, q.y0 %f, q.y1 %f, q.s0 %f, q.s1 %f, q.t0 %f, q.t1 %f\n\n", q.x0* scale, q.x1* scale, q.y0* scale, q.y1 * scale, q.s0, q.s1, q.t0, q.t1);
	}
//std::vector<unsigned int> indices = {
//    0, 1, 2,  // First triangle
   // 0, 2, 3   // Second triangle
//};
	

		
		

       
			
						
			
			tcounter++;
        }
		else  if (*text == ' ') {  // Handle the space character
          //  float spaceWidth = 10.0f * scale;  // Define space width as per your requirements
         // xOffSet = x;
		 Text_Vertices3.push_back(0 + xOffSet);  Text_Vertices3.push_back(y + (spaceWidth * 1.5) );  Text_Vertices4.push_back( 1.0f); Text_Vertices4.push_back( 1.0f );
		 Text_Vertices3.push_back(spaceWidth + xOffSet);  Text_Vertices3.push_back(y);  Text_Vertices4.push_back( 1.0f ); Text_Vertices4.push_back( 1.0f );
		 Text_Vertices3.push_back( 0 + xOffSet);  Text_Vertices3.push_back(y );  Text_Vertices4.push_back( 1.0f ); Text_Vertices4.push_back( 1.0f );
		

		Text_Vertices3.push_back( 0 + xOffSet);  Text_Vertices3.push_back( y + (spaceWidth * 1.5)  );  Text_Vertices4.push_back( 1.0f ); Text_Vertices4.push_back( 1.0f );
		
		 Text_Vertices3.push_back( spaceWidth + xOffSet);  Text_Vertices3.push_back( y + (spaceWidth * 1.5)  );  Text_Vertices4.push_back( 1.0f ); Text_Vertices4.push_back( 1.0f );
		 Text_Vertices3.push_back( spaceWidth + xOffSet);  Text_Vertices3.push_back( y );  Text_Vertices4.push_back( 1.0f ); Text_Vertices4.push_back( 1.0f );
	

		   xOffSet += spaceWidth;
		   tcounter++;
        } 
        ++text;
    }
	
//	glBindBuffer(GL_ARRAY_BUFFER, rendererSTBText.VBO);
 //          glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
 //           glEnableVertexAttribArray(0);
	
	//     glBindBuffer(GL_ARRAY_BUFFER, rendererSTBText.VBO);
  //          glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  //          glEnableVertexAttribArray(1);
			
	// glBufferData(GL_ARRAY_BUFFER, Text_Vertices3.size()   * sizeof(float), Text_Vertices3.data(), GL_STREAM_DRAW);
	
	    // Vertex positions
		
		 glGenVertexArrays(1, &rendererSTBText.VAO);
    glBindVertexArray(rendererSTBText.VAO);
		
		    glGenBuffers(2, rendererSTBText.VBO);
			
    glBindBuffer(GL_ARRAY_BUFFER, rendererSTBText.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, Text_Vertices3.size() * sizeof(float), Text_Vertices3.data(), GL_STATIC_DRAW);
 //   glBufferData(GL_ARRAY_BUFFER, Text_Vertices3.size()/2 * sizeof(float), Text_Vertices3.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, rendererSTBText.VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, Text_Vertices4.size() * sizeof(float), Text_Vertices4.data(), GL_STATIC_DRAW);
 //   glBufferData(GL_ARRAY_BUFFER, Text_Vertices3.size()/2 * sizeof(float), Text_Vertices3.data(), GL_STATIC_DRAW);
   // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),  (void*)0);
   
    glEnableVertexAttribArray(1);
	
	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
    glBindVertexArray(0);
	
}



void makeTextHindi(const char* text, float x, float y, float scale, float r, float g, float b )
{
	
	for(int i =0 ; i < (strlen(text) + 1/ 3) ; i+= 3)
	{
		printf("text[0]: %x,text[1]: %x,text[2]: %x\n",text[i],text[i+1],text[i+2]);
		
	}
	for (int i = 0; i < strlen(text); i += 3) {
    printf("text[0]: %x, text[1]: %x, text[2]: %x\n",
           (unsigned char)text[i],
           (i + 1 < strlen(text)) ? (unsigned char)text[i + 1] : 0,
           (i + 2 < strlen(text)) ? (unsigned char)text[i + 2] : 0);
}


	//printf("Hindi Text Length: %d", strlen(text) + 1);
	
	//exit(0);
	
	
	   glBindVertexArray(0);
	   
//	PrintTextString newPrintObject;
	PrintTextString *newPrintObject;
	// sizeof(struct Person)
	newPrintObject = (PrintTextString*) malloc(sizeof( struct PrintTextString));
	newPrintObject->iLength =  strlen(text);
	newPrintObject->iID = 0;
	int textLength = strlen(text) + 1;
	int textLengthNatural = strlen(text) ;
	
	newPrintObject->szText = (char*)malloc( textLength);
	
	strcpy(newPrintObject->szText,text);
	
	
	newPrintObjectSomeText2 = newPrintObject;
	
	// float Text_Vertices2[16];
std::vector<float> Text_Vertices3;
std::vector<float> Text_Vertices4;	
    unsigned int indices[] = {0, 1, 3, 1, 2, 3};
int tcounter =0;
int tcounter2 =0;
// https://archive.org/details/msdos_Montezumas_Revenge_1984
float xOffSet = 0.0f;
float yOffset = 0.0f;
xOffSet += x;
yOffset += y;

    while (*text && tcounter < (textLengthNatural /3) ) {
	  //  while (tcounter < 4) {
     //   if (*text >= 32 && *text < 128)
		 {
            stbtt_aligned_quad q;
		///	Details of ASCII Value for Space

//Decimal: 32
		
float xpos = x;

			//(unsigned char)text[i],
          // (i + 1 < strlen(text)) ? (unsigned char)text[i + 1] : 0,
          // (i + 2 < strlen(text)) ? (unsigned char)text[i + 2] : 0);
		  int iTempHigher = (unsigned char)text[tcounter2 + 1] - 0xa5;
		  // 164
		   int textValue =   (unsigned char)text[tcounter2 + 2]  +(iTempHigher * 128);
		   
		   
      //      stbtt_GetBakedQuad(rendererSTBTextHindi.cdata, 512, 512, *text-2304, &xpos, &y, &q, 1);
	   stbtt_GetBakedQuad(rendererSTBTextHindi.cdata, 512, 512,textValue, &xpos, &y, &q, 1);
	  printf("Hindi maketext textValue: %d\n\n",  textValue);
	//	printf("Hindi maketext renderText4 *text:%c %d textValue: %d\n\n", text[tcounter] , text[tcounter], textValue);	
	//printf("stbtt_GetBakedQuad *text: %c xpos: %d y: %d, q.s0: %d\n\n", *text, xpos,y,q.s0);

			
		//	Text_Vertices2[0] = q.x0 * scale; Text_Vertices2[1] = q.y0 * scale; Text_Vertices2[2] = q.s0; Text_Vertices2[3] = q.t0;
		//	Text_Vertices2[4] = q.x1 * scale; Text_Vertices2[5] = q.y0 * scale; Text_Vertices2[6] = q.s1; Text_Vertices2[7] = q.t0;
		//	Text_Vertices2[8] = q.x1 * scale; Text_Vertices2[9] = q.y1 * scale; Text_Vertices2[10] = q.s1; Text_Vertices2[11] = q.t1;
		//	Text_Vertices2[12] = q.x0 * scale; Text_Vertices2[13] = q.y1 * scale; Text_Vertices2[14] = q.s0; Text_Vertices2[15] = q.t1;
		
	// /	 Text_Vertices3.push_back(q.x0 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
	// /	 Text_Vertices3.push_back(q.x1 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t0);
	// /	 Text_Vertices3.push_back(q.x1 * scale);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
	// /	 Text_Vertices3.push_back(q.x0 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t1);
		 
	//	 if(iIndexSetup == 0)
	//	 {
		/*
Setup shadersShader compilation OK!: 1
Shader compilation OK!: 2
stbtt_GetBakedQuad *text: H xpos: 1610612736 y: 0, q.s0: 0                                                       0.052734375     
                                                                                    0.12890625     0.16015625     0.05859375   0.095703125
Text_Vertices3  q.x0 2.000000, q.x1 18.000000, q.y0 -20.000000, q.y1 0.000000, q.s0 0.130859, q.s1 0.162109, q.t0 0.056641, q.t1 0.095703
Text_Vertices3scale  q.x0 0.040000, q.x1 0.360000, q.y0 -0.400000, q.y1 0.000000, q.s0 0.130859, q.s1 0.162109, q.t0 0.056641, q.t1 0.095703

stbtt_GetBakedQuad *text: e xpos: 1073741824 y: 0, q.s0: 0

Text_Vertices3  q.x0 1.000000, q.x1 15.000000, q.y0 -15.000000, q.y1 1.000000, q.s0 0.031250, q.s1 0.058594, q.t0 0.111328, q.t1 0.142578
Text_Vertices3scale  q.x0 0.020000, q.x1 0.300000, q.y0 -0.300000, q.y1 0.020000, q.s0 0.031250, q.s1 0.058594, q.t0 0.111328, q.t1 0.142578

stbtt_GetBakedQuad *text: l xpos: 536870912 y: 0, q.s0: 0

Text_Vertices3  q.x0 2.000000, q.x1 5.000000, q.y0 -21.000000, q.y1 0.000000, q.s0 0.195312, q.s1 0.201172, q.t0 0.111328, q.t1 0.152344
Text_Vertices3scale  q.x0 0.040000, q.x1 0.100000, q.y0 -0.420000, q.y1 0.000000, q.s0 0.195312, q.s1 0.201172, q.t0 0.111328, q.t1 0.152344

stbtt_GetBakedQuad *text: l xpos: 536870912 y: 0, q.s0: 0

Text_Vertices3  q.x0 2.000000, q.x1 5.000000, q.y0 -21.000000, q.y1 0.000000, q.s0 0.195312, q.s1 0.201172, q.t0 0.111328, q.t1 0.152344
Text_Vertices3scale  q.x0 0.040000, q.x1 0.100000, q.y0 -0.420000, q.y1 0.000000, q.s0 0.195312, q.s1 0.201172, q.t0 0.111328, q.t1 0.152344

stbtt_GetBakedQuad *text: o xpos: 1610612736 y: 0, q.s0: 0

Text_Vertices3  q.x0 1.000000, q.x1 15.000000, q.y0 -15.000000, q.y1 1.000000, q.s0 0.275391, q.s1 0.302734, q.t0 0.111328, q.t1 0.142578
Text_Vertices3scale  q.x0 0.020000, q.x1 0.300000, q.y0 -0.300000, q.y1 0.020000, q.s0 0.275391, q.s1 0.302734, q.t0 0.111328, q.t1 0.142578

stbtt_GetBakedQuad *text: L xpos: 1073741824 y: 0, q.s0: 0

Text_Vertices3  q.x0 2.000000, q.x1 15.000000, q.y0 -20.000000, q.y1 0.000000, q.s0 0.238281, q.s1 0.263672, q.t0 0.056641, q.t1 0.095703
Text_Vertices3scale  q.x0 0.040000, q.x1 0.300000, q.y0 -0.400000, q.y1 0.000000, q.s0 0.238281, q.s1 0.263672, q.t0 0.056641, q.t1 0.095703

*/
/*
std::vector<float> vertices1 = {                                            //3 _____2
    -0.5f, -0.5f, 0.0f,  // Bottom-left  (Vertex 1) 0  Lower left corner       |   /
     0.6f,  0.6f, 0.0f,  // Bottom-right (Vertex 2) 2 Upper right corner       |  / 
    -0.5f,  0.5f, 0.0f,  // Top-left     (Vertex 3) 1 Upper left corner        |1/
	                                                                        //    /|6
     -0.5f,  -0.5f, 0.0f,   // Top-right    (Vertex 4)  //0 Lower left corner    / |
	  0.5f,  -0.5f, 0.0f ,  // Top-right    (Vertex 5)  //3 Lower right corner  /  |
	   0.6f,  0.6f, 0.0f   // Top-right    (Vertex 6)  //2 Upper right corner  /4__|5
};
*/

//q.x0 += xOffSet;
//q.x1 += xOffSet;
/*
		 Text_Vertices3.push_back(q.x0 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back(q.x1 * scale);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
		 Text_Vertices3.push_back(q.x0 * scale);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t1);
		

		Text_Vertices3.push_back(q.x0 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		
		 Text_Vertices3.push_back(q.x1 * scale);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back(q.x1 * scale);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
	*/
	
	// OLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLD
	/*
	Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
		 Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t1);
		

		Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
	*/
	// OLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLDOLD
	/*
	Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t0);
		

		Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
		
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y0 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t1);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back(q.y1 * scale);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
	*/
	
		Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back((q.y1 * scale) +  yOffset);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back((q.y0 * scale) +  yOffset);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
		 Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back((q.y0 * scale) +  yOffset);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t1);
		

		Text_Vertices3.push_back((q.x0 * scale) + xOffSet);  Text_Vertices3.push_back((q.y1 * scale) +  yOffset);  Text_Vertices4.push_back( q.s0); Text_Vertices4.push_back( q.t0);
		
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back((q.y1 * scale) +  yOffset);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t0);
		 Text_Vertices3.push_back((q.x1 * scale) + xOffSet);  Text_Vertices3.push_back((q.y0 * scale) +  yOffset);  Text_Vertices4.push_back( q.s1); Text_Vertices4.push_back( q.t1);
	
	float xTotalDifference = (q.x1 * scale) - (q.x0 * scale );
		
		xOffSet += xTotalDifference;
		 
		 
	/*
	  // LEVEL
	  
	  -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY,  0.0f, 0.0f, 1.0f, //0 Lower left corner
	 0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner
	 -0.9f,  0.9f, 0.0f,     0.0f, 1.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //1 Upper left corner
	
	
	 -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f, //0 Lower left corner
	
	0.9f, -0.9f, 0.0f,     1.0f, 1.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f,  //3 Lower right corner
	  0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner

	*/
	//-0.9f, -0.9f,	LEVEL1STARTX, LEVEL1STARTY,   //0 Lower left corner
	// 0.9f,  0.9f, 	LEVEL1ENDX, LEVEL1ENDY, //2 Upper right corner
	// -0.9f,  0.9f, 	LEVEL1STARTX, LEVEL1ENDY,//1 Upper left corner
//	 -0.9f, -0.9f, 	LEVEL1STARTX, LEVEL1STARTY, //0 Lower left corner
	 
	// 0.9f, -0.9f, 	LEVEL1ENDX, LEVEL1STARTY,  //3 Lower right corner
	 // 0.9f,  0.9f, 	LEVEL1ENDX, LEVEL1ENDY, //2 Upper right corner
		/*
		typedef struct
{
   float x0,y0,s0,t0; // top-left
   float x1,y1,s1,t1; // bottom-right
} stbtt_aligned_quad;*/

		
		
	//	 }
		 
		 printf("Hindi Text_Vertices3  q.x0 %f, q.x1 %f, q.y0 %f, q.y1 %f, q.s0 %f, q.s1 %f, q.t0 %f, q.t1 %f\n", q.x0, q.x1, q.y0, q.y1, q.s0, q.s1, q.t0, q.t1);
     printf("Hindi  Text_Vertices3scale  q.x0 %f, q.x1 %f, q.y0 %f, q.y1 %f, q.s0 %f, q.s1 %f, q.t0 %f, q.t1 %f\n\n", q.x0* scale, q.x1* scale, q.y0* scale, q.y1 * scale, q.s0, q.s1, q.t0, q.t1);
//std::vector<unsigned int> indices = {
//    0, 1, 2,  // First triangle
   // 0, 2, 3   // Second triangle
//};
	

		
		

       
			
						
			
			tcounter++;
			tcounter2+= 3;
        }
        // ++text;
			text+= 3;
    }
	
//	glBindBuffer(GL_ARRAY_BUFFER, rendererSTBText.VBO);
 //          glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
 //           glEnableVertexAttribArray(0);
	
	//     glBindBuffer(GL_ARRAY_BUFFER, rendererSTBText.VBO);
  //          glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  //          glEnableVertexAttribArray(1);
			
	// glBufferData(GL_ARRAY_BUFFER, Text_Vertices3.size()   * sizeof(float), Text_Vertices3.data(), GL_STREAM_DRAW);
	
	    // Vertex positions
		
		 glGenVertexArrays(1, &rendererSTBTextHindi.VAO);
    glBindVertexArray(rendererSTBTextHindi.VAO);
		
		
		    glGenBuffers(2, rendererSTBTextHindi.VBO);
			
    glBindBuffer(GL_ARRAY_BUFFER, rendererSTBTextHindi.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, Text_Vertices3.size() * sizeof(float), Text_Vertices3.data(), GL_STATIC_DRAW);
 //   glBufferData(GL_ARRAY_BUFFER, Text_Vertices3.size()/2 * sizeof(float), Text_Vertices3.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, rendererSTBTextHindi.VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, Text_Vertices4.size() * sizeof(float), Text_Vertices4.data(), GL_STATIC_DRAW);
 //   glBufferData(GL_ARRAY_BUFFER, Text_Vertices3.size()/2 * sizeof(float), Text_Vertices3.data(), GL_STATIC_DRAW);
   // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),  (void*)0);
   
    glEnableVertexAttribArray(1);
	
	
	
			    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
	
}


void renderText(TextRendererInline* renderer, const char* text, float x, float y, float scale, float r, float g, float b) {
  // renderer = rendererSTBText;

printf("renderText %s\n\n", text);
//for(int l = 0 ; l < 96; l++)
//{
	/*
	typedef struct
{
   unsigned short x0,y0,x1,y1; // coordinates of bbox in bitmap
   float xoff,yoff,xadvance;
} stbtt_bakedchar;

	*/
	//printf("l2: %d rendererSTBText.cdata.x0: %d, rendererSTBText.cdata.x1 %d, rendererSTBText.cdata.y0 %d, rendererSTBText.cdata.y1 %d , rendererSTBText.cdata.xoff %f , rendererSTBText.cdata.yoff %f , rendererSTBText.cdata.xadvance %f\n\n", l, 
//	rendererSTBText.cdata[l].x0 , rendererSTBText.cdata[l].x1 , rendererSTBText.cdata[l].y0 , rendererSTBText.cdata[l].y1 , rendererSTBText.cdata[l].xoff, rendererSTBText.cdata[l].yoff,  rendererSTBText.cdata[l].xadvance );
	
//}
 
 
 glBindVertexArray(0);
    glBindVertexArray(rendererSTBText.VAO);
   glUseProgram(rendererSTBText.shaderProgram);

   glBindTexture(GL_TEXTURE_2D, rendererSTBText.texture);
  
printf("renderText2\n\n");


    // Set uniforms
    float projection[16] = {
        2.0f/800.0f, 0, 0, -1,
        0, -2.0f/600.0f, 0, 1,
        0, 0, 1, 0,
        0, 0, 0, 1
    }; // Simple ortho projection for 800x600 window
    glUniformMatrix4fv(glGetUniformLocation(rendererSTBText.shaderProgram, "projection"), 1, GL_FALSE, projection);
    glUniform3f(glGetUniformLocation(rendererSTBText.shaderProgram, "textColor"), r, g, b);
printf("renderText3\n\n");
    float xpos = x;
   // float Text_Vertices[6][4];
    float Text_Vertices2[16];
	
    unsigned int indices[] = {0, 1, 3, 1, 2, 3};
int tcounter =0;
    //while (*text) {
	    while (tcounter < 4) {
        if (*text >= 32 && *text < 128) {
            stbtt_aligned_quad q;
			
		

            stbtt_GetBakedQuad(rendererSTBText.cdata, 512, 512, *text-32, &xpos, &y, &q, 1);
	//	printf("renderText4\n\n");	
	printf("stbtt_GetBakedQuad *text: %c xpos: %d y: %d, q.s0: %d\n\n", *text, xpos,y,q.s0);
/*
            Text_Vertices[0][0] = q.x0 * scale; Text_Vertices[0][1] = q.y0 * scale; Text_Vertices[0][2] = q.s0; Text_Vertices[0][3] = q.t0;
            Text_Vertices[1][0] = q.x1 * scale; Text_Vertices[1][1] = q.y0 * scale; Text_Vertices[1][2] = q.s1; Text_Vertices[1][3] = q.t0;
            Text_Vertices[2][0] = q.x1 * scale; Text_Vertices[2][1] = q.y1 * scale; Text_Vertices[2][2] = q.s1; Text_Vertices[2][3] = q.t1;
            Text_Vertices[3][0] = q.x0 * scale; Text_Vertices[3][1] = q.y1 * scale; Text_Vertices[3][2] = q.s0; Text_Vertices[3][3] = q.t1;
			
			*/
			
			
			Text_Vertices2[0] = q.x0 * scale; Text_Vertices2[1] = q.y0 * scale; Text_Vertices2[2] = q.s0; Text_Vertices2[3] = q.t0;
			Text_Vertices2[4] = q.x1 * scale; Text_Vertices2[5] = q.y0 * scale; Text_Vertices2[6] = q.s1; Text_Vertices2[7] = q.t0;
			Text_Vertices2[8] = q.x1 * scale; Text_Vertices2[9] = q.y1 * scale; Text_Vertices2[10] = q.s1; Text_Vertices2[11] = q.t1;
			Text_Vertices2[12] = q.x0 * scale; Text_Vertices2[13] = q.y1 * scale; Text_Vertices2[14] = q.s0; Text_Vertices2[15] = q.t1;
		
		
//printf("renderText5\n\n");
        //    glBindBuffer(GL_ARRAY_BUFFER, rendererSTBText.VBO);
           // glBufferSubData(GL_ARRAY_BUFFER, sizeof(Text_Vertices2), Text_Vertices2, GL_STREAM_DRAW);
		//   if(iDrawFirst == 0)
		//   {
		//	   glBufferData(GL_ARRAY_BUFFER, sizeof(Text_Vertices2), Text_Vertices2, GL_STREAM_DRAW);
		//	   iDrawFirst++;
		//   }
		//   else
		//   {
		//	    glBufferSubData(GL_ARRAY_BUFFER, sizeof(Text_Vertices2), 0, Text_Vertices2);
		 //  }
		//   glBufferSubData(GL_ARRAY_BUFFER, sizeof(Text_Vertices2), 0, Text_Vertices2);
		 glBufferData(GL_ARRAY_BUFFER, sizeof(Text_Vertices2), Text_Vertices2, GL_STREAM_DRAW);
	//		printf("renderText6\n\n");
            /*
			    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices2), SPRITEBLOCKSIZE * (MAX_BOXES + 8), vertices_dynamic_original);


//	vertices_dynamic_original[0] = CutX3; // test boxes update
	
    glBindBuffer(GL_ARRAY_BUFFER, 0);
			*/
         //   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererSTBText.EBO);
         //   glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
   // glBindBuffer(GL_ARRAY_BUFFER, rendererSTBText.VBO);
       glBindBuffer(GL_ARRAY_BUFFER, rendererSTBText.VBO[0]);
           glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
		//	printf("renderText7\n\n");
	//		    glBindBuffer(GL_ARRAY_BUFFER, rendererSTBText.VBO);
	     glBindBuffer(GL_ARRAY_BUFFER, rendererSTBText.VBO[1]);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);
			
			
			    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
			
			
			
//printf("\n glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); %d ", tcounter++);
//printf("renderText8\n\n");
    glDrawArrays(GL_TRIANGLES, 0, 4);
 // printf("renderText9\n\n");
          //  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			tcounter++;
        }
        ++text;
    }
	tcounter =0 ;
//	printf("TEXT RENDER STB TRUETYPE END");
	
}


void initText1()
{ 

//SetupFont2("NotoSansSC-VariableFont_wght.ttf"); 

// 
//SetupFont("assets/fonts/Noto_Sans_Devanagari-Noto_Sans_SC/Noto_Sans_Devanagari/NotoSansDevanagari-VariableFont_wdth-wght.ttf");
initTextrendererSTBText("arial.ttf", 32.0f); 
 //initTextrendererSTBText("NotoSansSC-VariableFont_wght.ttf", 32.0f); 
//SetupFont("NotoSansSC-VariableFont_wght.ttf");
	//  initTextrendererSTBText("verdana.ttf", 32.0f); 
	 
	//  initTextrendererSTBTextHindi("NotoSansSC-VariableFont_wght.ttf", 32.0f); 
	
	// arial.ttf
	//SetupFont("arial.ttf");
	//initTextrendererSTBTextHindi("assets/fonts/Noto_Sans_Devanagari-Noto_Sans_SC/Noto_Sans_Devanagari/NotoSansDevanagari-VariableFont_wdth-wght.ttf", 32.0f); 
	  printf("initTextrendererSTBTextHindi end \n\r");
	  
}	
// F Devanagari 0
// 0900 Devanagari 097F

// Function to create an orthographic projection matrix for 2D text rendering
void createOrthoMatrix(float *matrix, float left, float right, float bottom, float top) {
    // Zero out the matrix
    for (int i = 0; i < 16; i++) matrix[i] = 0.0f;

    // Set up orthographic projection (column-major order for OpenGL)
    matrix[0]  = 2.0f / (right - left); // Scale X
    matrix[5]  = 2.0f / (top - bottom); // Scale Y
    matrix[10] = -1.0f;                 // Z depth (simple 2D, no scaling)
    matrix[12] = -(right + left) / (right - left); // Translate X
    matrix[13] = -(top + bottom) / (top - bottom); // Translate Y
    matrix[15] = 1.0f;                  // Homogeneous coordinate
}
	// Function to print a 4x4 matrix
void printMatrix(float *matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%8.3f ", matrix[i * 4 + j]);
        }
        printf("\n");
    }
	 printf("\n");
	  printf("\n");
}

 // static constexpr float kProjectionHalfHeight = 2.0f ; // zoomed out
 static constexpr float kProjectionHalfHeight = 1.f; //normal zoom
//static constexpr float kProjectionHalfHeight = 0.5f;  // zoomed in

/*!
 * The near plane distance for the projection matrix. Since this is an orthographic projection
 * matrix, it's convenient to have negative values for sorting (and avoiding z-fighting at 0).
 */
static constexpr float kProjectionNearPlane = -1.f;

/*!
 * The far plane distance for the projection matrix. Since this is an orthographic porjection
 * matrix, it's convenient to have the far plane equidistant from 0 as the near plane.
 */
static constexpr float kProjectionFarPlane = 1.f;
	
void drawTextColo()
{
	//glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
   // Draw first object
 // glBindVertexArray(vao1);
  glBindVertexArray(rendererSTBText.VAO);
    glUseProgram(rendererSTBText.shaderProgram);

   glBindTexture(GL_TEXTURE_2D, rendererSTBText.texture);
  float r = 0.7f;
float g = 0.7f;
float b = 0.7f;
      float projection[16] = {
     //   2.0f/800.0f, 0, 0, -1,
      //  0, -2.0f/600.0f, 0, 1,
	  
	     2.0f/800.0f, 0, 0, 0,
        0, -2.0f/600.0f, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }; // Simple ortho projection for 800x600 window
	
	//createOrthoMatrix(projection, 0.0f, 800.0f, 0.0f, 600.0f);
     Utility::buildOrthographicMatrix(
                projection,
                kProjectionHalfHeight,
                float(g_Width) / g_Height,  // aspect
                kProjectionNearPlane,
                kProjectionFarPlane);
				
				
    // Print the matrix for verification
   // printf("Orthographic Matrix for Text Rendering:\n");
   // printMatrix(projection);
	
	
    glUniformMatrix4fv(glGetUniformLocation(rendererSTBText.shaderProgram, "projection"), 1, GL_FALSE, projection);
	// glUniformMatrix4fv(uProjection, 1, false, projectionMatrix);
	
    glUniform3f(glGetUniformLocation(rendererSTBText.shaderProgram, "textColor"), r, g, b);
  
  
 //^^^^   glDrawArrays(GL_TRIANGLES, 0, newPrintObjectSomeText->iLength * 4);
  // glDrawArrays(GL_TRIANGLES, 0, 4);
glDrawArrays(GL_TRIANGLES, 0, newPrintObjectSomeText->iLength * 6);
    //renderText(&rendererSTBText, "HelloL", 100.0f, 300.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	 
    glBindVertexArray(0);
	    glUseProgram(0);
}


void drawTextColoHindi()
{
	//glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

    // Draw first object
 // glBindVertexArray(vao1);
  // printf("  glBindVertexArray(rendererSTBTextHindi.VAO)\n\n");
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glBindVertexArray(rendererSTBTextHindi.VAO);
   // glUseProgram(rendererSTBTextHindi.shaderObject.shaderProgram);
 //  void ShaderTextTempHindi::activate() const {
 //   glUseProgram(program_);
//}

// printf("  rendererSTBTextHindi.shaderObject->activate() %d\n\n",rendererSTBTextHindi.shaderObject.get());
 
rendererSTBTextHindi.shaderObject->activate();
// rendererSTBTextHindi.GetShaderID();

 //printf(" glBindTexture(GL_TEXTURE_2D, rendererSTBTextHindi.texture);\n\n");
  

   glBindTexture(GL_TEXTURE_2D, rendererSTBTextHindi.texture);
   
  float r = 0.7f;
float g = 0.7f;
float b = 0.7f;
      float projection[16] = {
     //   2.0f/800.0f, 0, 0, -1,
      //  0, -2.0f/600.0f, 0, 1,
	  
	     2.0f/g_Width, 0, 0, 0,
        0, -2.0f/g_Height, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }; // Simple ortho projection for 800x600 window
	
	//createOrthoMatrix(projection, 0.0f, 800.0f, 0.0f, 600.0f);
  
 //printf(" Utility::buildOrthographicMatrix(;\n\n");
 
  Utility::buildOrthographicMatrix(
                projection,
                kProjectionHalfHeight,
                float(g_Width) / g_Height,  // aspect
                kProjectionNearPlane,
                kProjectionFarPlane);
				
				
    // Print the matrix for verification
  //  printf("Orthographic Matrix for Text Rendering:\n");
   // printMatrix(projection);
	
	
   // glUniformMatrix4fv(glGetUniformLocation(rendererSTBText.shaderProgram, "projection"), 1, GL_FALSE, projection);
	// glUniformMatrix4fv(uProjection, 1, false, projectionMatrix);
	
  //  glUniform3f(glGetUniformLocation(rendererSTBText.shaderProgram, "textColor"), r, g, b);
  // void setProjectionMatrix(float *projectionMatrix) const;
//	 void setTextureID(GLint TextureIDD) const;
 // void setTextColor(float r, float g, float b) const;
 //printf(" rendererSTBTextHindi.shaderObject->setProjectionMatrix\n\n");
 
  rendererSTBTextHindi.shaderObject->setProjectionMatrix(projection);
  //printf("  rendererSTBTextHindi.shaderObject->setTextColor\n\n");
 
  rendererSTBTextHindi.shaderObject->setTextColor( r, g, b);
  //  printf("  rendererSTBTextHindi::glDrawArrays \n\n");
 
 //^^^^   glDrawArrays(GL_TRIANGLES, 0, newPrintObjectSomeText->iLength * 4);
  // glDrawArrays(GL_TRIANGLES, 0, 4);
glDrawArrays(GL_TRIANGLES, 0, newPrintObjectSomeText2->iLength * 6);
    //renderText(&rendererSTBText, "HelloL", 100.0f, 300.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	 
    glBindVertexArray(0);
	    glUseProgram(0);
		// printf("  rendererSTBTextHindi::end \n\n");
 
}

// हाय वर्ल्ड
	

// Globals for VAOs and VBOs
GLuint vao1, vbo1;
GLuint vao2, vbo2;

 std::vector<float> vertices2;

void initBuffers() {
	
	
	
    // --- Setup VAO 1 ---
    glGenVertexArrays(1, &vao1);
    glBindVertexArray(vao1);

std::vector<float> vertices1 = {                                            //3 _____2
    -0.5f, -0.5f, 0.0f,  // Bottom-left  (Vertex 1) 0  Lower left corner       |   /
     0.6f,  0.6f, 0.0f,  // Bottom-right (Vertex 2) 2 Upper right corner       |  / 
    -0.5f,  0.5f, 0.0f,  // Top-left     (Vertex 3) 1 Upper left corner        |1/
	                                                                        //    /|6
     -0.5f,  -0.5f, 0.0f,   // Top-right    (Vertex 4)  //0 Lower left corner    / |
	  0.5f,  -0.5f, 0.0f ,  // Top-right    (Vertex 5)  //3 Lower right corner  /  |
	   0.6f,  0.6f, 0.0f   // Top-right    (Vertex 6)  //2 Upper right corner  /4__|5
};
/*
   // LEVEL
	  
	  -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY,  0.0f, 0.0f, 1.0f, //0 Lower left corner
	 0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner
	 -0.9f,  0.9f, 0.0f,     0.0f, 1.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //1 Upper left corner
	 
	 -0.9f, -0.9f, 0.0f,     1.0f, 0.0f, 0.0f,0.0f,	LEVEL1STARTX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f, //0 Lower left corner
	 0.9f, -0.9f, 0.0f,     1.0f, 1.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1STARTY, 0.0f, 0.0f, 1.0f,  //3 Lower right corner
	  0.9f,  0.9f, 0.0f,     0.0f, 0.0f, 1.0f,0.0f,	LEVEL1ENDX, LEVEL1ENDY, 0.0f, 0.0f, 1.0f, //2 Upper right corner

*/
    std::vector<float> colors1 = {
        0.5f, 0.5f, 0.0f,  // Color 1
        0.5f, 0.0f, 0.0f,  // Color 2
        0.0f, 0.5f, 0.0f,  // Color 3
        0.5f, 0.0f, 0.5f ,  // Color 4 (added to match vertex count)
		   0.5f, 0.3f, 0.5f ,  // Color 4 (added to match vertex count)
		      0.5f, 0.7f, 0.5f   // Color 4 (added to match vertex count)
    };
    std::vector<float> uv1 = {
        0.0f, 0.0f,  // UV 1 (2D coordinates)
        0.5f, 0.5f,  // UV 2
        0.0f, 0.5f,  // UV 3
		
        0.0f, 0.0f ,  // UV 4 (corrected to 2D)
		   0.5f, 0.0f,   // UV 4 (corrected to 2D)
		      0.5f, 0.5f   // UV 4 (corrected to 2D)
    };

    // Generate separate VBOs for each attribute
    GLuint vbo1[3];  // Array for 3 buffer objects
    glGenBuffers(3, vbo1);

    // Vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices1.size() * sizeof(float), vertices1.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);
    glBufferData(GL_ARRAY_BUFFER, colors1.size() * sizeof(float), colors1.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // UV coordinates
    glBindBuffer(GL_ARRAY_BUFFER, vbo1[2]);
    glBufferData(GL_ARRAY_BUFFER, uv1.size() * sizeof(float), uv1.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
	




    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // --- Setup VAO 2 ---
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);

    //= {
   //     -0.5f,  0.0f, 0.0f,  // Vertex 1
    //     0.5f,  0.0f, 0.0f,  // Vertex 2
   //      0.0f, -0.5f, 0.0f ,  // Vertex 3
		 
	//	 0.5f,  0.0f, 0.0f,  // Vertex 4
    //    -0.5f,  0.0f, 0.0f,  // Vertex 5
    //     0.0f, 0.5f, 0.0f   // Vertex 6
		 vertices2.push_back(-0.5f);  vertices2.push_back(0.0f);  vertices2.push_back(0.0f);
		 vertices2.push_back(0.5f);  vertices2.push_back(0.0f);  vertices2.push_back(0.0f);
		 vertices2.push_back(0.0f);  vertices2.push_back(-0.5f);  vertices2.push_back(0.0f);
		 
		  vertices2.push_back(0.5f);  vertices2.push_back(0.0f);  vertices2.push_back(0.0f);
		  vertices2.push_back(-0.5f);  vertices2.push_back(0.0f);  vertices2.push_back(0.0f);
		   vertices2.push_back(0.0f);  vertices2.push_back(0.5f);  vertices2.push_back(0.0f);
   // };

    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(float), vertices2.data(), GL_STREAM_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void render() {
	
	
    glClear(GL_COLOR_BUFFER_BIT);
	
		 renderGrid( gridSHADER );
	
	  if (mIsFirstFrame) {
    mIsFirstFrame = false;
  //  mgr->RequestNewScene(new DemoScene());
    mgr->RequestNewScene(new LoaderScene());
//	  mgr->DoFrame();
  mgr->StartGraphics();
  }

  // render!
  mgr->DoFrame();
	
	
	//renderSprites(spritesSHADER); // FIX
	//renderSprites2(spritesSHADER); // FIX
glColor4f(0.0f, 0.5f, 1.0f, 1.0f);
// makeText ( "HelloL", 100.0f, 300.0f, 1.0f, 1.0f, 1.0f, 1.0f);
   // renderText(&rendererSTBText, "HelloL", 100.0f, 300.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	 
	 
	
   //glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

    // Draw first object
  //  glBindVertexArray(vao1);
   // glDrawArrays(GL_TRIANGLES, 0, 6);


      glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	  
    // Draw second object
    glBindVertexArray(vao2);
    glDrawArrays(GL_LINES, 0, 2);
	 glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	 glDrawArrays(GL_LINES, 2, 4);
	  glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	 glDrawArrays(GL_LINES, 4, 6);
	
    //renderText(&rendererSTBText, "HelloL", 100.0f, 300.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	//renderGridPoints( gridSHADER );
	 //renderGridLines( gridSHADER );
	
	//renderGridLines( 0 );
	// renderGrid( 0 );
	//renderGridPoints( 0 );
	//renderGridLinesEBO( gridSHADER );
	
  
	
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 drawTextColo();
	//  drawTextColoHindi();
	  glDisable(GL_BLEND);
	  
	    // if this is the first frame, install the demo scene

  
	 // rendererSTBTextHindi.GetShaderID();
	// renderGrid( rendererSTBTextHindi.shaderObject->GetShaderID() );
	  // github.com/0xFA11/MultiplayerNetworkingResources
	  // 
	  
    glBindVertexArray(0);

    glutSwapBuffers();
}
/*
int frame = 0; float timebase = 0; float time = 0; float fps = 0;

void updateFPS() {
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 16.66666666666667) // 16.66666666666667
		{ 
	//[[[[vertices2[12] += 0.01f;
	//[[[[printf("vertices2[12]: %f",vertices2[12]);
	
	fps = frame * 1000.0 / (time - timebase);
	timebase = time; frame = 0; 
	
//[]	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
//    glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(float), vertices2.data(), GL_STREAM_DRAW);

   // glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(float), vertices2.data(), GL_STREAM_DRAW);
  // float *tempFloat = &vertices2[12];
	//   glBufferSubData(GL_ARRAY_BUFFER, 12, 1, (void*)tempFloat);
//[]	glBufferSubData(GL_ARRAY_BUFFER, 12 * sizeof(float), sizeof(float), &vertices2[12]);
	
 //[]   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
 //[]   glEnableVertexAttribArray(0);

 //[]   glBindBuffer(GL_ARRAY_BUFFER, 0);
 //[]   glBindVertexArray(0);
	
	}
	
 // UpdateVertices();
 
 // RawMouseCode
 
	}*/
	

void idle() {
	//	updateFPS();
		 // Render text
       
		glutPostRedisplay(); 
		}
		
	MapManager* mapManager = nullptr; // Declare as pointer globally or in main	
void initGL() {
    glewInit();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Background color
	
 setupGridBuffers();
 setupSpriteBuffers();
  

 
 initText1();

//makeText ( "HelloL", 100.0f, 300.0f, 1.0f, 1.0f, 1.0f, 1.0f);
// 
//void makeText(const char* text, float x, float y, float scale, float r, float g, float b )
  printf("makeText\n\r");

  makeText ( "Hello L1B", -0.5f, 0.4f, 0.02f, 0.0f, 1.0f, 1.0f);
 
 printf("makeTextHindi\n\r");

   // makeTextHindi( u8"हायवर्ल्ड", -1.2f, 0.4f, 0.01f, 1.0f, 0.0f, 0.5f);

 // makeTextHindi( "हैलो विश्व", -0.5f, 0.0f, 0.02f, 1.0f, 0.0f, 1.0f);
      printf("initBuffers\n\r");
    initBuffers();
	printf("	MapManager mapManager;\n\r");
	//MapManager mapManager;
//	mapManager = new MapManager(); // Initialize after all setup
	mapManager = new MapManager();
	
	mapManager->InitEnemy();
	
//	mapManager->InitDialogBallon();
	
//	mapManager->InitLitePhysicsObjects();
		
	mapManager->InitAddBox();
//	mapManager->InitTriangle();
//	mapManager->InitHexagon();
//	mapManager->InitDirt();
	
	mgr = SceneManager::GetInstance();
 
 
// Alternatively, query viewport dimensions using OpenGL
    GLint viewport[4]; // [x, y, width, height]
    glGetIntegerv(GL_VIEWPORT, viewport);
    printf("Viewport Width: %d, Viewport Height: %d\n", viewport[2], viewport[3]);
	
	mgr->SetScreenSize(viewport[2], viewport[3]);
	 
  
	//mapManager->GenerateMap();
//	mapManager->InitMap();
	//mapManager.
	printf("	initGL() ; finished\n\r");
}
void WindowReshape(int width, int height)
{
g_Width = width;
g_Height = height;

HWND hwnd = GetForegroundWindow();
 RECT rect;
    GetClientRect(hwnd, &rect);
    int width2 = rect.right - rect.left;
    int height2 = rect.bottom - rect.top;
	 
	 if (width2 != mSurfWidth || height2 != mSurfHeight) {
    // notify scene manager that the surface has changed size
   #ifdef ANDROID
   ALOGI("NativeEngine: surface changed size %dx%d --> %dx%d", mSurfWidth,
          mSurfHeight, width2, height2);
		  #else
		   printf("NativeEngine: surface changed size %dx%d --> %dx%d\n\r", mSurfWidth,
          mSurfHeight, width2, height2);	  
		  
		#endif	  
    mSurfWidth = width2;
    mSurfHeight = height2;
    mgr->SetScreenSize(mSurfWidth, mSurfHeight);
	SpriteManagerSetResolution(width2,height2);
    glViewport(0, 0, mSurfWidth, mSurfHeight);
  }
  
 
 //glViewport(0,0 , width2,height2);
	
}


void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
	
if (key == 65 || key == 97) //key a,A
{
g_PlayerBackwardKeyDown =1;
printf("\ng_PlayerBackwardKeyDown\n");

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

//static struct CookedEvent event;;

static bool _cooked_event_callback(struct CookedEvent *eventparam) {
  SceneManager *mgr = SceneManager::GetInstance();
  PointerCoords coords;
  memset(&coords, 0, sizeof(coords));
 coords.x = (float)eventparam->motionX;
coords.y = (float)eventparam->motionY;
coords.minX = (float)eventparam->motionMinX;
coords.maxX = (float)eventparam->motionMaxX;
coords.minY = (float)eventparam->motionMinY;
coords.maxY = (float)eventparam->motionMaxY;

  coords.isScreen = eventparam->motionIsOnScreen;
// Debug eventparam fields directly
   // printf("_cooked_event_callback eventparam->motionX:%f\n\reventparam->motionY:%f\n\r eventparam->motionMinX:%f\n\r eventparam->motionMaxX:%f\n\r eventparam->motionMinY:%f\n\r eventparam->motionMaxY:%f\n\r eventparam->motionIsOnScreen:%d\n\r eventparam->type:%d\n\r",
  //         eventparam->motionX, eventparam->motionY, eventparam->motionMinX, eventparam->motionMaxX, eventparam->motionMinY, eventparam->motionMaxY, eventparam->motionIsOnScreen, eventparam->type);
		   
// printf("_cooked_event_callback coords.x:%f\n\rcoords.y:%f\n\r coords.minX:%f\n\r coords.maxX:%f\n\r coords.minY:%f\n\r coords.maxY:%f\n\r coords.isScreen:%d\n\r event->type:%d\n\r",coords.x,
 //coords.y,
 
 //  coords.minX,
 // coords.maxX ,
 // coords.minY ,
 // coords.maxY,
 
 //coords.isScreen,
 //eventparam->type
 // );

  switch (eventparam->type) {
    case COOKED_EVENT_TYPE_JOY:
      mgr->UpdateJoy(eventparam->joyX, eventparam->joyY);
      return true;
    case COOKED_EVENT_TYPE_POINTER_DOWN:
      mgr->OnPointerDown(eventparam->motionPointerId, &coords);
      return true;
    case COOKED_EVENT_TYPE_POINTER_UP:
      mgr->OnPointerUp(eventparam->motionPointerId, &coords);
      return true;
    case COOKED_EVENT_TYPE_POINTER_MOVE:
      mgr->OnPointerMove(eventparam->motionPointerId, &coords);
      return true;
    case COOKED_EVENT_TYPE_KEY_DOWN:
      mgr->OnKeyDown(eventparam->keyCode);
      return true;
    case COOKED_EVENT_TYPE_KEY_UP:
      mgr->OnKeyUp(eventparam->keyCode);
      return true;
    case COOKED_EVENT_TYPE_BACK:
      return mgr->OnBackKeyPressed();
    default:
      return false;
  }
}

//-- MOUSE CODE 2
HHOOK hMouseHook;

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && hwndGetForegroundWindow > 0) {
        MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;

// Get Actual Mouse Place in Window or Not and in Window	
/*
	int windowX = glutGet(GLUT_WINDOW_X);
    int windowY = glutGet(GLUT_WINDOW_Y);
 
	int x = pt.x - windowX;
	int y = pt.y - windowY;

	int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
	*/
	
	struct CookedEvent localevent;
        memset(&localevent, 0, sizeof(localevent));
		// I think you should do webcams on chater
		RECT rect;
    //GetClientRect(hwndGetForegroundWindow, &rect);
	rect.left = glutGet(GLUT_WINDOW_X);
    rect.bottom = glutGet(GLUT_WINDOW_Y);
	rect.right = rect.left + glutGet(GLUT_WINDOW_WIDTH);
	rect.top = rect.bottom + glutGet(GLUT_WINDOW_HEIGHT);
	// Get Actual Mouse Place in Window or Not and in Window	
	
        if (wParam == WM_LBUTTONDOWN) {
		//	struct CookedEvent event;
		// memset(&event, 0, sizeof(event));
			localevent.motionPointerId = 0;
			localevent.type = COOKED_EVENT_TYPE_POINTER_DOWN;
			
			//	localevent.motionX  = (float)pMouseStruct->pt.x;
			//	localevent.motionY  = (float)pMouseStruct->pt.y ;
			//	localevent.motionMinX =  (float)rect.left;
			//	localevent.motionMaxX =  (float)rect.right;
			//	localevent.motionMinY =  (float)rect.bottom;
			//	localevent.motionMaxY =  (float)rect.top;
				
					localevent.motionX  =(float)pMouseStruct->pt.x - (float)rect.left;
					localevent.motionY  =(float)pMouseStruct->pt.y -   (float)rect.bottom ;
					localevent.motionMinX =0;
						localevent.motionMaxX =  (float)rect.right - (float)rect.left;
						localevent.motionMinY =  0;
					localevent.motionMaxY =  (float)rect.top - (float)rect.bottom; ;
					
				if(pMouseStruct->pt.x > rect.left && pMouseStruct->pt.x < rect.right
				&& pMouseStruct->pt.y > rect.bottom && pMouseStruct->pt.y < rect.top )
				{
				localevent.motionIsOnScreen = true;
				}
				else
				{
					localevent.motionIsOnScreen = false;
				}
				
				printf("wParam == WM_LBUTTONDOWN localevent.motionX:%d\n\rlocalevent.motionY:%d\n\r rect.left:%d\n\r rect.right:%d\n\r rect.bottom:%d\n\r rect.top:%d\n\r localevent.motionIsOnScreen:%d\n\r",
				localevent.motionX,
			localevent.motionY,
 
			rect.left,
			rect.right ,
			rect.bottom ,
				rect.top,
 
				localevent.motionIsOnScreen
			);
			
				_cooked_event_callback(&localevent);
				
   // coords.minX = event->motionMinX;
   // coords.maxX = event->motionMaxX;
   // coords.minY = event->motionMinY;
   // coords.maxY = event->motionMaxY;
   // coords.isScreen = event->motionIsOnScreen;
   //    RECT rect;
   //  GetClientRect(hwnd, &rect);
   //   int width = rect.right - rect.left;
   // int height = rect.bottom - rect.top;
	
            std::cout << "Left mouse button down at (" << pMouseStruct->pt.x << ", " << pMouseStruct->pt.y << ")" << std::endl;
        } else if (wParam == WM_RBUTTONDOWN) {
			
			
			localevent.motionPointerId = 1;
			localevent.type = COOKED_EVENT_TYPE_POINTER_DOWN;
			//	localevent.motionX  = (float)pMouseStruct->pt.x;
			//	localevent.motionY  = (float)pMouseStruct->pt.y ;
			//	localevent.motionMinX =  (float)rect.left;
			//	localevent.motionMaxX =  (float)rect.right;
			//	localevent.motionMinY =  (float)rect.bottom;
			//	localevent.motionMaxY =  (float)rect.top;
				localevent.motionX  =(float)pMouseStruct->pt.x - (float)rect.left;
					localevent.motionY  =(float)pMouseStruct->pt.y -   (float)rect.bottom ;
					localevent.motionMinX =0;
						localevent.motionMaxX =  (float)rect.right - (float)rect.left;
						localevent.motionMinY =  0;
					localevent.motionMaxY =  (float)rect.top - (float)rect.bottom; ;
						
				
				if(pMouseStruct->pt.x > rect.left && pMouseStruct->pt.x < rect.right
				&& pMouseStruct->pt.y > rect.bottom && pMouseStruct->pt.y < rect.top )
				{
				localevent.motionIsOnScreen = true;
				}
				else
				{
					localevent.motionIsOnScreen = false;
				}
				
				printf("wParam == WM_RBUTTONDOWN localevent.motionX:%d\n\rlocalevent.motionY:%d\n\r rect.left:%d\n\r rect.right:%d\n\r rect.bottom:%d\n\r rect.top:%d\n\r localevent.motionIsOnScreen:%d\n\r",
				localevent.motionX,
			localevent.motionY,
 
			rect.left,
			rect.right ,
			rect.bottom ,
				rect.top,
 
				localevent.motionIsOnScreen
			);
				
				
				_cooked_event_callback(&localevent);
				
			
            std::cout << "Right mouse button down at (" << pMouseStruct->pt.x << ", " << pMouseStruct->pt.y << ")" << std::endl;
        }else if (wParam == WM_MOUSEMOVE){
            std::cout << "Mouse moved to (" << pMouseStruct->pt.x << ", " << pMouseStruct->pt.y << ")" << std::endl; //commented out to reduce console spam.
        
	//	struct CookedEvent event;
	//  memset(&event, 0, sizeof(event));
	  
		localevent.motionPointerId = 0;
			localevent.type = COOKED_EVENT_TYPE_POINTER_MOVE;
			localevent.motionX  = (float)pMouseStruct->pt.x;
			//	localevent.motionX  = pMouseStruct->pt.x;
		//		localevent.motionY  = (float)pMouseStruct->pt.y ;
		//		localevent.motionMinX =  (float)rect.left;
		//		localevent.motionMaxX =  (float)rect.right;
		//		localevent.motionMinY =  (float)rect.bottom;
		//		localevent.motionMaxY =  (float)rect.top;
			localevent.motionX  =(float)pMouseStruct->pt.x - (float)rect.left;
					localevent.motionY  =(float)pMouseStruct->pt.y -   (float)rect.bottom ;
					localevent.motionMinX =0;
						localevent.motionMaxX =  (float)rect.right - (float)rect.left;
						localevent.motionMinY =  0;
					localevent.motionMaxY =  (float)rect.top - (float)rect.bottom; ;
					
		
		
				if(pMouseStruct->pt.x > rect.left && pMouseStruct->pt.x < rect.right
				&& pMouseStruct->pt.y > rect.bottom && pMouseStruct->pt.y < rect.top )
				{
				localevent.motionIsOnScreen = true;
				}
				else
				{
					localevent.motionIsOnScreen = false;
				}
				
		//		 printf("wParam == WM_MOUSEMOVE localevent.motionX:%f\n\rlocalevent.motionY:%f\n\r localevent.motionMinX:%f\n\r localevent.motionMaxX:%f\n\r localevent.motionMinY:%f\n\r localevent.motionMaxY:%f\n\r localevent.motionIsOnScreen:%d\n\r localevent.type:%d\n\r",
       //    localevent.motionX, localevent.motionY, localevent.motionMinX, localevent.motionMaxX, localevent.motionMinY, localevent.motionMaxY, localevent.motionIsOnScreen, localevent.type);
		   
		   
				_cooked_event_callback(&localevent);
		
		
		}
		else if (wParam == WM_LBUTTONUP){
		//	struct CookedEvent event;
		// memset(&event, 0, sizeof(event));
			localevent.motionPointerId = 1;
			
			localevent.type = COOKED_EVENT_TYPE_POINTER_UP;
		//		localevent.motionX  = (float)pMouseStruct->pt.x;
		//		localevent.motionY  = (float)pMouseStruct->pt.y ;
		//		localevent.motionMinX =  (float)rect.left;
		//		localevent.motionMaxX =  (float)rect.right;
		//		localevent.motionMinY =  (float)rect.bottom;
		//		localevent.motionMaxY =  (float)rect.top;
			localevent.motionX  =(float)pMouseStruct->pt.x - (float)rect.left;
					localevent.motionY  =(float)pMouseStruct->pt.y -   (float)rect.bottom ;
					localevent.motionMinX =0;
						localevent.motionMaxX =  (float)rect.right - (float)rect.left;
						localevent.motionMinY =  0;
					localevent.motionMaxY =  (float)rect.top - (float)rect.bottom; ;
					
			
				
				if(pMouseStruct->pt.x > rect.left && pMouseStruct->pt.x < rect.right
				&& pMouseStruct->pt.y > rect.bottom && pMouseStruct->pt.y < rect.top )
				{
				localevent.motionIsOnScreen = true;
				}
				else
				{
					localevent.motionIsOnScreen = false;
				}
				
				printf("wParam == WM_LBUTTONUP localevent.motionX:%d\n\rlocalevent.motionY:%d\n\r rect.left:%d\n\r rect.right:%d\n\r rect.bottom:%d\n\r rect.top:%d\n\r localevent.motionIsOnScreen:%d\n\r",
				localevent.motionX,
			localevent.motionY,
 
			rect.left,
			rect.right ,
			rect.bottom ,
				rect.top,
 
				localevent.motionIsOnScreen
 );
				
				_cooked_event_callback(&localevent);
		}
		else if (wParam == WM_RBUTTONUP){
		//	struct CookedEvent event;
		// memset(&event, 0, sizeof(event));
			localevent.motionPointerId = 0;
			localevent.type = COOKED_EVENT_TYPE_POINTER_UP;
			
			//	localevent.motionX  = (float)pMouseStruct->pt.x;
			//	localevent.motionY  = (float)pMouseStruct->pt.y ;
			//	localevent.motionMinX =  (float)rect.left;
			//	localevent.motionMaxX =  (float)rect.right;
			//	localevent.motionMinY =  (float)rect.bottom;
			//	localevent.motionMaxY =  (float)rect.top;
				localevent.motionX  =(float)pMouseStruct->pt.x - (float)rect.left;
					localevent.motionY  =(float)pMouseStruct->pt.y -   (float)rect.bottom ;
					localevent.motionMinX =0;
						localevent.motionMaxX =  (float)rect.right - (float)rect.left;
						localevent.motionMinY =  0;
					localevent.motionMaxY =  (float)rect.top - (float)rect.bottom; ;
					
		
				
				if(pMouseStruct->pt.x > rect.left && pMouseStruct->pt.x < rect.right
				&& pMouseStruct->pt.y > rect.bottom && pMouseStruct->pt.y < rect.top )
				{
				localevent.motionIsOnScreen = true;
				}
				else
				{
					localevent.motionIsOnScreen = false;
				}
				_cooked_event_callback(&localevent);
		}
        // ... handle other mouse events ...
    }

    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

//-- MOUSE CODE 2 WND

int main(int argc, char** argv) {
	setlocale(LC_ALL, "");
// MOUSE 2 HOOK
	 hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, GetModuleHandle(NULL), 0);

    if (hMouseHook == NULL) {
        std::cerr << "Failed to install mouse hook!" << std::endl;
        return 1;
    }
	// MOUSE 2 HOOK END



    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(g_Width, g_Height);
    glutCreateWindow("Multiple VAO and VBO Example 45");

    initGL();
HWND hwnd = GetForegroundWindow();
 RECT rect;
    GetClientRect(hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
	
 SpriteManagerSetResolution(width,height);
 
 updateSpriteManagerUniforms();
 
 glutReshapeFunc(WindowReshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(processNormalKeys);
//	glutSpecialFunc(processSpecialKeys);
	
	//    glutKeyboardFunc(KeyboardDown); //Telling glut what function to call when the event occurs
//    glutKeyboardUpFunc(KeyboardUp); //Telling glut what function to call when the event occurs

	    glutKeyboardUpFunc(KeyboardUp); //Telling glut what function to call when the event occurs


    glutDisplayFunc(render);
	hwndGetForegroundWindow = GetForegroundWindow();
	
    glutMainLoop();

    return 0;
}