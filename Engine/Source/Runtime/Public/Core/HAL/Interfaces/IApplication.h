#pragma once

namespace ow
{

class IApplication
{
public:
	virtual ~IApplication() {}
	
	virtual void Init() = 0;
	virtual void Shutdown() = 0;
	virtual void Update() = 0;
};

}