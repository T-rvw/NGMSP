#pragma once

#include "D3D12Header.h"

#include <RHI/IRHITexture.h>

namespace ow
{

class D3D12Device;

class D3D12Texture : public IRHITexture
{
public:
	D3D12Texture() = delete;
	explicit D3D12Texture(const D3D12Device* pDevice, const RHITextureCreateInfo& createInfo);
	D3D12Texture(const D3D12Texture&) = delete;
	D3D12Texture& operator=(const D3D12Texture&) = delete;
	D3D12Texture(D3D12Texture&&) = default;
	D3D12Texture& operator=(D3D12Texture&&) = default;
	virtual ~D3D12Texture() = default;
};

}