#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHISwapChain;

class RHITexture;

/// <summary>
/// RHISwapChain is a physcial device which helps to query device details before creating logical devices.
/// Vulkan : VkPhyscialDevice
/// D3D12 : IDXGIAdapter(n)
/// Metal : MTLDevice
/// </summary>
class RHI_API RHISwapChain
{
public:
	RHISwapChain();
	RHISwapChain(const RHISwapChain&) = delete;
	RHISwapChain& operator=(const RHISwapChain&) = delete;
	RHISwapChain(RHISwapChain&& other) noexcept;
	RHISwapChain& operator=(RHISwapChain&& other) noexcept;
	~RHISwapChain();

	void Reset(std::unique_ptr<IRHISwapChain>&& impl);
	std::vector<RHITexture> GetBackBufferTextures() const;

private:
	IRHISwapChain* m_pImpl = nullptr;
};

}