#pragma once

#include <Core/HAL/APIDefinition.h>

#include <vector>

namespace ow
{

class IRHIInstance;
struct RHIInstanceCreateInfo;

enum class RHIBackend;

class RHIAdapter;
class RHISurface;

/// <summary>
/// RHIInstance is an entry point to access core apis, enable debug layers.
/// Vulkan : VkInstance
/// D3D12 : IDXGIFactory(n)
/// Metal : CAMetalLayer
/// </summary>
class RHI_API RHIInstance
{
public:
	static RHIInstance Create(const RHIInstanceCreateInfo& createInfo);

public:
	RHIInstance();
	RHIInstance(const RHIInstance&) = delete;
	RHIInstance& operator=(const RHIInstance&) = delete;
	RHIInstance(RHIInstance&& other) noexcept;
	RHIInstance& operator=(RHIInstance&& other) noexcept;
	~RHIInstance();

	void Dump();

	RHIBackend GetBackend() const;
	void* GetHandle() const;

	std::vector<RHIAdapter> EnumerateAdapters() const;
	RHISurface CreateSurface(void* pPlatformWindowHandle, void* pPlatformInstanceHandle) const;

private:
	IRHIInstance* m_pImpl = nullptr;
};

}