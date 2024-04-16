#include <Engine.h>

#include <Graphics/GraphicsContext.h>

int main()
{
	using namespace ow;

	GraphicsContext graphicsContext;

	RHIInstanceCreateInfo instanceCI;
	instanceCI.Backend = RHIBackend::D3D12;
	instanceCI.Debug = RHIDebugMode::Normal;
	instanceCI.Validation = RHIValidationMode::GPU;
	graphicsContext.InitializeInstance(instanceCI);

	// Query all RHI adapters.
	//uint32 adapterCount;
	//pRHIInstance->EnumerateAdapters(adapterCount, nullptr);
	//std::vector<IRHIAdapter*> rhiAdapters(adapterCount);
	//pRHIInstance->EnumerateAdapters(adapterCount, rhiAdapters.data());
	//for (const auto* pRHIAdapter : rhiAdapters)
	//{
	//	Dump(pRHIAdapter);
	//}
	//
	//// Find a proper GPU to create logical device.
	//auto optAdapterIndex = FindBestRHIAdapter(rhiAdapters);
	//assert(optAdapterIndex.has_value());
	//int32 adapterIndex = optAdapterIndex.value();
	//auto& pBestAdapter = rhiAdapters[adapterIndex];
	//printf("Select adapter : %s\n", pBestAdapter->GetInfo().Name.c_str());
	//pBestAdapter->Init();
	//
	//// Create device and command queues.
	//printf("\n");
	//uint32 commandQueueCICount;
	//pBestAdapter->QueryCommandQueueCreateInfos(commandQueueCICount, nullptr);
	//std::vector<RHICommandQueueCreateInfo*> commandQueueCIs;
	//pBestAdapter->QueryCommandQueueCreateInfos(commandQueueCICount, commandQueueCIs.data());
	//for (const auto& queueCI : commandQueueCIs)
	//{
	//	queueCI->Dump();
	//}
	//
	//std::vector<RHICommandType> expectQueueTypes { RHICommandType::Graphics, RHICommandType::Compute, RHICommandType::Copy };
	//std::vector<RHICommandQueueCreateInfo*> bestQueueCIs = FindBestCommandQueues(expectQueueTypes, commandQueueCIs);
	//for (const auto& bestQueueCI : bestQueueCIs)
	//{
	//	printf("Select %s command queue : %u\n", EnumName(bestQueueCI->Type).data(), bestQueueCI->ID);
	//}
	
	//RHIDeviceCreateInfo deviceCI;
	//deviceCI.Features.Headless = false;
	//deviceCI.Features.RayTracing = true;
	//deviceCI.Features.MeshShaders = true;
	//auto rhiDevice = pBestAdapter->CreateDevice(deviceCI, static_cast<uint32>(bestQueueCIs.size()), bestQueueCIs.data());
	//Dump(rhiDevice);

	//
	//std::vector<RHICommandQueue> commandQueues;
	//std::vector<RHIFence> commandQueueFences;
	//for (const auto& bestQueueCI : bestQueueCIs)
	//{
	//	auto rhiCommandQueue = rhiDevice.CreateCommandQueue(bestQueueCI);
	//	rhiCommandQueue.Dump();
	//	commandQueues.emplace_back(MoveTemp(rhiCommandQueue));
	//	commandQueueFences.push_back(rhiDevice.CreateFence());
	//}
	//
	//// Create application and main window.
	//PlatformApplication app;
	//app.Init();
	//
	//WindowCreateInfo windowCI;
	//PlatformWindow mainWindow;
	//windowCI.Title = "00_HelloWorld";
	//windowCI.Width = 1280;
	//windowCI.Height = 720;
	//mainWindow.Init(windowCI, app.GetProcessInstance());
	//
	//// Create SwapChain to bind to native window.
	//RHISwapChainCreateInfo swapChainCI;
	//swapChainCI.Instance = &rhiInstance;
	//swapChainCI.NativeWindowHandle = mainWindow.GetHandle();
	//swapChainCI.NativeInstanceHandle = app.GetProcessInstance();
	//swapChainCI.BackBufferWidth = windowCI.Width;
	//swapChainCI.BackBufferHeight = windowCI.Height;
	//swapChainCI.BackBufferCount = 2;
	//swapChainCI.Format = RHIFormat::R8G8B8A8Unorm;
	//swapChainCI.PresentMode = RHIPresentMode::VSync;
	//auto rhiSwapChain = rhiDevice.CreateSwapChain(swapChainCI);
	//
	//// Run
	//app.Run();

	return 0;
}