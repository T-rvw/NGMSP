#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

class IRHIDevice;
struct RHIDeviceCreateInfo;

/// <summary>
/// RHIDevice simply wraps physical/logical device, helps to check feature levels, manage command queues.
/// </summary>
class RHI_API RHIDevice
{
public:
	RHIDevice();
	RHIDevice(const RHIDevice&) = delete;
	RHIDevice& operator=(const RHIDevice&) = delete;
	RHIDevice(RHIDevice&& other) noexcept;
	RHIDevice& operator=(RHIDevice&& other) noexcept;
	~RHIDevice();

	void Init(const RHIDeviceCreateInfo& createInfo);

private:
	IRHIDevice* m_pImpl = nullptr;
};

}