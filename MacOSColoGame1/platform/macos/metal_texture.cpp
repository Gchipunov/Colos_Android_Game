// platform/macos/metal_texture.cpp
#include <Metal/Metal.hpp>
#include "Renderer.hpp" // Assuming this has your MTL::Device

MTL::Texture* CreateMetalTexture(MTL::Device* device, unsigned char* pixelData, int width, int height) {
    // 1. Define the texture descriptor
    MTL::TextureDescriptor* pDesc = MTL::TextureDescriptor::alloc()->init();
    pDesc->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
    pDesc->setWidth(width);
    pDesc->setHeight(height);
    pDesc->setUsage(MTL::TextureUsageShaderRead);

    // 2. Create the texture object
    MTL::Texture* pTexture = device->newTexture(pDesc);

    // 3. Upload the raw data
    MTL::Region region = MTL::Region(0, 0, width, height);
    NS::UInteger bytesPerRow = 4 * width;

    pTexture->replaceRegion(region, 0, pixelData, bytesPerRow);

    pDesc->release();
    return pTexture;
}
