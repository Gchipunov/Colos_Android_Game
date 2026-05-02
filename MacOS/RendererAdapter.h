//
//  RendererAdapter.h
//  Colo Game
//
//  Created by user on 3/7/26.
//

/*
#import "QuartzCore/CAMetalLayer.h"
#import "Metal/MTLDevice.hpp"
#import "Renderer.hpp"

@interface RendererAdapter :NSObject
{
    Renderer *_pRenderer;
    
}
-(void)draw:(id <CAMetalDrawable>) drawable device: (id <MTLDevice>) device;
@end
*/
#import <QuartzCore/CAMetalLayer.h>
#import <Metal/MTLDevice.h>
#import <MetalKit/MTKView.h>

#import "Renderer.hpp"

@interface RendererAdapter : NSObject<MTKViewDelegate>
{
  Renderer * _pRenderer;
}
- (nonnull instancetype) initWithMTKView:(MTKView * _Nonnull )pView;
@end
