#include <Engine.h>

int main()
{
	using namespace ow;
	
	// Graphics
	RHIInstanceCreateInfo instanceCI;
	instanceCI.Backend = RHIBackend::Vulkan;
	instanceCI.Debug = DebugMode::Normal;
	instanceCI.Validation = ValidationMode::GPU;

	auto rhiInstance = RHIInstance::Create(instanceCI);
	rhiInstance.Init();
	rhiInstance.Dump();

	auto rhiAdapters = rhiInstance.EnumAdapters();
	for (const auto& rhiAdapter : rhiAdapters)
	{
		rhiAdapter.Dump();
	}

	RHIAdapter* pBestAdapter = FindBestRHIAdapter(rhiAdapters);
	assert(pBestAdapter);
	printf("\nSelect adapter : %s\n", pBestAdapter->GetName());
	pBestAdapter->Init();

	RHIDeviceCreateInfo deviceCI;
	deviceCI.Features.Headless = false;
	deviceCI.Features.RayTracing = true;
	deviceCI.Features.MeshShaders = true;
	auto rhiDevice = pBestAdapter->CreateDevice(deviceCI);
	rhiDevice.Init();
	rhiDevice.Dump();

	// Application
	PlatformApplication app;
	app.Init();

	WindowCreateInfo windowCI;
	PlatformWindow mainWindow;
	windowCI.Title = "00_HelloWorld";
	mainWindow.Init(windowCI, app.GetProcessInstance());

	app.Run();

	return 0;
}