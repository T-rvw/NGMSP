#include "SampleApp.h"

namespace ow
{

SampleApp::SampleApp(SampleBase* pSample) :
	m_pSample(pSample)
{
	const SampleCreateInfo& createInfo = m_pSample->GetCreateInfo();

	PlatformTime::Init();

	WindowCreateInfo windowCI;
	windowCI.Title = createInfo.Title.c_str();
	windowCI.Width = createInfo.Width;
	windowCI.Height = createInfo.Height;
	m_mainWindow.Init(windowCI);
}

SampleApp::~SampleApp()
{
}

void SampleApp::UpdateTime()
{
	m_lastTime = m_currentTime;
	m_currentTime = PlatformTime::Seconds();
}

bool SampleApp::Run()
{
	UpdateTime();

	m_pSample->Init(m_mainWindow.GetHandle());

	while (m_application.PollMessages())
	{
		UpdateTime();
		m_pSample->Update(GetDeltaTime());
	}

	m_pSample->Shutdown();

	return true;
}

}