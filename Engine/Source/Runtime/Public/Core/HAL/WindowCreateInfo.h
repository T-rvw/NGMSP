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
		PositionX = 0;
		PositionY = 0;
		Width = 1280;
		Height = 720;
		Borderless = false;
		FullScreen = false;
		NoMaximize = false;
		NoMinimize = false;
	}

	const char* Title;
	void* ParentWindow;
	int32 PositionX;
	int32 PositionY;
	int32 Width;
	int32 Height;
	bool Borderless;
	bool FullScreen;
	bool NoMaximize;
	bool NoMinimize;
};

}