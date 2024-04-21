#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHIDevice : public RefCountObject
{
public:
	virtual ~IRHIDevice() {}
};

}