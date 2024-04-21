#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IRHITexture : public RefCountObject
{
public:
	virtual ~IRHITexture() {}
};

class IRHISampler : public RefCountObject
{
public:
	virtual ~IRHISampler() {}
};


}