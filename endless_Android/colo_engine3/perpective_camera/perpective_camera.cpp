//perspective_camera.cpp

#include "perpective_camera.h"

PerspectiveCamera::PerspectiveCamera(vec3 position, vec3 up, float yaw, float pitch) 
    : Front({0.0f, 0.0f, -1.0f}), Yaw(yaw), Pitch(pitch) {
    Position = position;
    WorldUp = up;
    UpdateVectors();
}

void PerspectiveCamera::UpdateVectors() {
    float yawRad = Yaw * (3.14159265f / 180.0f);
    float pitchRad = Pitch * (3.14159265f / 180.0f);

    // Calculate the new Front vector
    Front.x = cosf(yawRad) * cosf(pitchRad);
    Front.y = sinf(pitchRad);
    Front.z = sinf(yawRad) * cosf(pitchRad);
    
    // Normalize and recalculate Right/Up
    Front = Normalize(Front); 
    Right = Normalize(CrossProduct(Front, WorldUp));
    Up    = Normalize(CrossProduct(Right, Front));
}

void PerspectiveCamera::GetViewMatrix(float* m) {
    vec3 zAxis = { -Front.x, -Front.y, -Front.z }; // OpenGL lookDir is -z
    vec3 xAxis = Right;
    vec3 yAxis = Up;

    // Column 1
    m[0] = xAxis.x; m[1] = yAxis.x; m[2] = zAxis.x; m[3] = 0.0f;
    // Column 2
    m[4] = xAxis.y; m[5] = yAxis.y; m[6] = zAxis.y; m[7] = 0.0f;
    // Column 3
    m[8] = xAxis.z; m[9] = yAxis.z; m[10] = zAxis.z; m[11] = 0.0f;
    // Column 4 (Translation)
    m[12] = -DotProduct(xAxis, Position);
    m[13] = -DotProduct(yAxis, Position);
    m[14] = -DotProduct(zAxis, Position);
    m[15] = 1.0f;
}

// Math Helpers
vec3 PerspectiveCamera::Normalize(vec3 v) {
    float mag = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return { v.x / mag, v.y / mag, v.z / mag };
}

vec3 PerspectiveCamera::CrossProduct(vec3 a, vec3 b) {
    return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}

float PerspectiveCamera::DotProduct(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}