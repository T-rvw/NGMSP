#pragma once

#include <Core/HAL/Platform.h>
#include <RHI/RHITypes.h>

namespace ow
{

class IRHICommandPool;

/// <summary>
/// </summary>
class RHI_API RHICommandPool
{
public:
	RHICommandPool();
	RHICommandPool(const RHICommandPool&) = delete;
	RHICommandPool& operator=(const RHICommandPool&) = delete;
	RHICommandPool(RHICommandPool&& other) noexcept;
	RHICommandPool& operator=(RHICommandPool&& other) noexcept;
	~RHICommandPool();

	void Init();

private:
	IRHICommandPool* m_pImpl = nullptr;
};

}