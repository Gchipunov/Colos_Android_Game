// platform/macos/metal_texture.mm
#import <Metal/Metal.h>
#include <vector>

// Forward declaration of the C linkage function
extern "C" void* CreateMetalTextureInternal(void* devicePtr, unsigned char* pixels, int width, int height) {
    id<MTLDevice> device = (__bridge id<MTLDevice>)devicePtr;
    
    // Define the descriptor explicitly (No 'auto')
    MTLTextureDescriptor *descriptor = [MTLTextureDescriptor 
        texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm
                                     width:(NSUInteger)width
                                    height:(NSUInteger)height
                                 mipmapped:NO];
    
    // Create the texture
    id<MTLTexture> texture = [device newTextureWithDescriptor:descriptor];
    
    // Upload the data
    MTLRegion region = MTLRegionMake2D(0, 0, (NSUInteger)width, (NSUInteger)height);
    NSUInteger bytesPerRow = (NSUInteger)(4 * width);
    
    [texture replaceRegion:region 
               mipmapLevel:0 
                 withBytes:pixels 
               bytesPerRow:bytesPerRow];
    
    // Return as a raw pointer to be stored in your C++ class
    return (__bridge_retained void*)texture;
}
