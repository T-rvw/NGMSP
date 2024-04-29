#pragma once

#include "D3D12Header.h"

namespace ow
{

class D3D12Utils
{
public:
	template<typename T>
	static HRESULT As(IUnknown* pSource, T** pTarget)
	{
		return pSource->QueryInterface(__uuidof(T), reinterpret_cast<void**>(pTarget));
	}
};

}