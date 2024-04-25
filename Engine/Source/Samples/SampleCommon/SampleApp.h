#pragma once

#include "SampleBase.h"

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

	void UpdateTime();
	double GetDeltaTime() const { return m_currentTime - m_lastTime; }
	bool Run();

private:
	PlatformWindow m_mainWindow;
	PlatformApplication m_application;
	SampleBase* m_pSample = nullptr;

	double m_currentTime;
	double m_lastTime;
};

}