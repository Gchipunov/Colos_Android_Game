#include "ColoEngine.h"

void ColoEngine::buildBuffers()
{
  const std::vector<float> triangle = {
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.0f, -1.0f, 0.0f,
// -0.5f, -1.0f, 0.0f,
  
  };
  
  const std::vector<ushort> indices = {
0 , 1, 2,

  // 2 , 3 , 0 or 0, 2 ,3 
  };


  // Creation (inside buildBuffers)
_pIndexBuffer = _pDevice->newBuffer(indices.data(), 
                                    indices.size() * sizeof(uint16_t), 
                                    MTL::ResourceStorageModeShared);
  
}
