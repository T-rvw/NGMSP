#pragma once

namespace ow
{

class IPlatformProcess
{
public:
	virtual ~IPlatformProcess() {}

	virtual bool Init() = 0;
};

}