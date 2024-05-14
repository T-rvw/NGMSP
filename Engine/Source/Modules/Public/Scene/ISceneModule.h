#pragma once

#include <Core/Modules/IModule.h>
#include <Scene/SceneForward.h>

namespace ow
{

class ISceneModule : public IModule, public RefCountObject
{
public:
	virtual ~ISceneModule() {}
};

}