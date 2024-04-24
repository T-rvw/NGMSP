#include <Engine.h>
#include <Graphics/GraphicsContext.h>

#include <Core/HAL/Interfaces/IApplication.h>

class SampleApp : public ow::IApplication
{
public:
	virtual void Init() override
	{
	}

	virtual void Shutdown() override
	{
	}

	virtual void Update() override
	{
	}
};

int main()
{
	using namespace ow;

	// Create application and main window.
	SampleApp sampleApp;
	PlatformApplication app(&sampleApp);

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
	graphicsCI.Debug = RHIDebugMode::Enabled;
	graphicsCI.Validation = RHIValidationMode::GPU;
	graphicsCI.Features |= RHIFeatures::MeshShaders;
	graphicsCI.Features |= RHIFeatures::RayTracing;
	graphicsCI.Features |= RHIFeatures::WorkGraphs;
	graphicsCI.NativeWindowHandle = mainWindow.GetHandle();
	graphicsCI.NativeInstanceHandle = app.GetProcessInstance();
	graphicsCI.BackBufferWidth = windowCI.Width;
	graphicsCI.BackBufferHeight = windowCI.Height;
	graphicsContext.Init(graphicsCI);

	// Run
	app.Run();

	return 0;
}