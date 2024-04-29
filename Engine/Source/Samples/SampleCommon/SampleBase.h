#pragma once

#include <Graphics/DeviceContext.h>

#include <memory>
#include <string>

namespace ow
{

struct SampleCreateInfo
{
	RHIBackend Backend = RHIBackend::Vulkan;
	std::string Title = "SampleFramework";
	uint32 Width = 1280;
	uint32 Height = 720;
};

class SampleApp;

class SampleBase
{
public:
	SampleBase() = delete;
	explicit SampleBase(SampleCreateInfo createInfo) : m_createInfo(std::move(createInfo)) {}
	SampleBase(const SampleBase&) = delete;
	SampleBase& operator=(const SampleBase&) = delete;
	SampleBase(SampleBase&&) = default;
	SampleBase& operator=(SampleBase&&) = default;
	virtual ~SampleBase() {}
	
	virtual void Init(void* pNativeWindow);
	virtual void Shutdown() = 0;
	virtual void Update(double deltaTime) = 0;

	const SampleCreateInfo& GetCreateInfo() const { return m_createInfo; }

protected:
	std::unique_ptr<DeviceContext> m_deviceContext;
	SampleApp* m_pSampleApp = nullptr;
	SampleCreateInfo m_createInfo;
};

}