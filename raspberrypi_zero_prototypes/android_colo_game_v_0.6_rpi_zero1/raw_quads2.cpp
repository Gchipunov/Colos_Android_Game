
// raw_quads2.cpp 
// Georgiy Chipunov
// a simple Terminal Input to Raspberry pi Zero, moving a Red Quad
//
// Compilation command:
// g++ -o raw_quads2 raw_quads2.cpp -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt

// g++ -O2 -std=c++11 raw_quads2.cpp -o raw_quads2 \
-I/opt/vc/include \
-I/opt/vc/include/interface/vcos/pthreads \
-I/opt/vc/include/interface/vmcs_host/linux \
-L/opt/vc/lib \
-lGLESv2 -lEGL -lbcm_host -lm -lrt -lpthread
/*
// Prompt Gemini:
// it compiled with command:g++ -O2 -std=c++11 input_terminal_quads1.cpp -o input_terminal_quads1 \

-I/opt/vc/include \

-I/opt/vc/include/interface/vcos/pthreads \

-I/opt/vc/include/interface/vmcs_host/linux \

-L/opt/vc/lib \

-lGLESv2 -lEGL -lbcm_host -lm -lrt -lpthread

Good, and works, I was wondering if you can make it so its direct input where if I press A or D it moves right to left or W and S it moves up and down.. like more keyboard input style like : glfw3 code:

void Gosha_UI_Text_Button1::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {


/*

g_local_player->keyCallback( window,  key,  scancode,  action,  mods);



  //  g_ColoQuatCamera->keyCallback( window,  key,  scancode,  action,  mods);


g_ColoQuatCamera->keyCallbackDebug( window,  key,  scancode,  action,  mods);

//  g_ColoQuatCamera->keyCallbackDebug2( window,  key,  scancode,  action,  mods);





if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)

        glfwSetWindowShouldClose(window, GL_TRUE);


// GAME DEBUG CODE NEED TO RECODE FOR Release

if (key == GLFW_KEY_B && action == GLFW_PRESS)

        pSpriteManager2->iThreeDeeCamera = 2;

if (key == GLFW_KEY_V && action == GLFW_PRESS)

        pSpriteManager2->iThreeDeeCamera = 1;       // Will be depricated or replaced, quat_camera

if (key == GLFW_KEY_N && action == GLFW_PRESS)

        pSpriteManager2->iThreeDeeCamera = 3;

// END-GAME DEBUG CODE NEED TO RECODE FOR Release


// pSpriteManager2->iThreeDeeCamera = 2;


//

}*/
// source : input_terminal_quads1.cpp
// https://gemini.google.com/app/b75894deb2a5704d

// https://gemini.google.com/app/b75894deb2a5704d
// g++ -std=c++11 quad_move2.cpp -o quad_move2_bard2 -lbrcmGLESv2 -lbrcmEGL -lbcm_host -lpthread -I/opt/vc/include -L/opt/vc/lib

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <termios.h> // Added for raw terminal input
#include <bcm_host.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <thread>
#include <atomic>

typedef struct {
    GLuint program;
    GLint posLoc;
    GLint colorLoc;
    GLint timeLoc;
} ShaderProgram;

typedef struct tagEsContext {
    uint32_t width;
    uint32_t height;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

    ShaderProgram simpleShader;
    ShaderProgram specialShader;

    GLuint vboMoving;
    GLuint vboStatic;

    double startTime;

    // --- NEW COORDINATE VARIABLES ---
    std::atomic<float> posX;
    std::atomic<float> posY;
    std::atomic<bool> running;
} EsContext;

EsContext state;

// Standard vertices from your original code
GLfloat base_vertices[] = {
    -0.2f,  0.2f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -0.2f, -0.2f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     0.2f, -0.2f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -0.2f,  0.2f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     0.2f, -0.2f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     0.2f,  0.2f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
};

GLfloat third_quad_vertices[] = {
    0.3f,  0.8f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    0.3f,  0.3f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    0.8f,  0.3f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    0.3f,  0.8f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    0.8f,  0.3f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    0.8f,  0.8f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
};

// --- RAW TERMINAL INPUT THREAD ---
void input_thread_func(EsContext *ctx) {
    struct termios old_t, new_t;
    tcgetattr(STDIN_FILENO, &old_t); // Get current settings
    new_t = old_t;
    new_t.c_lflag &= ~(ICANON | ECHO); // Disable buffering and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &new_t);

    printf("Controls: W/A/S/D to move, Q to quit.\n");

    while (ctx->running) {
        char c = getchar();
        float step = 0.05f;

        if (c == 'w' || c == 'W') ctx->posY = ctx->posY + step;
        if (c == 's' || c == 'S') ctx->posY = ctx->posY - step;
        if (c == 'a' || c == 'A') ctx->posX = ctx->posX - step;
        if (c == 'd' || c == 'D') ctx->posX = ctx->posX + step;
        if (c == 'q' || c == 'Q') ctx->running = false;

        usleep(1000);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_t); // Restore settings on exit
}

float get_time_s(double start) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double current = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    return (float)(current - start);
}

