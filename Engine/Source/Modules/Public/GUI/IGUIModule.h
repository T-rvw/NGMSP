#pragma once

#include <Core/Modules/IModule.h>
#include <GUI/GUIForward.h>

namespace ow
{

class IGUIModule : public IModule, public RefCountObject
{
public:
	virtual ~IGUIModule() {}
};

}