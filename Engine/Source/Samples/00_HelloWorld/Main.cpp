#include <Engine.h>

using namespace ow;

IRHIInstance* CreateRHIInstance(const RHIInstanceCreateInfo& createInfo)
{
	//ModuleManager::Module* rhiModule = nullptr;
	//switch (createInfo.Backend)
	//{
	//case RHIBackend::D3D12:
	//{
	//	rhiModule = ModuleManager::Get().LoadModule("[RHI][D3D12]", "RHID3D12");
	//	break;
	//}
	//case RHIBackend::Vulkan:
	//{
	//	rhiModule = ModuleManager::Get().LoadModule("[RHI][Vulkan]", "RHIVulkan");
	//	break;
	//}
	//default:
	//{
	//	assert("Unknown RHI backend.");
	//	break;
	//}
	//}
	//
	//assert(rhiModule);
	//auto* pModule = static_cast<IRHIModule*>(rhiModule->InitFunc());
	//return pModule->CreateRHIInstance();

	return nullptr;
}

int main()
{
	// Init RHI instance.
	RHIInstanceCreateInfo instanceCI;
	instanceCI.Backend = RHIBackend::Vulkan;
	instanceCI.Debug = RHIDebugMode::Normal;
	instanceCI.Validation = RHIValidationMode::GPU;
	IRHIInstance* pRHIInstance = CreateRHIInstance(instanceCI);
	
	//PlatformModule rhiModule;
	//rhiModule.Lo("RHIVulkan");
	//auto intializeModuleFunc = (InitializeModuleFunc)rhiModule.GetFunctionAddress("InitializeModule");
	//auto* pRHIModule = static_cast<IRHIModule*>(intializeModuleFunc());
	//pRHIModule->Initialize();
	//rhiModule.Free();

	//auto rhiInstance = RHIInstance::Create(instanceCI);
	//rhiInstance.Dump();
	//
	//// Find a proper GPU to create logical device.
	//auto rhiAdapters = rhiInstance.EnumerateAdapters();
	//for (const auto& rhiAdapter : rhiAdapters)
	//{
	//	rhiAdapter.Dump();
	//}
	//
	//auto optAdapterIndex = FindBestRHIAdapter(rhiAdapters);
	//assert(optAdapterIndex.has_value());
	//int32 adapterIndex = optAdapterIndex.value();
	//
	//auto& bestAdapter = rhiAdapters[adapterIndex];
	//printf("Select adapter : %s\n", bestAdapter.GetName());
	//bestAdapter.Init();
	//
	//// Create device and command queues.
	//printf("\n");
	//auto queueCIs = bestAdapter.QueryCommandQueueCreateInfos();
	//for (const auto& queueCI : queueCIs)
	//{
	//	queueCI.Dump();
	//}
	//
	//std::vector<RHICommandType> expectQueueTypes { RHICommandType::Graphics, RHICommandType::Compute, RHICommandType::Copy };
	//std::vector<RHICommandQueueCreateInfo> bestQueueCIs = FindBestCommandQueues(expectQueueTypes, queueCIs);
	//for (const auto& bestQueueCI : bestQueueCIs)
	//{
	//	printf("Select %s command queue : %u\n", EnumName(bestQueueCI.Type).data(), bestQueueCI.ID);
	//}
	//
	//RHIDeviceCreateInfo deviceCI;
	//deviceCI.Features.Headless = false;
	//deviceCI.Features.RayTracing = true;
	//deviceCI.Features.MeshShaders = true;
	//auto rhiDevice = bestAdapter.CreateDevice(deviceCI, bestQueueCIs);
	//rhiDevice.Dump();
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