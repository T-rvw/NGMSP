#pragma once

namespace ow::dx12
{

class DeviceImpl;

/// <summary>
/// GPU device simply wraps physical and logical device, helps to check feature levels, manage command queues.
/// </summary>
class ENGINE_API Device
{
public:
	Device();
	Device(const Device&) = delete;
	Device& operator=(const Device&) = delete;
	Device(Device&& other) noexcept;
	Device& operator=(Device&& other) noexcept;
	~Device();

private:
	DeviceImpl* m_pImpl = nullptr;
};

}