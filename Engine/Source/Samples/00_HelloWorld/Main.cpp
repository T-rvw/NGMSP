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
	graphicsContext.Initialize(instanceCI);

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