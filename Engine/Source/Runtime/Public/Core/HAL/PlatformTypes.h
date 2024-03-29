#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

struct ENGINE_API WindowCreateInfo
{
	WindowCreateInfo()
	{
		Title = "MainWindow";
		ParentWindow = nullptr;
		Width = 1280;
		Height = 720;
	}

	const char* Title;
	void* ParentWindow;
	int32 Width;
	int32 Height;
};

}