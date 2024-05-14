#pragma once

#include <Core/HAL/BasicTypes.h>
#include <Core/Math/Box.hpp>

namespace ow
{

struct WindowCreateInfo
{
	WindowCreateInfo()
	{
		Title = "MainWindow";
		ParentWindow = nullptr;
		MoveRectCenter = true;
		WindowRect = Rect(1280, 720);
	}

	const char* Title;
	void* ParentWindow;
	bool MoveRectCenter;
	Rect WindowRect;
};

}