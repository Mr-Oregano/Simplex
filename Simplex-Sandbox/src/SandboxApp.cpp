
#include "SandboxApp.h"

#include <Simplex.h>
#include <Ref.h>

Scope<App> App::CreateApp()
{
	return CreateScope<SandboxApp>();
}

SandboxApp::SandboxApp()
	: m_Running(false)
{
}

SandboxApp::~SandboxApp()
{
}

void SandboxApp::Start()
{
	m_Running = true;

	LOG_INFO("Hello world");
	LOG_WARN("Hello world");
	LOG_ERROR("Hello world");
	LOG_CRITICAL("Hello world");

	m_Window = Window::Create();
}

void SandboxApp::Update()
{
	m_Window->SetVisible();

	while (m_Running)
	{
		m_Window->Update();
	}
}

void SandboxApp::Shutdown()
{
	LOG_INFO("Terminating...");
}
