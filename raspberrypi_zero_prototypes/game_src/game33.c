#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include <bcm_host.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>


  #define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

// pi@raspberrypi:~/game_src/assets $  wget https://raw.githubusercontent.com/Gchipunov/Colos_Android_Game/refs/heads/main/texture_map.png
// link project:
//  gcc -o game19 game19.c -std=c99 -D_POSIX_C_SOURCE=200809L -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt

// gcc -o game16 game16.c -std=c99 -D_POSIX_C_SOURCE=200809L -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt
// gcc -o game17 game17.c -std=c99 -D_POSIX_C_SOURCE=200809L -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt
// gcc -o game18 game18.c -std=c99 -D_POSIX_C_SOURCE=200809L -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt

// gcc -o game20 game20.c -std=c99 -D_POSIX_C_SOURCE=200809L -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt

// gcc -o game21 game21.c -std=c99 -D_POSIX_C_SOURCE=200809L -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt
// gcc -o game22 game22.c -std=c99 -D_POSIX_C_SOURCE=200809L -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt
// gcc  -o game22 -I/usr/include game22.c -lGLESv2 -lEGL -lbcm_host -lm -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads  -I/opt/vc/include/interface/vmcs_host/linux
// // gcc -o game22 game22.c -std=c99 -D_POSIX_C_SOURCE=200809L -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt
// gcc -o game23 game23.c -std=c99 -D_POSIX_C_SOURCE=200809L -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt
// gcc -o game24 game24.c -std=c99 -D_POSIX_C_SOURCE=200809L -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt
// gcc -o game25 game25.c -std=c99 -D_POSIX_C_SOURCE=200809L -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt

typedef struct tagEsContext
{
    GLint width;
    GLint height;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    GLuint program;
    GLuint vertexBuffer;
    GLint mvpLoc;

        GLint texcoordLoc;
        GLint textureLoc ;
    float angle;
} EsContext;
EsContext state;


static void get_native_display_size(uint32_t* width, uint32_t* height)
{
    if (graphics_get_display_size(0, width, height) < 0) {
        perror("Failed to graphics_get_display_size");
        exit(EXIT_FAILURE);
    }
}

static NativeWindowType create_native_window(uint32_t width, uint32_t height)
{
    VC_RECT_T dst_rect;
    vc_dispmanx_rect_set(&dst_rect, 0, 0, width, height);
    VC_RECT_T src_rect;
    vc_dispmanx_rect_set(&src_rect, 0, 0, (width<<16), (height<<16));
    DISPMANX_DISPLAY_HANDLE_T dispman_display = vc_dispmanx_display_open(0);
    DISPMANX_UPDATE_HANDLE_T dispman_update = vc_dispmanx_update_start(0);
    DISPMANX_ELEMENT_HANDLE_T dispman_element =
        vc_dispmanx_element_add(dispman_update, dispman_display, 0, &dst_rect,
                               0, &src_rect, DISPMANX_PROTECTION_NONE, 0, 0,
                               DISPMANX_NO_ROTATE);

    static EGL_DISPMANX_WINDOW_T nativewindow;
    nativewindow.element = dispman_element;
    nativewindow.width = width;
    nativewindow.height = height;
    vc_dispmanx_update_submit_sync(dispman_update);
    return (NativeWindowType)&nativewindow;
}

void init_ogl(EsContext *state)
{
   state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglInitialize(state->display, NULL, NULL) == EGL_FALSE) {
        perror("Failed to eglInitialize");
        exit(EXIT_FAILURE);
    }

    static const EGLint attribute_list[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
       EGL_BUFFER_SIZE, 8,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE
    };
    EGLint num_config = 0;
    EGLConfig config;
    if (eglChooseConfig(state->display, attribute_list, &config, 1, &num_config) == EGL_FALSE) {

        perror("Failed to eglChooseConfig");
        exit(EXIT_FAILURE);
                }


    if (eglBindAPI(EGL_OPENGL_ES_API) == EGL_FALSE) {
        perror("Failed to eglBindAPI");
        exit(EXIT_FAILURE);
    }

    static const EGLint context_attributes[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

                state->context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, context_attributes);
    if (state->context == EGL_NO_CONTEXT) {
        perror("Failed to eglCreateContext");
        exit(EXIT_FAILURE);
    }

    get_native_display_size(&state->width, &state->height);
    NativeWindowType nativewindow = create_native_window(state->width, state->height);
    state->surface = eglCreateWindowSurface(state->display, config, nativewindow, NULL);
    if (state->surface == EGL_NO_SURFACE) {
                perror("Failed to eglCreateWindowSurface");
        exit(EXIT_FAILURE);
    }

    if (eglMakeCurrent(state->display, state->surface, state->surface, state->context) == EGL_FALSE) {

        perror("Failed to eglMakeCurrent");
        exit(EXIT_FAILURE);
    }
}

