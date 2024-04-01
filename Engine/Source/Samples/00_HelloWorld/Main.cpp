#include <Engine.h>

int main()
{
	using namespace ow;
	
	{
		RHIInstanceCreateInfo instanceCI;
		instanceCI.Backend = RHIBackend::Vulkan;

		RHIInstance rhiInstance;
		rhiInstance.Init(instanceCI);
		rhiInstance.Dump();

		RHIAdapter* pSelectAdapter = nullptr;
		auto rhiAdapters = rhiInstance.EnumAdapters();
		for (const auto& rhiAdapter : rhiAdapters)
		{
			rhiAdapter->Dump();
		}

		RHIAdapter* pBestAdapter = FindBestRHIAdapter(rhiAdapters);
		assert(pBestAdapter);
		printf("\nSelect adapter : %s\n", pBestAdapter->GetName());

		RHIDeviceCreateInfo deviceCI;
		auto rhiDevice = pBestAdapter->CreateDevice(deviceCI);
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