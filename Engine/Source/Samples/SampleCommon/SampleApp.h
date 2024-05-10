#pragma once

#include "SampleBase.h"

#include <memory>

namespace ow
{

class SampleApp
{
public:
	SampleApp() = delete;
	explicit SampleApp(SampleBase* pSample);
	SampleApp(const SampleApp&) = delete;
	SampleApp& operator=(const SampleApp&) = delete;
	SampleApp(SampleApp&&) = default;
	SampleApp& operator=(SampleApp&&) = default;
	virtual ~SampleApp();

	void Init(int argc, const char** argv);
	bool Run();
	void UpdateTime();
	double GetDeltaTime() const { return m_currentTime - m_lastTime; }

private:
	CommandLine m_commandLine;
	PlatformWindow m_mainWindow;
	PlatformApplication m_application;
	SampleBase* m_pSample;
	double m_currentTime;
	double m_lastTime;
};

}

#define DEFINE_SAMPLE(SampleClass) \
	int main(int argc, const char** argv) \
	{ \
		auto pSample = std::make_unique<SampleClass>(); \
		auto sampleApp = SampleApp(pSample.get()); \
		sampleApp.Init(argc, argv); \
		return sampleApp.Run(); \
	}