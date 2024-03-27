#pragma once

#include "../IRHIInstance.h"

namespace ow
{

struct RHIInstanceCreateInfo;

class D3D12Instance : public IRHIInstance
{
public:
	D3D12Instance() = default;
	D3D12Instance(const D3D12Instance&) = delete;
	D3D12Instance& operator=(const D3D12Instance&) = delete;
	D3D12Instance(D3D12Instance&&) = default;
	D3D12Instance& operator=(D3D12Instance&&) = default;
	~D3D12Instance() = default;

	virtual void Init(const RHIInstanceCreateInfo& createInfo) override;
	virtual void Shutdown() override;

	virtual int32 GetDeviceCount() const override;
	virtual RHIDevice* GetDevice(int32 index) override;

private:
};

}