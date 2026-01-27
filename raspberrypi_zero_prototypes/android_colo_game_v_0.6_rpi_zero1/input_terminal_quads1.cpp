// quads_shade1.cpp
// Georgiy Chipunov -  Basic Quads Movement Demo, need fix if enter other than 0-9, Press CTRL+C
// Compilation command:
// g++ -o input_terminal_quads1 input_terminal_quads1.cpp -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host -lm -lrt

// g++ -O2 -std=c++11 input_terminal_quads1.cpp -o input_terminal_quads1 \
-I/opt/vc/include \
-I/opt/vc/include/interface/vcos/pthreads \
-I/opt/vc/include/interface/vmcs_host/linux \
-L/opt/vc/lib \
-lGLESv2 -lEGL -lbcm_host -lm -lrt -lpthread

// Prompt Gemini:
// Code in C++ 11, raspberry pi zero armv6 OpenGLES 2.0 ,
  // get input after I run ./ pi@raspberrypi:~/android_colo_game_v_0.6_rpi_zero1 $ ./quad_move2_bard2
//, modify code:
// source : quads_shade1
// https://gemini.google.com/app/b75894deb2a5704d
// g++ -std=c++11 quad_move2.cpp -o quad_move2_bard2 -lbrcmGLESv2 -lbrcmEGL -lbcm_host -lpthread -I/opt/vc/include -L/opt/vc/lib

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <bcm_host.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <vector>
#include <iostream>
#include <thread>  // Added for C++11 threading
#include <atomic>  // Added for thread-safe variables

// Struct to hold shader program info
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

    // --- NEW INPUT VARIABLES ---
    std::atomic<float> moveSpeed; // Thread-safe float
    std::atomic<bool> running;
} EsContext;

EsContext state;

// ... (base_vertices and third_quad_vertices remain the same as your original) ...
GLfloat base_vertices[] = {
    -0.5f,  0.5f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.1f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     0.1f, -0.1f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     0.1f, -0.1f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     0.1f,  0.5f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -0.1f, -0.2f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
    -0.1f, -0.8f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.8f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
    -0.1f, -0.2f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.8f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.2f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
};

GLfloat third_quad_vertices[] = {
    0.3f,  0.8f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    0.3f,  0.3f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    0.8f,  0.3f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    0.3f,  0.8f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    0.8f,  0.3f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    0.8f,  0.8f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
};

// --- INPUT THREAD FUNCTION ---
void input_thread_func(EsContext *ctx) {
    float new_speed;
    while (ctx->running) {
        std::cout << "\nEnter move speed (e.g., 1.0 to 10.0, or 0 to exit): " << std::flush;
        if (std::cin >> new_speed) {
            if (new_speed == 0) {
                ctx->running = false;
                break;
            }
            ctx->moveSpeed = new_speed;
            std::cout << "Speed set to: " << new_speed << std::endl;
        }
    }
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

void draw(EsContext *state) {
    float t = get_time_s(state->startTime);
    // Use the moveSpeed variable updated by the input thread
    float offset = sinf(t * state->moveSpeed) * 0.5f;

    GLfloat updated_vertices[96];
    memcpy(updated_vertices, base_vertices, sizeof(base_vertices));
    for (int i = 0; i < 12; i++) { updated_vertices[i * 8] += offset; }

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
    glDrawArrays(GL_TRIANGLES, 0, 12);

    glUseProgram(state->specialShader.program);
    glUniform1f(state->specialShader.timeLoc, t);
    glBindBuffer(GL_ARRAY_BUFFER, state->vboStatic);
    glEnableVertexAttribArray(state->specialShader.posLoc);
    glVertexAttribPointer(state->specialShader.posLoc, 4, GL_FLOAT, GL_FALSE, stride, (const void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    eglSwapBuffers(state->display, state->surface);
}

int main(int argc, char* argv[]) {
    bcm_host_init();

    // Initialize state
    state.moveSpeed = 3.0f; // Default speed
    state.running = true;

    init_ogl(&state);
    init_shaders(&state);
    init_geometry(&state);

    // Start the input thread
    std::thread inputThread(input_thread_func, &state);
    inputThread.detach(); // Let it run independently

    while (state.running) {
        draw(&state);
        usleep(16000);
    }

    return 0;
}