unsigned char *SpriteManager_image;
 int SpriteManager_w, SpriteManager_h, SpriteManager_comp;//original_no_channels
 GLuint SpriteManager_m_texture = 0;

 int PlayerSpriteIndex;
  int PlayerUVIndex;


 int g_iSpriteManagerFlipSprites = 0;

 int g_iDDSTransparentcyFix = 0;  // mostly for the temp level map

GLuint loadImageMaterialSpriteManager()
{
//       D:\DDS-Utilities>nvdxt -quality_production -file texture_map8.png  -dx$
// Version 8.30
//    Reading texture_map8.png  [Processing] Writing .\texture_map8.dds

// D:\DDS-Utilities>

    int desired_no_channels = 4;
//        stbi_set_flip_vertically_on_load(true);

      SpriteManager_image = stbi_load("assets/texture_map.png", &SpriteManager_w, &SpriteManager_h, &SpriteManager_comp , desired_no_channels  );
      if(SpriteManager_image == NULL) {
          printf("Error in loading the image\n");
          exit(1);
     }
     printf("Loaded image with a width of %dpx, a height of %dpx.  The original  image had %d channels, the loaded image has %d channels.\n",
         SpriteManager_w, SpriteManager_h, SpriteManager_comp, desired_no_channels);

     // ...

         glGenTextures(1, &SpriteManager_m_texture);
//int comp = 4;

glBindTexture(GL_TEXTURE_2D, SpriteManager_m_texture);

//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


if(SpriteManager_comp == 3)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SpriteManager_w, SpriteManager_h, 0, GL_RGB, GL_UNSIGNED_BYTE, SpriteManager_image);

else if(SpriteManager_comp == 4)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SpriteManager_w, SpriteManager_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, SpriteManager_image);




        stbi_image_free(SpriteManager_image);


// Poor filtering, or ...
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // ... nice trilinear filtering ...
//      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        // ... which requires mipmaps. Generate them automatically.
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        return SpriteManager_m_texture;

}

void init_shaders(EsContext *state)
{

// Vertex Shader
const char *vertex_shader =
    "#version 100\n"
    "attribute vec3 position;\n"
    "attribute lowp vec2 TEXCOORD0;\n"
    "varying lowp vec2 texcoord0;\n"
    "varying lowp vec4 distance0;\n" // Stores the clip-space position
    "uniform mat4 mvpMatrix;\n"
    "void main() {\n"
    "    texcoord0 = TEXCOORD0;\n"
    "    distance0 = mvpMatrix * vec4(position, 1.0);\n" // Calculate clip-space position
    "    gl_Position = distance0;\n" // Set gl_Position to the clip-space position
    "}\n";

// Fragment Shader
const char *fragment_shader =
    "#version 100\n"
    "precision mediump float;\n"
    "uniform sampler2D DIFFUSE;\n" // Still present, but not used for color in this example
    "varying lowp vec2 texcoord0;\n"
    "varying lowp vec4 distance0;\n" // Receives the clip-space position from vertex shader
    "void main() {\n"
    "    // Calculate the normalized device coordinate (NDC) depth from the clip-space Z and W components.\n"
    "    // For perspective projection, Z/W gives the depth in NDC space, typically [-1, 1].\n"
    "    float ndc_depth = distance0.z / distance0.w;\n"
    "\n"
    "    // Remap the NDC depth from [-1, 1] to [0, 1] for color representation.\n"
    "    // A value of 0.0 corresponds to -1.0 (near plane), and 1.0 corresponds to 1.0 (far plane).\n"
    "    float normalized_distance = (ndc_depth + 1.0) * 0.5;\n"
    "\n"
    "    // Invert the normalized distance so that objects closer to the camera (smaller depth) are brighter.\n"
    "    // If you want farther objects to be brighter, remove '1.0 -'.\n"
    "    float brightness = 1.0 - normalized_distance;\n"
    "\n"
    "    // Set the fragment color based on the calculated brightness (grayscale).\n"
    "    // The alpha component is set to 1.0 for full opacity.\n"
    "    gl_FragColor = vec4(brightness, brightness, brightness, 1.0);\n"
    "\n"
    "    // If you want to blend with the texture, you could do something like:\n"
    "    // vec4 texture_color = texture2D(DIFFUSE, texcoord0);\n"
    "    // gl_FragColor = vec4(mix(texture_color.rgb, vec3(brightness), 0.5), texture_color.a);\n"
    "}\n";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
        glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    state->program = glCreateProgram();
    glAttachShader(state->program, vs);
    glAttachShader(state->program, fs);
    glLinkProgram(state->program);

 GLint linked;
    glGetProgramiv(state->program, GL_LINK_STATUS, &linked);
    if (!linked) {
    GLint infoLen = 0;
    glGetProgramiv(state->program, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen > 1) {
        char* infoLog = malloc(sizeof(char) * infoLen);
        glGetProgramInfoLog(state->program, infoLen, NULL, infoLog);
        printf("Error linking program:\n%s\n", infoLog);
        free(infoLog);
    }
    perror("Failed to link program");
    exit(EXIT_FAILURE);
}

    state->mvpLoc = glGetUniformLocation(state->program, "mvpMatrix");
        GLuint texcoordLoc = glGetAttribLocation(state->program, "TEXCOORD0");
GLuint textureLoc = glGetUniformLocation(state->program, "DIFFUSE");
state->texcoordLoc =texcoordLoc;
state->textureLoc =textureLoc;

}


