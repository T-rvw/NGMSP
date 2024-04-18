#include <Engine.h>
#include <Graphics/GraphicsContext.h>

int main()
{
	using namespace ow;

	// Create application and main window.
	PlatformApplication app;
	app.Init();

	WindowCreateInfo windowCI;
	PlatformWindow mainWindow;
	windowCI.Title = "00_HelloWorld";
	windowCI.Width = 1280;
	windowCI.Height = 720;
	mainWindow.Init(windowCI);

	// Create graphics engine.
	GraphicsContext graphicsContext;
	GraphicsCreateInfo graphicsCI;
	graphicsCI.Backend = RHIBackend::Vulkan;
	graphicsCI.Features |= RHIFeatures::MeshShaders;
	graphicsCI.Features |= RHIFeatures::RayTracing;
	graphicsCI.Features |= RHIFeatures::WorkGraphs;
	graphicsCI.NativeWindowHandle = mainWindow.GetHandle();
	graphicsCI.NativeInstanceHandle = app.GetProcessInstance();
	graphicsContext.Initialize(graphicsCI);

	// Run
	app.Run();

	return 0;
}