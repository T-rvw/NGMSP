#pragma once

#include <Core/HAL/Platform.h>

namespace ow
{

struct ENGINE_API WindowCreateInfo
{
	WindowCreateInfo()
	{
		PositionX = 0;
		PositionY = 0;
		Width = 1280;
		Height = 720;
		Title = "MainWindow";
		Borderless = false;
		FullScreen = false;
		NoMaximize = false;
		NoMinimize = false;
	}

	int32 PositionX;
	int32 PositionY;
	int32 Width;
	int32 Height;
	const char* Title;
	bool Borderless;
	bool FullScreen;
	bool NoMaximize;
	bool NoMinimize;
};

}