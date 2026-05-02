#pragma once
#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalDrawable.hpp>

class Renderer {
public:
    Renderer(MTL::Device* pDevice);
    ~Renderer();

    // This is where you put your buffer logic for Colo Duo Bagabundos
    void buildBuffers(); 
    
    // The main draw call triggered by RendererAdapter
    void drawFrame(const CA::MetalDrawable* pDrawable, MTL::RenderPassDescriptor* pRpd);

private:
    MTL::Device* _pDevice;
    MTL::CommandQueue* _pCommandQueue;
    MTL::Buffer* _pVertexBuffer; // For [[buffer(5)]]
    MTL::Buffer* _pTimerBuffer;  // For [[buffer(7)]]
    MTL::RenderPipelineState* _pPipelineState;
};
