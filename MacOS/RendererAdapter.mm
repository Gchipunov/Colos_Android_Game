//
//  RendererAdapter.m
//  Colo Game
//
//  Created by user on 3/7/26.
//
//https://github.com/DataDrivenEngineer/metal-videos
//https://github.com/DataDrivenEngineer/metal-cpp-projects/tree/main/metal-cpp-projects
//https://github.com/amyollomani1/GameEngineIOS/blob/main/xcodeMakeWindow/renderer.hpp

//https://github.com/MadLadSquad/UImGuiRendererExamples

//https://github.com/search?q=%23include+%22Metal%2FMetal.hpp%22&type=code

//https://github.com/arcanum-project/game
//https://www.youtube.com/watch?v=qmdx32MjVnY

//#import <Foundation/Foundation.h>
#import "RendererAdapter.h"

@implementation RendererAdapter

- (nonnull instancetype) initWithMTKView:(MTKView *)pView
{
  self = [super init];
  _pRenderer = new Renderer((__bridge MTL::Device *)pView.device);
  return self;
}

-(void)drawInMTKView:(MTKView *)view
{
  _pRenderer->drawFrame((__bridge const CA::MetalDrawable * const)view.currentDrawable);
}

-(void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size
{
}
-(void)dealloc
{
  delete _pRenderer;
}
@end
