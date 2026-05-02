// core/resource_manager/ass_texture_manager.cpp
#include "stb_image.h"
#include <string>
#include <iostream>

struct RawTextureData {
    unsigned char* pixels;
    int width, height;
};

RawTextureData LoadTextureToMemory(const std::string& filename) {
    int width, height, channels;
    
    // Metal/OpenGL usually expect (0,0) at the bottom for UVs
    stbi_set_flip_vertically_on_load(true); 

    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 4);

    if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return { nullptr, 0, 0 };
    }

    return { data, width, height };
}