void init_geometry(EsContext *state)
{
  //  float vertices[] = {
        // Front
  //      -0.5f, -0.5f,  0.5f,
  //       0.5f, -0.5f,  0.5f,
  //       0.5f,  0.5f,  0.5f,
  //      -0.5f,  0.5f,  0.5f,
        // Back
  //    -0.5f, -0.5f, -0.5f,
  //       0.5f, -0.5f, -0.5f,
  //       0.5f,  0.5f, -0.5f,
  //      -0.5f,  0.5f, -0.5f,
  //  };
         float vertices[] = {
        // Front
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        // Back
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    };


   GLushort indices[] = {
    // Front face (correct)
    0, 1, 2, 0, 2, 3,

    // Right face (fixed to CCW)
    1, 5, 6, 1, 6, 2,

    // Back face (fixed to CCW)
    5, 4, 7, 5, 7, 6,

    // Left face (fixed to CCW)
    4, 0, 3, 4, 3, 7,

    // Top face (fixed to CCW)
    3, 2, 6, 3, 6, 7,

    // Bottom face (fixed to CCW)
    4, 5, 1, 4, 1, 0
};
    glGenBuffers(1, &state->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, state->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint indexBuffer;
 glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void draw(EsContext *state)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glUseProgram(state->program);

    // Simple perspective projection
    float aspect = (float)state->width / state->height;
    float proj[16] = {
        1.0f/aspect, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.01f, -1.0f,
        0.0f, 0.0f, -2.01f, 0.0f
    };

    // Rotation matrix
    state->angle += 0.01f;

 // Rotation matrix around X-axis
float angleX = state->angle;
float cX = cosf(angleX);
float sX = sinf(angleX);
float rotX[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, cX, -sX, 0.0f,
    0.0f, sX, cX, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

// Rotation matrix around Z-axis
float angleZ = state->angle;
float cZ = cosf(angleZ);
float sZ = sinf(angleZ);
float rotZ[16] = {
    cZ, -sZ, 0.0f, 0.0f,
    sZ, cZ, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

// Combine rotation matrices
float rot[16];
for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
        rot[i*4+j] = 0.0f;
        for (int k = 0; k < 4; k++)
            rot[i*4+j] += rotX[i*4+k] * rotZ[k*4+j];
    }



    // Translate cube away from camera
    float trans[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, -2.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
 // Matrix multiplication
    float mvp[16];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            mvp[i*4+j] = 0.0f;
            for (int k = 0; k < 4; k++)
                mvp[i*4+j] += proj[i*4+k] * rot[k*4+j];
        }
    float temp[16];

         for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            temp[i*4+j] = 0.0f;
            for (int k = 0; k < 4; k++)
                temp[i*4+j] += mvp[i*4+k] * trans[k*4+j];
        }
    for (int i = 0; i < 16; i++)
        mvp[i] = temp[i];

    glUniformMatrix4fv(state->mvpLoc, 1, GL_FALSE, mvp);


    glBindBuffer(GL_ARRAY_BUFFER, state->vertexBuffer);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);

    glEnableVertexAttribArray(0);

 glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SpriteManager_m_texture);
    glUniform1i(glGetUniformLocation(state->program, "DIFFUSE"), 0);


   // glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

    eglSwapBuffers(state->display, state->surface);
}


void initglsettings()
{

}

int main(int argc, char* argv[])
{
    bcm_host_init();
    init_ogl(&state);
    init_shaders(&state);
    init_geometry(&state);
    loadImageMaterialSpriteManager();
    initglsettings();

    while (1) {
        draw(&state);
        usleep(16666); // ~60 FPS
   }

    return 0;
}


