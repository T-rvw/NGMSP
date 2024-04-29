#pragma once

#include <Core/Core.h>
#include <RHI/RHI.h>

#include <optional>

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
	void CreateCommandQueues(const Vector<RHICommandQueueCreateInfo*>& queueCIs);
	void CreateSwapChain(void* pNativeWindow, uint32 width, uint32 height);

private:
	std::optional<int32> FindSuitableAdapter(const Vector<IRHIAdapter*>& adapters);

private:
	static constexpr int32 RHICommandTypeCount = EnumCount<RHICommandType>();
	static constexpr int32 BackBufferCount = 2;
	
	RHIFeatureFlags m_features;
	RHIDebugMode m_debugMode = RHIDebugMode::Enabled;
	RHIValidationMode m_validationMode = RHIValidationMode::GPU;

	ModuleHandle m_pRHIModule;
	InstanceHandle m_pInstance;
	DeviceHandle m_pDevice;
	SwapChainHandle m_pSwapChain;
	CommandPoolHandle m_pCommandPools[RHICommandTypeCount];
	CommandQueueHandle m_pCommandQueues[RHICommandTypeCount];
	FenceHandle m_pCommandQueueFences[RHICommandTypeCount];

	CommandBufferHandle m_pSetupCommandBuffer;
	CommandBufferHandle m_pCommandBuffers[BackBufferCount];
	FenceHandle m_pFrameFences[BackBufferCount];
	SemaphoreHandle m_acquireImageSemaphores[BackBufferCount];
	SemaphoreHandle m_renderCompleteSemaphores[BackBufferCount];
};

}