#include "SampleBase.h"

namespace ow
{

void SampleBase::Init(RHIBackend backend, void* pNativeWindow, const Rect& windowRect)
{
	m_deviceContext = std::make_unique<DeviceContext>(backend, pNativeWindow, windowRect);
}

void SampleBase::Shutdown()
{

}

void SampleBase::Update(double deltaTime)
{
	m_deviceContext->Update();
}

}