#include <Engine.h>

int main()
{
	using namespace ow;
	
	PlatformApplication app;
	app.Init();

	PlatformWindow mainWindow;
	WindowCreateInfo createInfo;
	createInfo.Title = "00_HelloWorld";
	mainWindow.Init(createInfo, app.GetProcessInstance());
	
	app.Run();
	return 0;
}