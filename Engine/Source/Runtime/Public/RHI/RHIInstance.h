#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHIAdapter.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHIInstance;
struct RHIInstanceCreateInfo;

class RHIAdapter;

/// <summary>
/// RHIInstance is an entry point to access core apis, enable debug layers.
/// Vulkan : VkInstance
/// D3D12 : IDXGIFactory(n)
/// Metal : CAMetalLayer
/// </summary>
class RHI_API RHIInstance
{
public:
	RHIInstance();
	RHIInstance(const RHIInstance&) = delete;
	RHIInstance& operator=(const RHIInstance&) = delete;
	RHIInstance(RHIInstance&& other) noexcept;
	RHIInstance& operator=(RHIInstance&& other) noexcept;
	~RHIInstance();

	void Init(const RHIInstanceCreateInfo& createInfo);
	void Dump();

	RHIBackend GetBackend() const;
	void* GetHandle() const;

	std::vector<std::unique_ptr<RHIAdapter>> EnumAdapters() const;

private:
	IRHIInstance* m_pImpl = nullptr;
};

}