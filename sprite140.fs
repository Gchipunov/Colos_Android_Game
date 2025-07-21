 #version 140
	
	uniform float fragLoopDuration;
uniform float time;

	uniform vec2 iResolution;
	
	uniform sampler2D ourTexture;

	
	in vec4 v_colour;
	in vec3 v_pos;
	in vec2 TexCoord;
    in float v_animationState;
	in float v_animationFrame;
	in float v_shaderType;

	out vec4 color;

	
    

	const vec4 firstColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 secondColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
const float  minX = -2.5;
const float minY = -2.0;
const float maxX =  1.5;
const float maxY =  2.0 ;
    void main() 
    {
		float x = gl_FragCoord.x;
        float y = gl_FragCoord.y;

        vec2 c = vec2((x* (maxX-minX) / iResolution.x + minX), (y*(maxY-minY)/ iResolution.y + minY));
        vec2 z = c;

		
		    float lerpValue = gl_FragCoord.y / 500.0f;

		 float currTime = mod(time, fragLoopDuration);
    float currLerp = currTime / fragLoopDuration;
		
		vec4 thridColor = vec4(z.x, z.y, v_colour.b, 1.0f);
		
        color = vec4(v_colour.r, v_colour.g, v_colour.b, 1); // white color
		    color = mix(thridColor, secondColor, currLerp);
			
			
			vec2 TexCoord2 = TexCoord;
	
color = texture(ourTexture, TexCoord2) * vec4(color);  


    
    }