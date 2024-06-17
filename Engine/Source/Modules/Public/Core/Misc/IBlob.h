#pragma once

#include <Core/Base/RefCountPtr.h>

namespace ow
{

class IBlob : public RefCountObject
{
public:
	virtual ~IBlob() {}

	virtual const void* GetData() const = 0;
	virtual uint32 GetSize() const = 0;
};

}