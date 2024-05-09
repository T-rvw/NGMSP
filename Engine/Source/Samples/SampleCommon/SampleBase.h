#pragma once

#include <Graphics/DeviceContext.h>

#include <memory>

namespace ow
{

class SampleApp;

class SampleBase
{
public:
	SampleBase() = default;
	SampleBase(const SampleBase&) = delete;
	SampleBase& operator=(const SampleBase&) = delete;
	SampleBase(SampleBase&&) = default;
	SampleBase& operator=(SampleBase&&) = default;
	virtual ~SampleBase() {}
	
	void Init(RHIBackend backend, void* pNativeWindow, uint32 width, uint32 height);
	void Update(double deltaTime);
	void Shutdown();

protected:
	std::unique_ptr<DeviceContext> m_deviceContext;
	SampleApp* m_pSampleApp = nullptr;
};

}