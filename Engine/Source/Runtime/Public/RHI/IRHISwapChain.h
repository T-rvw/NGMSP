#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHISwapChain : public RefCountObject
{
public:
	virtual ~IRHISwapChain() {}
};

}