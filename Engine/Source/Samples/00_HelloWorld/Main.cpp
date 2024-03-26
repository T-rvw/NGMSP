#include <Engine.h>

int32 WINAPI WinMain(_In_ HINSTANCE hInInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ char* pCmdLine, _In_ int32 nCmdShow)
{
	UNUSED(hPrevInstance);
	UNUSED(pCmdLine);
	UNUSED(nCmdShow);

	using namespace ow;
	
	PlatformApplication app;
	app.Init((void*)hInInstance);

	PlatformWindow mainWindow;
	WindowCreateInfo createInfo;
	createInfo.Title = "00_HelloWorld";
	mainWindow.Init(createInfo, app.GetProcessInstance());
	
	app.Run();
	return 0;
}