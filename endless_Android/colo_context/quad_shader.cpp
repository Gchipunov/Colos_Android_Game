
#include "quad_shader.h"

ColoQuadShaderManager::ColoQuadShaderManager(AAssetManager* assetMgr)
{
	m_assetMgr = assetMgr;
	
	
}

ColoQuadShaderManager::~ColoQuadShaderManager()
{
	
	
}


GLuint ColoQuadShaderManager::compile_shader(const char *source, GLenum type) {
	if (!source || source[0] == '\0') {
        printf("ERROR: Shader source is empty or NULL!\n");
        return 0;
    }
	
	// Get the actual length to avoid relying solely on the null terminator
    GLint length = (GLint)strlen(source);
	printf("Compiling Shader with length: %d\n",length);
	
    GLuint shader = glCreateShader(type);
   // glShaderSource(shader, 1, &source, NULL);
   // Passing the length explicitly is safer for the RPi driver
    glShaderSource(shader, 1, &source, &length);
	
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char* infoLog = (char*)malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
          //  fprintf(stderr, "=== SHADER COMPILE ERROR (%s) ===\n%s\n", 
           //         (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"), infoLog);
		   // Print to BOTH stderr and stdout to make sure we see it in the Pi terminal
            printf("\n--- GLSL COMPILE ERROR (%s) ---\n%s\n-------------------------------\n", 
                   (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"), infoLog);
            free(infoLog);
        }
		else {
            // This happens if the driver rejected the source entirely
            printf("DRIVER REJECTED SOURCE: Check for hidden non-ASCII characters.\n");
        }
		printf("compile_shader: glDeleteShader\n"); 
        glDeleteShader(shader);
        return 0;
    }
	printf("compile_shader: compiled shader:%d\n",shader); 
//	program = shader;
	

	
	
    return shader;
}