// ... (get_native_display_size, create_native_window, compile_shader, create_program, init_shaders, init_geometry, init_ogl remain identical) ...
static void get_native_display_size(uint32_t* width, uint32_t* height) { graphics_get_display_size(0, width, height); }
static NativeWindowType create_native_window(uint32_t width, uint32_t height) {
    VC_RECT_T dst_rect, src_rect;
    vc_dispmanx_rect_set(&dst_rect, 0, 0, width, height);
    vc_dispmanx_rect_set(&src_rect, 0, 0, (width<<16), (height<<16));
    DISPMANX_DISPLAY_HANDLE_T dispman_display = vc_dispmanx_display_open(0);
    DISPMANX_UPDATE_HANDLE_T dispman_update = vc_dispmanx_update_start(0);
    DISPMANX_ELEMENT_HANDLE_T dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display, 0, &dst_rect, 0, &src_rect, DISPMANX_PROTECTION_NONE, 0, 0, DISPMANX_NO_ROTATE);
    static EGL_DISPMANX_WINDOW_T nativewindow;
    nativewindow.element = dispman_element; nativewindow.width = width; nativewindow.height = height;
    vc_dispmanx_update_submit_sync(dispman_update);
    return (NativeWindowType)&nativewindow;
}
// ... (Helper functions: compile_shader, create_program, init_shaders, etc. stay the same) ...
// Note: Only updating draw() to use the new posX/posY

void draw(EsContext *state) {
    float t = (float)get_time_s(state->startTime);

    // Update moving quads based on manual posX/posY
    GLfloat updated_vertices[48];
    memcpy(updated_vertices, base_vertices, sizeof(base_vertices));

    for (int i = 0; i < 6; i++) {
        updated_vertices[i * 8]     += state->posX; // Update X
        updated_vertices[i * 8 + 1] += state->posY; // Update Y
    }

    glViewport(0, 0, state->width, state->height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLsizei stride = 8 * sizeof(GLfloat);

    glUseProgram(state->simpleShader.program);
    glBindBuffer(GL_ARRAY_BUFFER, state->vboMoving);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(updated_vertices), updated_vertices);

    glEnableVertexAttribArray(state->simpleShader.posLoc);
    glVertexAttribPointer(state->simpleShader.posLoc, 4, GL_FLOAT, GL_FALSE, stride, (const void*)0);
    glEnableVertexAttribArray(state->simpleShader.colorLoc);
    glVertexAttribPointer(state->simpleShader.colorLoc, 4, GL_FLOAT, GL_FALSE, stride, (const void*)(4 * sizeof(GLfloat)));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    eglSwapBuffers(state->display, state->surface);
}


GLuint compile_shader(const char *source, GLenum type) {
    GLuint shader = glCreateShader(type); glShaderSource(shader, 1, &source, NULL); glCompileShader(shader);
    GLint compiled; glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) { char info[512]; glGetShaderInfoLog(shader, 512, NULL, info); printf("Shader Error: %s\n", info); }
    return shader;
}
void create_program(ShaderProgram* sp, const char* vs_src, const char* fs_src) {
    GLuint vs = compile_shader(vs_src, GL_VERTEX_SHADER); GLuint fs = compile_shader(fs_src, GL_FRAGMENT_SHADER);
    sp->program = glCreateProgram(); glAttachShader(sp->program, vs); glAttachShader(sp->program, fs); glLinkProgram(sp->program);
    sp->posLoc = glGetAttribLocation(sp->program, "position"); sp->colorLoc = glGetAttribLocation(sp->program, "color_in"); sp->timeLoc = glGetUniformLocation(sp->program, "u_time");
}
void init_shaders(EsContext *state) {
    const char *vs_1 = "attribute vec4 position; attribute vec4 color_in; varying vec4 color_out; void main() { color_out = color_in; gl_Position = position; }";
    const char *fs_1 = "precision mediump float; varying vec4 color_out; void main() { gl_FragColor = color_out; }";
    create_program(&state->simpleShader, vs_1, fs_1);
    const char *vs_2 = "attribute vec4 position; attribute vec4 color_in; varying vec4 v_pos; void main() { v_pos = position; gl_Position = position; }";
    const char *fs_2 = "precision mediump float; uniform float u_time; varying vec4 v_pos; void main() { gl_FragColor = vec4(0.5 + 0.5*sin(u_time + v_pos.x), 0.5 + 0.5*cos(u_time + v_pos.y), 0.8, 1.0); }";
    create_program(&state->specialShader, vs_2, fs_2);
}
void init_geometry(EsContext *state) {
    glGenBuffers(1, &state->vboMoving); glBindBuffer(GL_ARRAY_BUFFER, state->vboMoving); glBufferData(GL_ARRAY_BUFFER, sizeof(base_vertices), base_vertices, GL_DYNAMIC_DRAW);
    glGenBuffers(1, &state->vboStatic); glBindBuffer(GL_ARRAY_BUFFER, state->vboStatic); glBufferData(GL_ARRAY_BUFFER, sizeof(third_quad_vertices), third_quad_vertices, GL_STATIC_DRAW);
}
void init_ogl(EsContext *state) {
    state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY); eglInitialize(state->display, NULL, NULL);
    static const EGLint attribute_list[] = { EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE };
    EGLConfig config; EGLint num_config; eglChooseConfig(state->display, attribute_list, &config, 1, &num_config);
    eglBindAPI(EGL_OPENGL_ES_API);
    static const EGLint context_attributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    state->context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, context_attributes);
    get_native_display_size(&state->width, &state->height);
    NativeWindowType nativewindow = create_native_window(state->width, state->height);
    state->surface = eglCreateWindowSurface(state->display, config, nativewindow, NULL);
    eglMakeCurrent(state->display, state->surface, state->surface, state->context);
    struct timeval tv; gettimeofday(&tv, NULL); state->startTime = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}


int main(int argc, char* argv[]) {
    bcm_host_init();
    state.posX = 0.0f;
    state.posY = 0.0f;
    state.running = true;

    init_ogl(&state);
    init_shaders(&state);
    init_geometry(&state); // Make sure this creates state.vboMoving

    std::thread inputThread(input_thread_func, &state);

    while (state.running) {
        draw(&state);
        usleep(16000);
    }

    inputThread.join(); // Wait for thread to finish cleanup
    return 0;
}
// pi@raspberrypi:~/andro
