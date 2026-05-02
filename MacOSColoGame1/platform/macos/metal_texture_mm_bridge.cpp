// platform/macos/metal_texture_mm_bridge.cpp
#include "colo_texture.h"
#include <iostream>

// Link to the Objective-C function
extern "C" void* CreateMetalTextureInternal(void* devicePtr, unsigned char* pixels, int width, int height);

bool ColoTexture::LoadMetal(void* devicePtr, unsigned char* pixels, int w, int h) {
    if (pixels == nullptr) {
        std::cerr << "ColoTexture Error: Pixel data is null" << std::endl;
        return false;
    }

    this->mWidth = w;
    this->mHeight = h;

    // Call our bridge function
    // mMetalTexHandle is a void* defined in your header
    this->mMetalTexHandle = CreateMetalTextureInternal(devicePtr, pixels, w, h);

    return (this->mMetalTexHandle != nullptr);
}
