#include <Engine.h>

int main()
{
	using namespace ow;
	
	// Graphics
	RHIInstanceCreateInfo instanceCI;
	instanceCI.Backend = RHIBackend::Vulkan;
	instanceCI.Debug = RHIDebugMode::Normal;
	instanceCI.Validation = RHIValidationMode::GPU;

	auto rhiInstance = RHIInstance::Create(instanceCI);
	rhiInstance.Init();
	rhiInstance.Dump();

	auto rhiAdapters = rhiInstance.EnumerateAdapters();
	for (const auto& rhiAdapter : rhiAdapters)
	{
		rhiAdapter.Dump();
	}

	auto optAdapterIndex = FindBestRHIAdapter(rhiAdapters);
	assert(optAdapterIndex.has_value());
	int32 adapterIndex = optAdapterIndex.value();

	auto& bestAdapter = rhiAdapters[adapterIndex];
	printf("Select adapter : %s\n", bestAdapter.GetName());
	bestAdapter.Init();

	printf("\n");
	auto queueCIs = bestAdapter.QueryCommandQueueCreateInfos();
	for (const auto& queueCI : queueCIs)
	{
		queueCI.Dump();
	}

	std::vector<RHICommandQueueCreateInfo> bestQueueCIs = FindBestCommandQueues({ RHICommandQueueType::Graphics, RHICommandQueueType::Compute, RHICommandQueueType::Copy }, queueCIs);
	for (const auto& bestQueueCI : bestQueueCIs)
	{
		printf("Select %s command queue : %u\n", EnumName(bestQueueCI.Type).data(), bestQueueCI.ID);
	}

	RHIDeviceCreateInfo deviceCI;
	deviceCI.Features.Headless = false;
	deviceCI.Features.RayTracing = true;
	deviceCI.Features.MeshShaders = true;
	auto rhiDevice = bestAdapter.CreateDevice(deviceCI, bestQueueCIs);
	rhiDevice.Init();
	rhiDevice.Dump();

	std::vector<RHICommandQueue> commandQueues;
	std::vector<RHIFence> commandQueueFences;
	for (const auto& bestQueueCI : bestQueueCIs)
	{
		auto rhiCommandQueue = rhiDevice.CreateCommandQueue(bestQueueCI);
		rhiCommandQueue.Dump();
		commandQueues.emplace_back(MoveTemp(rhiCommandQueue));
		commandQueueFences.push_back(rhiDevice.CreateFence());
	}

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