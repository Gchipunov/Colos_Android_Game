//
//  Renderer.hpp
//  Colo Game
//
//  Created by user on 3/6/26.
//

//#ifndef Renderer_hpp
//#define Renderer_hpp

//#include <stdio.h>

//#endif /* Renderer_hpp */

#ifndef Renderer_hpp
#define Renderer_hpp
/*
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <vector>

class Renderer {
public:
    Renderer(CA::MetalDrawable * const pDrawable, MTL::Device * const pDevice);
    ~Renderer();
    
    void draw() const;

private:
    CA::MetalDrawable * _pDrawable;
    MTL::Device * _pDevice;
    MTL::CommandQueue * _pCommandQueue;
};
*/

#include <memory>

#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalDrawable.hpp>

class Renderer {
public:
  Renderer(MTL::Device * const pDevice);
  ~Renderer();
  void drawFrame(const CA::MetalDrawable * const pDrawable);
private:
  MTL::Device * const _pDevice;
  MTL::CommandQueue * const _pCommandQueue;
  std::unique_ptr<MTL::RenderPipelineState, void(*)(MTL::RenderPipelineState *)> _pRenderPipelineState;
  float _timer;
  
  void buildShaders();
};

#endif /* Renderer_hpp */
