#ifndef colo_game_gosha_math_hpp
#define colo_game_gosha_math_hpp


typedef struct {
    float x, y, z;
} vec3;


typedef struct {
    float x, y;
} vec2;


typedef struct {
    float m[16]; // Column-major order
} mat4;


// Structure to represent a point

/*
typedef struct {
    double x;
    double y;
} Point;
*/
// Function to calculate the centroid of a triangle
inline vec2 calculateCentroid(vec2 p1, vec2 p2, vec2 p3) {
    vec2 centroid;
    centroid.x = (p1.x + p2.x + p3.x) / 3.0;
    centroid.y = (p1.y + p2.y + p3.y) / 3.0;
    return centroid;
}

// Structure to represent a point in 3D space
typedef struct {
    float x;
    float y;
    float z;
	 float w;
} vec4;

// Function to calculate the centroid of a triangle in 3D
inline vec3 calculateCentroid3D(vec3 p1, vec3 p2, vec3 p3) {
    vec3 centroid;
    centroid.x = (p1.x + p2.x + p3.x) / 3.0;
    centroid.y = (p1.y + p2.y + p3.y) / 3.0;
    centroid.z = (p1.z + p2.z + p3.z) / 3.0;
    return centroid;
}

#endif