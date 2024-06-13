#include <Graphics/DeviceContext.h>

#include <unordered_set>

namespace ow
{

DeviceContext::DeviceContext(RHIBackend backend, void* pNativeWindow, const Rect& windowRect)
{
	// RHI
	LoadRHIModule(backend);
	InitRHIInstance();
	InitLogicalDevice();
	InitSwapChain(pNativeWindow, windowRect.GetWidth(), windowRect.GetHeight());

	// Shader Compiler
	LoadShaderCompileModule();
}

DeviceContext::~DeviceContext()
{
}

void DeviceContext::Update()
{
}

void DeviceContext::LoadRHIModule(RHIBackend backend)
{
	ModuleData* pRHILibrary = nullptr;
	switch (backend)
	{
	case RHIBackend::D3D12:
	{
		pRHILibrary = ModuleManager::Get().AddModule("[RHI][D3D12]", "RHID3D12");
		break;
	}
	case RHIBackend::Vulkan:
	{
		pRHILibrary = ModuleManager::Get().AddModule("[RHI][Vulkan]", "RHIVulkan");
		break;
	}
	default:
	{
		Assert("Unknown RHI backend.");
		return;
	}
	}

	Assert(pRHILibrary);
	m_rhiModule = static_cast<IRHIModule*>(pRHILibrary->InitFunc());
}

void DeviceContext::InitRHIInstance()
{
	RHIInstanceCreateInfo instanceCI;
	instanceCI.Features = m_features;
	instanceCI.Debug = m_debugMode;
	instanceCI.Validation = m_validationMode;
	m_instance = m_rhiModule->CreateRHIInstance(instanceCI);
	Assert(m_instance);
}

void DeviceContext::InitLogicalDevice()
{
	// Query all RHI adapters.
	uint32 adapterCount;
	m_instance->EnumerateAdapters(adapterCount, nullptr);
	Vector<IRHIAdapter*> rhiAdapters(adapterCount);
	m_instance->EnumerateAdapters(adapterCount, rhiAdapters.data());

	for (const auto* rhiAdapter : rhiAdapters)
	{
		rhiAdapter->GetInfo().Dump();
	}

	// Find a proper GPU to create logical device.
	auto optAdapterIndex = FindSuitableAdapter(rhiAdapters);
	Assert(optAdapterIndex.has_value());
	int32 adapterIndex = optAdapterIndex.value();
	auto& pBestAdapter = rhiAdapters[adapterIndex];
	printf("Select adapter : %s\n", pBestAdapter->GetInfo().Name.c_str());

	// Query display output info.
	uint32 adapterOutputCount;
	pBestAdapter->EnumerateOutputs(adapterOutputCount, nullptr);
	Vector<RHIOutputInfo*> outputInfos(adapterOutputCount);
	pBestAdapter->EnumerateOutputs(adapterOutputCount, outputInfos.data());
	for (const auto* outputInfo : outputInfos)
	{
		outputInfo->Dump();
	}
	
	// Create logical device and required command queues.
	RHIDeviceCreateInfo deviceCI;
	deviceCI.Features = m_features;
	deviceCI.CommandQueueTypes.Enable(RHICommandType::Graphics);
	deviceCI.CommandQueueTypes.Enable(RHICommandType::Compute);
	deviceCI.CommandQueueTypes.Enable(RHICommandType::Copy);
	deviceCI.Debug = m_debugMode;
	deviceCI.Validation = m_validationMode;
	m_device = pBestAdapter->CreateDevice(deviceCI);
}

void DeviceContext::InitSwapChain(void* pNativeWindow, uint32 width, uint32 height)
{
	RHISwapChainCreateInfo swapChainCI;
	swapChainCI.NativeWindowHandle = pNativeWindow;
	swapChainCI.BackBufferWidth = width;
	swapChainCI.BackBufferHeight = height;
	swapChainCI.BackBufferCount = BackBufferCount;
	swapChainCI.Format = RHIFormat::RGBA8_UNORM;
	swapChainCI.ColorSpace = RHIColorSpace::SRGB_NONLINEAR;
	swapChainCI.PresentMode = RHIPresentMode::VSync;
	m_swapChain = m_device->CreateSwapChain(swapChainCI);

	InitPerFrameData();
}

void DeviceContext::InitPerFrameData()
{
	uint32 backBufferCount = m_swapChain->GetBackBufferCount();
	m_perFrameData.clear();
	m_perFrameData.resize(backBufferCount);

	for (uint32 frameIndex = 0; frameIndex < backBufferCount; ++frameIndex)
	{
		auto& perFrameData = m_perFrameData[frameIndex];

		RHICommandPoolCreateInfo commandPoolCI;
		commandPoolCI.Type = RHICommandType::Graphics;
		perFrameData.PrimaryCommandPool = m_device->CreateCommandPool(commandPoolCI);

		RHICommandListCreateInfo commandBufferCI;
		perFrameData.PrimaryCommandList = perFrameData.PrimaryCommandPool->CreateCommandList(commandBufferCI);

		RHIFenceCreateInfo fenceCI;
		perFrameData.QueueSubmitFence = m_device->CreateFence(fenceCI);

		RHISemaphoreCreateInfo semaphoreCI;
		perFrameData.AcquireNextSemaphore = m_device->CreateSemaphore(semaphoreCI);
		perFrameData.RenderCompleteSemaphore = m_device->CreateSemaphore(semaphoreCI);
	}
}

void DeviceContext::InitPipeline()
{
	RHIPipelineLayoutCreateInfo pipelineLayoutCI;
	m_pipelineLayout = m_device->CreatePipelineLayout(pipelineLayoutCI);

	RHIGraphicsPipelineStateCreateInfo pipelineStateCI;
	pipelineStateCI.SwapChain = m_swapChain;
	m_pipelineState = m_pipelineLayout->CreateGraphicsPipelineState(pipelineStateCI);
}

Optional<int32> DeviceContext::FindSuitableAdapter(const Vector<IRHIAdapter*>& adapters)
{
	Optional<int32> bestAdapterIndex;
	uint64 bestScore = 0;
	for (int32 adapterIndex = 0, adapterCount = static_cast<int32>(adapters.size()); adapterIndex < adapterCount; ++adapterIndex)
	{
		const IRHIAdapter* pAdapter = adapters[adapterIndex];
		const auto& adapterInfo = pAdapter->GetInfo();

		uint64 score = 0;
		if (GPUAdapterType::Discrete == adapterInfo.Type)
		{
			score += 1ULL << 63;
		}
		else if (GPUAdapterType::Integrated == adapterInfo.Type)
		{
			score += 1ULL << 62;
		}

		score += adapterInfo.VideoMemorySize >> 20;

		if (score > bestScore)
		{
			bestAdapterIndex = adapterIndex;
			bestScore = score;
		}
	}

	return bestAdapterIndex;
}

void DeviceContext::LoadShaderCompileModule()
{
	ModuleData* pShaderCompilerLibrary = ModuleManager::Get().AddModule("[ShaderCompiler]", "ShaderCompiler");
	Assert(pShaderCompilerLibrary);
	m_shaderCompileModule = static_cast<IShaderCompilerModule*>(pShaderCompilerLibrary->InitFunc());

	ShaderCompileInfo compileInfo;
	compileInfo.Source = RHIShaderLanguage::HLSL;
	compileInfo.Target = RHIShaderByteCode::SPIRV;
	compileInfo.Type = RHIShaderType::Fragment;
	compileInfo.EntryPointName = "main";
	compileInfo.Features.Enable(ShaderCompileFeatures::DebugInfo);
	compileInfo.FileName = "PixelShader.hlsl";
	compileInfo.IncludeDirectories.push_back("Z:\\NGMSP\\Engine\\Assets\\Shaders");
	auto compileResult = m_shaderCompileModule->CompileShader("Z:\\NGMSP\\Engine\\Assets\\Shaders\\PixelShader.hlsl", compileInfo);
}

}