#version 300 es
in vec3 inPosition;
in vec2 inUV;

out vec2 fragUV;

uniform mat4 uProjection;

uniform mat4 uView;

void main() {
    fragUV = inUV;
    gl_Position = uProjection * uView * vec4(inPosition, 1.0);
}