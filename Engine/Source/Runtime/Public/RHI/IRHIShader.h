#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHIShader : public RefCountObject
{
public:
	virtual ~IRHIShader() {}
};

}