//void ColoQuadShaderManager::init_shaders(EsContext *state) {
	void ColoQuadShaderManager::init_shaders() {
    const char *vs_src =
        "attribute vec4 position;" // The shader now uses vec4 for everything. This is great for the Raspberry Pi Zero as it keeps the GPU's registers aligned.
        "attribute vec4 color_in;"
		"attribute vec4 uv_in;"
        "varying vec4 v_color;" // : DO NOT CHANGE from vec4
        "varying vec4 v_pos;" // Note: do not changed to vec2 for the rainbow logic : DO NOT CHANGE vec4
		"varying vec4 v_uv;"  // double UV coordinates for multiple texturing or other special uber shader use cases: DO NOT CHANGE vec4
    "uniform sampler2D u_texture; "// Sampling the animation data
"uniform int u_mode;"
"uniform float u_time;  "

	  "void main() {"
        "  v_color = color_in;"
      //  "  v_pos = position.xy;"
	   // "  v_pos = position;"
		 "  v_uv = uv_in;"
		 
		 
		 
       // "  gl_Position = position;"
	   
	   " vec4 currentPos = position;"

    // Mode 2: Fart/Gas Shader with Vertex Animation
     "if (u_mode == 2) {"
        // Use UV and time to sample the noise texture
       "  vec2 scrollingUV = uv_in.xy + vec2(u_time * 0.5, u_time * 0.3);"
       "  vec4 noise = texture2D(u_texture, scrollingUV);"
        
        // Displace position based on noise (the VAT logic)
       "  currentPos.x += (noise.r - 0.5) * 0.1;"
       "  currentPos.y += (noise.g - 0.5) * 0.1;"
     " } "

      " v_pos = currentPos;"
     " gl_Position = currentPos;"
	
        "}";
const char *fs_src =
        "precision mediump float;"
        "uniform float u_time;"
        "uniform int u_mode;" 
		"uniform sampler2D u_texture;" // Added for later texture use
        "varying vec4 v_color;" // : DO NOT CHANGE vec4
        "varying vec4 v_pos;"     // : DO NOT CHANGE vec4
		"varying vec4 v_uv;" 
        "void main() {"
    //    "  if (u_mode == 1) {"
     //   "    gl_FragColor = vec4(0.5 + 0.5*sin(u_time + v_pos.x * 5.0), 0.5 + 0.5*cos(u_time + v_pos.y * 5.0), 0.8, 1.0);"
     //   "  } else {"
     //   "    gl_FragColor = v_color;"
     //   "  }"
	 "  if (u_mode == 1) {" // Rainbow
    "    gl_FragColor = vec4(0.5 + 0.5*sin(u_time + v_pos.x * 5.0), 0.5 + 0.5*cos(u_time + v_pos.y * 5.0), 0.8, 1.0);"
    "  } else if (u_mode == 2) {" // Fart/Gas Shader
   //  "    float pulse = 0.7 + 0.3 * sin(u_time * 10.0);"
   //  "    float green = v_color.g * pulse;"
   //  "    gl_FragColor = vec4(v_color.r, green, v_color.b, 0.8);" // Slight transparency
   // Fart/Gas Shader with Glow
        // Sample noise for flickering
       " vec4 noise = texture2D(u_texture, v_uv.xy + vec2(u_time * 0.1));"
        
        // Calculate distance from center for glow (v_uv ranges 0 to 1)
       " float dist = distance(v_uv.xy, vec2(0.5, 0.5));"
       " float glow = 1.0 - smoothstep(0.0, 0.5, dist);"
        
        // Pulse the alpha and green channel
      "  float pulse = 0.8 + 0.2 * sin(u_time * 8.0 + noise.r);"
      "  vec3 gasColor = vec3(0.1, 0.9, 0.2) * pulse;"
        
      "  gl_FragColor = vec4(gasColor, glow * 0.8);"
		
   
    "  } else if (u_mode == 3) {" // Texture Mode
    "    gl_FragColor = texture2D(u_texture, v_uv.xy) * v_color;"
    "  } "
	"else if (u_mode == 4) {" // THE SHADERTOY FART SLOT
    "vec2 uv = v_uv.xy;"
    
    // Procedural "Fart" Swirl Math
    "float n = fract(sin(dot(uv, vec2(12.9898, 78.233) + u_time * 0.1)) * 43758.5453);"
    "float swirl = sin(uv.x * 10.0 + u_time + n) * cos(uv.y * 10.0 - u_time);"
    
    // Toxic Green Palette
   " vec3 color = vec3(0.2, 0.8 * (0.5 + 0.5 * swirl), 0.1);"
    
    // Add a bit of "stink" jitter
    "float alpha = smoothstep(0.1, 0.9, swirl + 0.5);"
    "gl_FragColor = vec4(color, alpha * 0.9);"
    " }  "

	
	"else {" // Standard Color
    "    gl_FragColor = v_color;"
    "  }"
	 
        "}";
		
    const char *fs_src_v5 =
        "precision mediump float;"
        "uniform float u_time;"
        "uniform int u_mode;" 
		"uniform sampler2D u_texture;" // Added for later texture use
        "varying vec4 v_color;" // : DO NOT CHANGE vec4
        "varying vec4 v_pos;"     // : DO NOT CHANGE vec4
		"varying vec4 v_uv;" 
        "void main() {"
    //    "  if (u_mode == 1) {"
     //   "    gl_FragColor = vec4(0.5 + 0.5*sin(u_time + v_pos.x * 5.0), 0.5 + 0.5*cos(u_time + v_pos.y * 5.0), 0.8, 1.0);"
     //   "  } else {"
     //   "    gl_FragColor = v_color;"
     //   "  }"
	 "  if (u_mode == 1) {" // Rainbow
    "    gl_FragColor = vec4(0.5 + 0.5*sin(u_time + v_pos.x * 5.0), 0.5 + 0.5*cos(u_time + v_pos.y * 5.0), 0.8, 1.0);"
    "  } else if (u_mode == 2) {" // Fart/Gas Shader
    "    float pulse = 0.7 + 0.3 * sin(u_time * 10.0);"
    "    float green = v_color.g * pulse;"
    "    gl_FragColor = vec4(v_color.r, green, v_color.b, 0.8);" // Slight transparency
    "  } else if (u_mode == 3) {" // Texture Mode
    "    gl_FragColor = texture2D(u_texture, v_uv.xy) * v_color;"
    "  } else {" // Standard Color
    "    gl_FragColor = v_color;"
    "  }"
	 
        "}";
// 1. Try to load from external files first
 //   std::string file_vs = ColoShaderLoader::LoadShaderSource("shaders/uber.vert");
 //   std::string file_fs = ColoShaderLoader::LoadShaderSource("shaders/uber.frag");
//ColoShaderLoader::loadTextAsset
 std::string file_vs = ColoAssetShaderLoader::loadTextAsset(m_assetMgr,"Quad1shader.vert");
 std::string file_fs = ColoAssetShaderLoader::loadTextAsset(m_assetMgr,"Quad1shader.frag");

    const char *final_vs_src;
    const char *final_fs_src;

    // 2. Fallback logic: If files are missing, use your hardcoded strings
    if (!file_vs.empty() && !file_fs.empty()) {
        printf("Loading shaders from files...\n");
        final_vs_src = file_vs.c_str();
        final_fs_src = file_fs.c_str();
    } else {
        printf("Shader files not found, using internal hardcoded 'Uber Shader'...\n");
		// version 1 OpenGLES 2.0
        // Your existing hardcoded strings
        static const char *vs_src = 
            "attribute vec4 position;"
            "attribute vec4 color_in;"
            "attribute vec4 uv_in;"
            "varying vec4 v_color;"
            "varying vec4 v_pos;"
            "varying vec4 v_uv;"
            "uniform sampler2D u_texture;"
            "uniform int u_mode;"
            "uniform float u_time;"
            "void main() {"
            "  v_color = color_in;"
            "  v_uv = uv_in;"
            "  vec4 currentPos = position;"
            "  if (u_mode == 2) {"
            "    vec2 scrollingUV = uv_in.xy + vec2(u_time * 0.5, u_time * 0.3);"
            "    vec4 noise = texture2D(u_texture, scrollingUV);"
            "    currentPos.x += (noise.r - 0.5) * 0.1;"
            "    currentPos.y += (noise.g - 0.5) * 0.1;"
            "  }"
            "  v_pos = currentPos;"
            "  gl_Position = currentPos;"
            "}";

        static const char *fs_src = 
            "precision mediump float;"
            "uniform float u_time;"
            "uniform int u_mode;"
            "uniform sampler2D u_texture;"
            "varying vec4 v_color;"
            "varying vec4 v_pos;"
            "varying vec4 v_uv;"
            "void main() {"
            "  if (u_mode == 1) {"
            "    gl_FragColor = vec4(0.5 + 0.5*sin(u_time + v_pos.x * 5.0), 0.5 + 0.5*cos(u_time + v_pos.y * 5.0), 0.8, 1.0);"
            "  } else if (u_mode == 2) {"
            "    vec4 noise = texture2D(u_texture, v_uv.xy + vec2(u_time * 0.1));"
            "    float dist = distance(v_uv.xy, vec2(0.5, 0.5));"
            "    float glow = 1.0 - smoothstep(0.0, 0.5, dist);"
            "    float pulse = 0.8 + 0.2 * sin(u_time * 8.0 + noise.r);"
            "    vec3 gasColor = vec3(0.1, 0.9, 0.2) * pulse;"
            "    gl_FragColor = vec4(gasColor, glow * 0.8);"
            "  } else if (u_mode == 4) {"
            "    vec2 uv = v_uv.xy;"
            "    float n = fract(sin(dot(uv, vec2(12.9898, 78.233) + u_time * 0.1)) * 43758.5453);"
            "    float swirl = sin(uv.x * 10.0 + u_time + n) * cos(uv.y * 10.0 - u_time);"
            "    vec3 color = vec3(0.2, 0.8 * (0.5 + 0.5 * swirl), 0.1);"
            "    gl_FragColor = vec4(color, smoothstep(0.1, 0.9, swirl + 0.5) * 0.9);"
            "  } else {"
            "    gl_FragColor = v_color;"
            "  }"
            "}";
        
		
		   static const char *vs_src3 = 
            "#version 300 es "
   " in vec3 inPosition;"
  "in vec2 inUV;"

  "out vec2 fragUV; "

  "uniform mat4 uProjection;"

  "void main() { "
   " fragUV = inUV;"
  "  gl_Position = uProjection * vec4(inPosition, 1.0);"
 "}";

        static const char *fs_src3 = 
            "#version 300 es"
"precision mediump float;"

"in vec2 fragUV;"

"uniform sampler2D uTexture;"

"out vec4 outColor;"

"void main() {"
 "   outColor = texture(uTexture, fragUV);"

"};";
        
		
      //  final_vs_src = vs_src;
     //   final_fs_src = fs_src;
	        final_vs_src = vs_src3;
            final_fs_src = fs_src3;
    }

    // 3. Compile and Link using your existing functions
    GLuint vs = compile_shader(final_vs_src, GL_VERTEX_SHADER);
    GLuint fs = compile_shader(final_fs_src, GL_FRAGMENT_SHADER);
	
 //   GLuint vs = compile_shader(vs_src, GL_VERTEX_SHADER);
//    GLuint fs = compile_shader(fs_src, GL_FRAGMENT_SHADER);

   program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    // --- CHECK LINK STATUS ---
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char* infoLog = (char*)malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(program, infoLen, NULL, infoLog);
            fprintf(stderr, "=== PROGRAM LINK ERROR ===\n%s\n", infoLog);
            free(infoLog);
        }
    }
	
	bShaderCompiled = true;
	
    attr_inPosition = glGetAttribLocation(program, "inPosition");
    attr_inUV = glGetAttribLocation(program, "inUV");
