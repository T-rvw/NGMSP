#include "D3D12Device.h"

#include "D3D12Adapter.h"
#include "D3D12Barrier.h"
#include "D3D12Buffer.h"
#include "D3D12CommandPool.h"
#include "D3D12CommandQueue.h"
#include "D3D12Fence.h"
#include "D3D12Semaphore.h"
#include "D3D12SwapChain.h"
#include "D3D12Texture.h"

#include <RHI/RHITypes.h>

namespace ow
{

D3D12Device::D3D12Device(const D3D12Adapter* pAdapter, const RHIDeviceCreateInfo& createInfo) :
	m_pAdapter(pAdapter)
{
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
	D3D12_FEATURE_DATA_FEATURE_LEVELS featureDatas{};
	featureDatas.pFeatureLevelsRequested = FeatureLevelsRange;
	featureDatas.NumFeatureLevels = FeatureLevelsCount;
	D3D12_VERIFY(pDevice->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &featureDatas, sizeof(D3D12_FEATURE_DATA_FEATURE_LEVELS)));
	D3D12_VERIFY(D3D12CreateDevice(m_pAdapter->GetHandle(), featureDatas.MaxSupportedFeatureLevel, IID_PPV_ARGS(pDevice.ReleaseAndGetAddressOf())));
	assert(pDevice);

	if (createInfo.Validation != RHIValidationMode::Disabled)
	{
		RefCountPtr<ID3D12InfoQueue1> pInfoQueue;
		if (D3D12_SUCCEED(pDevice->QueryInterface(IID_PPV_ARGS(pInfoQueue.GetAddressOf()))))
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
		D3D12_VERIFY(pDevice->SetStablePowerState(TRUE));
	}

	m_device = MoveTemp(pDevice);
}

RefCountPtr<IDXGIFactory6> D3D12Device::GetFactory() const
{
	return m_pAdapter->GetFactory();
}

RefCountPtr<IRHISwapChain> D3D12Device::CreateSwapChain(const RHISwapChainCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12SwapChain>(this, createInfo);
}

RefCountPtr<IRHICommandPool> D3D12Device::CreateCommandPool(const RHICommandPoolCreateInfo& createInfo)
{
	return nullptr;
}

RefCountPtr<IRHICommandQueue> D3D12Device::CreateCommandQueue(const RHICommandQueueCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12CommandQueue>(this, createInfo);;
}

RefCountPtr<IRHIBarrier> D3D12Device::CreateBarrier(const RHIBarrierCreateInfo& createInfo)
{
	return nullptr;
}

RefCountPtr<IRHIFence> D3D12Device::CreateFence(const RHIFenceCreateInfo& createInfo)
{
	return MakeRefCountPtr<D3D12Fence>(this, createInfo);
}

RefCountPtr<IRHISemaphore> D3D12Device::CreateSemaphore(const RHISemaphoreCreateInfo& createInfo)
{
	return nullptr;
}

RefCountPtr<IRHIBuffer> D3D12Device::CreateBuffer(const RHIBufferCreateInfo& createInfo)
{
	return nullptr;
}

RefCountPtr<IRHITexture> D3D12Device::CreateTexture(const RHITextureCreateInfo& createInfo)
{
	return nullptr;
}

const D3D12CommandQueue* D3D12Device::GetCommandQueue(RHICommandType commandType) const
{
	int32 typeIndex = static_cast<int32>(commandType);
	return m_pCommandQueues[typeIndex];
}

void D3D12Device::SetCommandQueue(const D3D12CommandQueue* pCommandQueue)
{
	int32 typeIndex = static_cast<int32>(pCommandQueue->GetType());
	m_pCommandQueues[typeIndex] = pCommandQueue;
}

void D3D12Device::ReportLiveObjects()
{
	RefCountPtr<ID3D12DebugDevice> pDebugDevice;
	D3D12_VERIFY(m_device->QueryInterface(__uuidof(ID3D12DebugDevice), reinterpret_cast<void**>(pDebugDevice.ReleaseAndGetAddressOf())));
	pDebugDevice->ReportLiveDeviceObjects((D3D12_RLDO_FLAGS)(D3D12_RLDO_IGNORE_INTERNAL | D3D12_RLDO_DETAIL));
}

}