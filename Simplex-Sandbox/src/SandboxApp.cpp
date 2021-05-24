
#include "SandboxApp.h"

#include <Simplex.h>
#include <Ref.h>

Scope<App> App::GetApp()
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
}

void SandboxApp::Update()
{
	while (m_Running)
	{
	}
}
