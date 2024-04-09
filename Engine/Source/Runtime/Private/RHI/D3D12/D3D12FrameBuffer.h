#pragma once

#include "D3D12Header.h"

#include <RHI/Interfaces/IRHIFramebuffer.h>

namespace ow
{

class D3D12Framebuffer : public IRHIFramebuffer
{
public:
	D3D12Framebuffer() = default;
	D3D12Framebuffer(const D3D12Framebuffer&) = delete;
	D3D12Framebuffer& operator=(const D3D12Framebuffer&) = delete;
	D3D12Framebuffer(D3D12Framebuffer&&) = default;
	D3D12Framebuffer& operator=(D3D12Framebuffer&&) = default;
	virtual ~D3D12Framebuffer() = default;
};

}