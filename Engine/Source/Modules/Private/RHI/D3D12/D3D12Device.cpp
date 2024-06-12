#include "D3D12Device.h"

#include "D3D12Adapter.h"
#include "D3D12Barrier.h"
#include "D3D12Buffer.h"
#include "D3D12CommandPool.h"
#include "D3D12CommandQueue.h"
#include "D3D12Fence.h"
#include "D3D12PipelineLayout.h"
#include "D3D12PipelineState.h"
#include "D3D12Semaphore.h"
#include "D3D12SwapChain.h"
#include "D3D12Texture.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12Device::D3D12Device(const D3D12Adapter* pAdapter, const RHIDeviceCreateInfo& createInfo) :
	m_pAdapter(pAdapter)
{
	// Creata a temporary 11.0 device to check feature support.
	constexpr D3D_FEATURE_LEVEL FeatureLevelsRange[] =
	{
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};
	constexpr uint32 FeatureLevelsCount = sizeof(FeatureLevelsRange) / sizeof(D3D_FEATURE_LEVEL);
	constexpr D3D_FEATURE_LEVEL MinFeatureLevel = FeatureLevelsRange[FeatureLevelsCount - 1];
	RefCountPtr<ID3D12Device5> pDevice;
	D3D12_VERIFY(D3D12CreateDevice(m_pAdapter->GetHandle(), MinFeatureLevel, IID_PPV_ARGS(&pDevice)));
	
	// D3D 11.1
	D3D12_FEATURE_DATA_FEATURE_LEVELS featureLevelsData = {};
	featureLevelsData.pFeatureLevelsRequested = FeatureLevelsRange;
	featureLevelsData.NumFeatureLevels = FeatureLevelsCount;
	D3D12_VERIFY(pDevice->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &featureLevelsData, sizeof(featureLevelsData)));
	Assert(featureLevelsData.MaxSupportedFeatureLevel >= D3D_FEATURE_LEVEL_11_1);

	// SM 6.6
	D3D12_FEATURE_DATA_SHADER_MODEL shaderModelData = {};
	shaderModelData.HighestShaderModel = D3D_SHADER_MODEL_6_6;
	D3D12_VERIFY(pDevice->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModelData, sizeof(shaderModelData)));
	Assert(shaderModelData.HighestShaderModel <= D3D_SHADER_MODEL_6_6);

	// Check resource binding's hardware support.
	// https://learn.microsoft.com/en-us/windows/win32/direct3d12/hardware-support
	D3D12_FEATURE_DATA_D3D12_OPTIONS featureOptionsData = {};
	D3D12_VERIFY(pDevice->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &featureOptionsData, sizeof(featureOptionsData)));
	Assert(featureOptionsData.ResourceBindingTier >= D3D12_RESOURCE_BINDING_TIER_3);

	if (createInfo.Features.IsEnabled(RHIFeatures::RayTracing))
	{
		// DXR 1.1
		D3D12_FEATURE_DATA_D3D12_OPTIONS5 featureOptions5Data = {};
		D3D12_VERIFY(pDevice->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &featureOptions5Data, sizeof(featureOptions5Data)));
		Assert(featureOptions5Data.RaytracingTier >= D3D12_RAYTRACING_TIER_1_1);
	}

	pDevice.Reset();
	D3D12_VERIFY(D3D12CreateDevice(m_pAdapter->GetHandle(), featureLevelsData.MaxSupportedFeatureLevel, IID_PPV_ARGS(m_device.ReleaseAndGetAddressOf())));
	Assert(m_device);

	if (createInfo.Validation != RHIValidationMode::Disabled)
	{
		RefCountPtr<ID3D12InfoQueue1> pInfoQueue;
		if (D3D12_SUCCEED(D3D12Utils::As<ID3D12InfoQueue1>(m_device, &pInfoQueue)))
		{
			D3D12_VERIFY(pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE));
			D3D12_VERIFY(pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE));
			D3D12_VERIFY(pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE));

			auto MessageCallback = [](D3D12_MESSAGE_CATEGORY Category, D3D12_MESSAGE_SEVERITY Severity,
				D3D12_MESSAGE_ID ID, LPCSTR pDescription, void* pContext)
				{
					printf("D3D12 Validation Layer: %s\n", pDescription);
				};

			DWORD callbackCookie = 0;
			D3D12_VERIFY(pInfoQueue->RegisterMessageCallback(MessageCallback, D3D12_MESSAGE_CALLBACK_FLAG_NONE, nullptr, &callbackCookie));
		}
	}

	if (createInfo.Features.IsEnabled(RHIFeatures::StablePower))
	{
		D3D12_VERIFY(D3D12EnableExperimentalFeatures(0, nullptr, nullptr, nullptr));
		D3D12_VERIFY(m_device->SetStablePowerState(TRUE));
	}

	constexpr uint32 commandTypeCount = EnumCount<RHICommandType>();
	for (uint32 typeIndex = 0; typeIndex < commandTypeCount; ++typeIndex)
	{
		auto commandType = static_cast<RHICommandType>(typeIndex);
		if (!createInfo.CommandQueueTypes.IsEnabled(commandType))
		{
			continue;
		}

		RHICommandQueueCreateInfo queueCI;
		queueCI.Type = commandType;
		m_commandQueues[typeIndex] = MakeRefCountPtr<D3D12CommandQueue>(this, queueCI);
	}
}

RefCountPtr<IDXGIFactory6> D3D12Device::GetFactory() const
{
	return m_pAdapter->GetFactory();
}

SwapChainHandle D3D12Device::CreateSwapChain(const RHISwapChainCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12SwapChain>(this, createInfo);
}

CommandPoolHandle D3D12Device::CreateCommandPool(const RHICommandPoolCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12CommandPool>(this, createInfo);
}

BarrierHandle D3D12Device::CreateBarrier(const RHIBarrierCreateInfo& createInfo)
{
	return nullptr;
}

BufferHandle D3D12Device::CreateBuffer(const RHIBufferCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12Buffer>(this, createInfo);
}

FenceHandle D3D12Device::CreateFence(const RHIFenceCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12Fence>(this, createInfo);
}

PipelineLayoutHandle D3D12Device::CreatePipelineLayout(const RHIPipelineLayoutCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12PipelineLayout>(this, createInfo);
}

SemaphoreHandle D3D12Device::CreateSemaphore(const RHISemaphoreCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12Semaphore>(createInfo);
}

TextureHandle D3D12Device::CreateTexture(const RHITextureCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12Texture>(this, createInfo);
}

CommandQueueHandle D3D12Device::GetCommandQueue(RHICommandType commandType) const
{
	return m_commandQueues[static_cast<uint32>(commandType)];
}

void D3D12Device::ReportLiveObjects()
{
	RefCountPtr<ID3D12DebugDevice> pDebugDevice;
	D3D12_VERIFY(D3D12Utils::As<ID3D12DebugDevice>(m_device, &pDebugDevice));
	pDebugDevice->ReportLiveDeviceObjects((D3D12_RLDO_FLAGS)(D3D12_RLDO_IGNORE_INTERNAL | D3D12_RLDO_DETAIL));
}

}