//	  state->mainShader.uvLoc = glGetAttribLocation(state->mainShader.program, "uv_in");
   uniform_uProjection = glGetUniformLocation(program, "uProjection");
//    state->mainShader.modeLoc = glGetUniformLocation(state->mainShader.program, "u_mode");
}


// Helper to safely reload without leaking memory
//void ColoQuadShaderManager::load_or_reload_shaders(EsContext *state) {
	
	void ColoQuadShaderManager::load_or_reload_shaders() {
	printf("load_or_reload_shaders\n");
	
    // 1. Load sources from file
    std::string file_vs = ColoAssetShaderLoader::loadTextAsset(m_assetMgr, "shaders/uber.vert");
    std::string file_fs = ColoAssetShaderLoader::loadTextAsset(m_assetMgr, "shaders/uber.frag");
// DEBUG: Check string sizes
    printf("VS size: %d, FS size: %d\n", (int)file_vs.size(), (int)file_fs.size());
    if (file_vs.empty() || file_fs.empty()) {
        fprintf(stderr, "Hot-Reload Failed: Could not find shader files.\n");
		printf("Hot-Reload Failed: Could not find shader files.\n");
        return;
    }

    // 2. Compile new shaders
    GLuint vs = compile_shader(file_vs.c_str(), GL_VERTEX_SHADER);
    GLuint fs = compile_shader(file_fs.c_str(), GL_FRAGMENT_SHADER);

    if (vs == 0 || fs == 0) 
	{
		printf("Hot-Reload Failed: Compile error already printed in compile_shader.\n");
		return; // Compile error already printed in compile_shader
	}
	
    // 3. Create a temporary program to test linking
    GLuint newProgram = glCreateProgram();
    glAttachShader(newProgram, vs);
    glAttachShader(newProgram, fs);
    glLinkProgram(newProgram);

    GLint linked;
    glGetProgramiv(newProgram, GL_LINK_STATUS, &linked);
    if (!linked) {
        // Link error printed here
		printf("Hot Reload Failed: Link error printed here\n");
        glDeleteProgram(newProgram);
        return;
    }

    // 4. Success! Cleanup old program and swap
    if (program != 0) {
        glDeleteProgram(program);
    }
    program =  newProgram;
	bShaderCompiled = true;
	
    //state->mainShader.program = newProgram;

    // 5. Re-cache locations (very important as they might change)
   // state->mainShader.posLoc = glGetAttribLocation(newProgram, "position");
   // state->mainShader.colorLoc = glGetAttribLocation(newProgram, "color_in");
   // state->mainShader.uvLoc = glGetAttribLocation(newProgram, "uv_in");
  //  state->mainShader.timeLoc = glGetUniformLocation(newProgram, "u_time");
   // state->mainShader.modeLoc = glGetUniformLocation(newProgram, "u_mode");

    printf("Shaders Hot-Reloaded Successfully!\n");
}


void ColoQuadShaderManager::Cleanup() {
    if (program != 0) {
        glDeleteProgram(program);
        program = 0;
    }
    bShaderCompiled = false;
}
