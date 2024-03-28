#include <Engine.h>

#include <iostream>

int main()
{
	using namespace ow;
	
	{
		RHIInstanceCreateInfo rhiCI;
		rhiCI.Backend = RHIBackend::D3D12;

		RHIInstance rhiInstance;
		rhiInstance.Init(rhiCI);

		auto rhiAdapters = rhiInstance.EnumAdapters();
		for (const auto& rhiAdapter : rhiAdapters)
		{
			rhiAdapter->Dump();
		}
	}

	{
		PlatformApplication app;
		app.Init();

		WindowCreateInfo windowCI;
		PlatformWindow mainWindow;
		windowCI.Title = "00_HelloWorld";
		mainWindow.Init(windowCI, app.GetProcessInstance());

		app.Run();
	}

	return 0;
}