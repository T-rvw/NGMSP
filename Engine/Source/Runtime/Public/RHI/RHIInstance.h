#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

class IRHIInstance;
struct RHIInstanceCreateInfo;

enum class RHIBackend;
class RHIDevice;

/// <summary>
/// RHIInstance helps to load dynamic apis, check conditions, init gpu device.
/// </summary>
class RHI_API RHIInstance
{
public:
	RHIInstance();
	RHIInstance(const RHIInstance&) = delete;
	RHIInstance& operator=(const RHIInstance&) = delete;
	RHIInstance(RHIInstance&& other) noexcept;
	RHIInstance& operator=(RHIInstance&& other) noexcept;
	~RHIInstance();

	void Init(const RHIInstanceCreateInfo& createInfo);
	void Shutdown();

	int32 GetDeviceCount() const;
	RHIDevice* GetDevice(int32 index);
	const RHIDevice* GetDevice(int32 index) const;

private:
	IRHIInstance* m_pImpl = nullptr;
};

}