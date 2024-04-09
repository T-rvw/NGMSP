#include "D3D12SwapChain.h"

#include "D3D12Texture.h"

#include <RHI/RHITexture.h>
#include <RHI/RHITypes.h>

namespace ow
{

std::vector<RHITexture> D3D12SwapChain::GetBackBufferTextures() const
{
    std::vector<RHITexture> rhiTextures;
    return rhiTextures;
}

}