#pragma once

namespace ow::gpu
{

class DeviceImpl
{
public:
	DeviceImpl() = default;
	DeviceImpl(const DeviceImpl&) = delete;
	DeviceImpl& operator=(const DeviceImpl&) = delete;
	DeviceImpl(DeviceImpl&&) = default;
	DeviceImpl& operator=(DeviceImpl&&) = default;
	~DeviceImpl() = default;

	void Init(const DeviceCreateInfo& createInfo);
};

}