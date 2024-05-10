#pragma once

#include <Core/Core.h>
#include <RHI/RHI.h>

namespace ow
{

class DeviceContext
{
public:
	DeviceContext() = delete;
	GFX_API explicit DeviceContext(RHIBackend backend, void* pNativeWindow, const Rect& windowRect);
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
	void CreateSwapChain(void* pNativeWindow, uint32 width, uint32 height);

private:
	Optional<int32> FindSuitableAdapter(const Vector<IRHIAdapter*>& adapters);

private:
	static constexpr int32 RHICommandTypeCount = EnumCount<RHICommandType>();
	static constexpr int32 BackBufferCount = 2;
	
	RHIFeatureFlags m_features;
	RHIDebugMode m_debugMode = RHIDebugMode::Enabled;
	RHIValidationMode m_validationMode = RHIValidationMode::GPU;

	ModuleHandle m_rhiModule;
	InstanceHandle m_instance;
	DeviceHandle m_device;
	SwapChainHandle m_swapChain;
	CommandPoolHandle m_commandPools[RHICommandTypeCount];
	CommandQueueHandle m_commandQueues[RHICommandTypeCount];
	FenceHandle m_commandQueueFences[RHICommandTypeCount];

	CommandListHandle m_setupCommandBuffer;
	CommandListHandle m_commandBuffers[BackBufferCount];
	FenceHandle m_frameFences[BackBufferCount];
	SemaphoreHandle m_acquireImageSemaphores[BackBufferCount];
	SemaphoreHandle m_renderCompleteSemaphores[BackBufferCount];
};

}