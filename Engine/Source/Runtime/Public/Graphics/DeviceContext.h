#pragma once

#include <Core/Core.h>
#include <RHI/RHI.h>

#include <optional>
#include <vector>

namespace ow
{

class DeviceContext
{
public:
	DeviceContext() = delete;
	GFX_API explicit DeviceContext(RHIBackend backend, void* pNativeWindow, uint32 width, uint32 height);
	DeviceContext(const DeviceContext&) = delete;
	DeviceContext& operator=(const DeviceContext&) = delete;
	DeviceContext(DeviceContext&& other) = default;
	DeviceContext& operator=(DeviceContext&& other) = default;
	GFX_API ~DeviceContext();

	GFX_API void Update();

private:
	void LoadRHIModule(RHIBackend backend);
	void CreateRHIInstance();
	void CreateLogicalDevice();
	void CreateCommandQueues(const std::vector<RHICommandQueueCreateInfo*>& queueCIs);
	void CreateSwapChain(void* pNativeWindow, uint32 width, uint32 height);

private:
	std::optional<int32> FindBestRHIAdapter(const std::vector<IRHIAdapter*>& adapters);
	std::optional<int32> FindBestCommandQueue(RHICommandType commandType, const std::vector<RHICommandQueueCreateInfo*>& createInfos);
	std::vector<RHICommandQueueCreateInfo*> FindBestCommandQueues(const std::vector<RHICommandType>& commandTypes, const std::vector<RHICommandQueueCreateInfo*>& createInfos);

private:
	static constexpr int32 RHICommandTypeCount = EnumCount<RHICommandType>();
	static constexpr int32 BackBufferCount = 2;
	
	BitFlags<RHIFeatures> m_features;
	RHIDebugMode m_debugMode = RHIDebugMode::Enabled;
	RHIValidationMode m_validationMode = RHIValidationMode::GPU;

	RefCountPtr<IRHIModule> m_pRHIModule;
	RefCountPtr<IRHIInstance> m_pInstance;
	RefCountPtr<IRHIDevice> m_pDevice;
	RefCountPtr<IRHISwapChain> m_pSwapChain;
	RefCountPtr<IRHICommandPool> m_pCommandPools[RHICommandTypeCount];
	RefCountPtr<IRHICommandQueue> m_pCommandQueues[RHICommandTypeCount];
	RefCountPtr<IRHIFence> m_pCommandQueueFences[RHICommandTypeCount];

	RefCountPtr<IRHICommandBuffer> m_pSetupCommandBuffer;
	RefCountPtr<IRHICommandBuffer> m_pCommandBuffers[BackBufferCount];
	RefCountPtr<IRHIFence> m_pFrameFences[BackBufferCount];
	RefCountPtr<IRHISemaphore> m_acquireImageSemaphores[BackBufferCount];
	RefCountPtr<IRHISemaphore> m_renderCompleteSemaphores[BackBufferCount];
};

}