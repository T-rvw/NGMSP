#include "SampleApp.h"

#include <Core/Core.h>
#include <RHI/RHI.h>

using namespace ow;

class HelloWorldSample : public SampleBase
{
public:
	using SampleBase::SampleBase;

	virtual ~HelloWorldSample()
	{
	}

	virtual void Init(void* pNativeWindow) override
	{
		SampleBase::Init(pNativeWindow);
	}

	virtual void Shutdown() override
	{
	}
	
	virtual void Update(double deltaTime) override
	{
		SampleBase::Update(deltaTime);
	}

	void Setup()
	{
	}

	void Render()
	{
	}

private:
	// Resources

};

int main()
{
	SampleCreateInfo sampleCI;
	sampleCI.Backend = RHIBackend::Vulkan;
	sampleCI.Title = "00_HelloWorld";
	sampleCI.Width = 1280;
	sampleCI.Height = 720;
	auto sample = std::make_unique<HelloWorldSample>(sampleCI);
	return SampleApp(sample.get()).Run();
}