#ifndef STB_IMAGE_LOADER_H
#define STB_IMAGE_LOADER_H

#include <vector>

struct TextureData {
    unsigned char* pixels;
    int width;
    int height;
    int channels; // Usually 4 for your RGBA setup
};

// Handshake functions
TextureData LoadImageToRAM(const std::vector<unsigned char>& compressedData);
void FreeImageRAM(unsigned char* pixels);

#endif
