#include "SampleBase.h"

namespace ow
{

void SampleBase::Init(RHIBackend backend, void* pNativeWindow, uint32 width, uint32 height)
{
	m_deviceContext = std::make_unique<DeviceContext>(backend, pNativeWindow, width, height);
}

void SampleBase::Shutdown()
{

}

void SampleBase::Update(double deltaTime)
{
	m_deviceContext->Update();
}

}