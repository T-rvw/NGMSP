#pragma once

#include <Core/Core.h>
#include <RHI/RHI.h>
#include <ShaderCompiler/IShaderCompilerModule.h>

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
	void InitRHIInstance();
	void InitLogicalDevice();
	void InitSwapChain(void* pNativeWindow, uint32 width, uint32 height);
	void InitPerFrameData();
	void InitPipeline();
	Optional<int32> FindSuitableAdapter(const Vector<IRHIAdapter*>& adapters);

	void LoadShaderCompileModule();

private:
	static constexpr int32 RHICommandTypeCount = EnumCount<RHICommandType>();
	static constexpr int32 BackBufferCount = 2;
	struct PerFrame
	{
		FenceHandle QueueSubmitFence;
		CommandPoolHandle PrimaryCommandPool;
		CommandListHandle PrimaryCommandList;
		SemaphoreHandle AcquireNextSemaphore;
		SemaphoreHandle RenderCompleteSemaphore;
	};

	RHIFeatureFlags m_features;
	RHIDebugMode m_debugMode = RHIDebugMode::Enabled;
	RHIValidationMode m_validationMode = RHIValidationMode::GPU;

	RHIModuleHandle m_rhiModule;
	InstanceHandle m_instance;
	DeviceHandle m_device;
	SwapChainHandle m_swapChain;
	Vector<PerFrame> m_perFrameData;
	PipelineLayoutHandle m_pipelineLayout;
	PipelineStateHandle m_pipelineState;

	ShaderCompilerModuleHandle m_shaderCompileModule;
	// test resources
	RefCountPtr<IRHIShader> m_vsHandle;
	RefCountPtr<IRHIShader> m_fsHandle;

};

}