#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include <math.h>

struct vec3 {
    float x, y, z;
};

class PerspectiveCamera {
public:
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;

    float Yaw;
    float Pitch;

    PerspectiveCamera(vec3 position = {0.0f, 0.0f, 0.0f}, 
                      vec3 up = {0.0f, 1.0f, 0.0f}, 
                      float yaw = -90.0f, 
                      float pitch = 0.0f);

    void UpdateVectors();
    void GetViewMatrix(float* outMatrix);

private:
    // Basic math helpers
    vec3 Normalize(vec3 v);
    vec3 CrossProduct(vec3 v1, vec3 v2);
    float DotProduct(vec3 v1, vec3 v2);
};

#endif
