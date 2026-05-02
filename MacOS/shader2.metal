#include <metal_stdlib>
using namespace metal;
// // https://github.com/amengede/getIntoMetalDev  09-textures
// 1. Define the interface between Vertex and Fragment
struct RasterizerData {
    float4 position [[position]]; // Required for vertex shaders
    float timer;                  // Will be interpolated across pixels
    uint vertexID [[flat]];       // [[flat]] prevents interpolation (useful for IDs)
};

[[vertex]] 
RasterizerData vertexShader(
    const device packed_float3 * triangleVertices [[buffer(5)]],
    const uint vertexIndex [[vertex_id]], // Changed to uint for standard indexing
    const constant float * timer [[buffer(7)]])
{
    RasterizerData out;

    float4x4 mat = float4x4(1.0f);
    mat[3][1] = sin(*timer);
    
    // Set the output position
    out.position = mat * float4(triangleVertices[vertexIndex], 1.0f);
    
    // 2. Pass the variables through
    out.timer = *timer;
    out.vertexID = vertexIndex;

    return out;
}

[[fragment]] 
float4 fragmentShader(RasterizerData in [[stage_in]]) {
    // 3. Access the data using the 'in' variable
    // Example: use the timer to pulse the brightness
    float pulse = sin(in.timer) * 0.5 + 0.5;
    
    // Example: color based on vertex ID (useful for debugging)
    if (in.vertexID % 3 == 0) {
        return float4(1.0 * pulse, 0.0, 1.0, 1.0); // Pink/Purple pulse
    }
    
    return float4(0.0, 1.0 * pulse, 1.0, 1.0); // Cyan pulse
}
