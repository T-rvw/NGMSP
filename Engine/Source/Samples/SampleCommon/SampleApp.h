#pragma once

#include "SampleBase.h"

#include <memory>

namespace ow
{

class SampleApp
{
public:
	SampleApp() = delete;
	explicit SampleApp(SampleBase* pSample, int argc, const char** argv);
	SampleApp(const SampleApp&) = delete;
	SampleApp& operator=(const SampleApp&) = delete;
	SampleApp(SampleApp&&) = default;
	SampleApp& operator=(SampleApp&&) = default;
	virtual ~SampleApp();

	void UpdateTime();
	double GetDeltaTime() const { return m_currentTime - m_lastTime; }
	bool Run();

private:
	CommandLine m_commandLine;
	PlatformWindow m_mainWindow;
	PlatformApplication m_application;
	SampleBase* m_pSample = nullptr;

	double m_currentTime;
	double m_lastTime;
};

}

#define DEFINE_SAMPLE(SampleClass) \
	int main(int argc, const char** argv) \
	{ \
		return SampleApp(std::make_unique<SampleClass>().get(), argc, argv).Run(); \
	}