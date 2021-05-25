
#include "SandboxApp.h"

#include <Simplex.h>
#include <Ref.h>
#include <Event.h>

#include <functional>

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

void SandboxApp::Run()
{
	m_Running = true;

	LOG_INFO("Hello world");
	LOG_WARN("Hello world");
	LOG_ERROR("Hello world");
	LOG_CRITICAL("Hello world");

	m_Window = Window::Create();

	m_Window->RegisterEventCallback([&](Event &e) { OnEvent(e); });

	m_Window->SetVisible();

	// Update
	while (m_Running)
	{
		m_Window->Update();
	}
	//

	LOG_INFO("Terminating...");
}

void SandboxApp::OnEvent(Event &e)
{
	e.Dispatch<WindowClose>([&](auto)
	{
		m_Running = false;
	});

	e.Dispatch<KeyDown>([](KeyDown e)
	{
		LOG_INFO("Key down {0}", (char) e.keyCode);
	});

	e.Dispatch<MouseButtonDown>([](MouseButtonDown e)
	{
		LOG_INFO("Mouse button down {0}", e.mouseButton);
	});

	e.Dispatch<MouseScroll>([](MouseScroll e)
	{
		LOG_INFO("Mouse scrolled {0}", e.velocityY);
	});
}
