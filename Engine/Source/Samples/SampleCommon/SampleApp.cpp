#include "SampleApp.h"

namespace ow
{

SampleApp::SampleApp(SampleBase* pSample, int argc, const char** argv)
{
	m_commandLine.Init(argc, argv);
	uint32 width = m_commandLine.GetUInt("width").value_or(1280);
	uint32 height = m_commandLine.GetUInt("height").value_or(720);

	PlatformTime::Init();

	WindowCreateInfo windowCI;
	windowCI.Title = m_commandLine.GetString("title").value_or("Sample");
	windowCI.Width = width;
	windowCI.Height = height;
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

	auto backend = m_commandLine.GetEnum<RHIBackend>("backend").value_or(RHIBackend::Vulkan);
	m_pSample->Init(backend, m_mainWindow.GetHandle(), m_mainWindow.GetWidth(), m_mainWindow.GetHeight());

	while (m_application.PollMessages())
	{
		UpdateTime();
		m_pSample->Update(GetDeltaTime());
	}

	m_pSample->Shutdown();

	return true;
}

}