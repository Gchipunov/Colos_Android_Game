// macos_platform.h
#ifndef MACOS_PLATFORM_GLOBAL_H
#define MACOS_PLATFORM_GLOBAL_H

//#include "../../colo_game_platform.h"

struct Vertex {
    simd::float2 position;
    simd::float2 texCoord;
};
struct InstanceData {
    simd::float2 position; // Screen position
    simd::float2 scale;    // Size of the sprite
    simd::float4 uvOffset; // [x, y, width, height] inside the spritesheet
};


#endif
