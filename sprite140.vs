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