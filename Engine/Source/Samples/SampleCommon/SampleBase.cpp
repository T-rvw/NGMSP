#include "SampleBase.h"

namespace ow
{

void SampleBase::Init(void* pNativeWindow)
{
	m_deviceContext = std::make_unique<DeviceContext>(m_createInfo.Backend, pNativeWindow, m_createInfo.Width, m_createInfo.Height);
}

void SampleBase::Shutdown()
{

}

void SampleBase::Update(double deltaTime)
{
	m_deviceContext->Update();
}

}