#include "stb_image_loader.h"
//#define STB_IMAGE_IMPLEMENTATION // in stb_imag_impl.cpp file
#include "stb_image.h"
// Colos_Android_Game/MacOSColoGame1/core/resource_manager
//stb_image_loader.cpp
// This struct acts as the "handshake" between CPU and GPU
TextureData LoadImageToRAM(const std::vector<unsigned char>& compressedData) {
    TextureData result = { nullptr, 0, 0, 0 };
    int channels;

    // We force 4 channels for RGBA consistency across GL and Metal
    result.pixels = stbi_load_from_memory(
        compressedData.data(), 
        compressedData.size(), 
        &result.width, 
        &result.height, 
        &channels, 4
    );

    return result;
}

void FreeImageRAM(unsigned char* pixels) {
    if (pixels) stbi_image_free(pixels);
}
