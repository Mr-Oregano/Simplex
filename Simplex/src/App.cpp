
// Precompiled
#include <sxpch.h>
//

#include <App.h>

#include <Log.h>
#include <Simplex.h>

App::App(const AppProps &props)
{
#ifndef SMPX_CONFIG_DIST
	Log::Init("SIMPLEX");
#endif

	m_Window = Window::Create(props.windowProps);

#ifdef SMPX_IMGUI
	m_Gui = m_Window->CreateGuiBackend();
#endif

	LOG_INFO("Initialized services.");
}

App::~App()
{
	LOG_INFO("Shutting down services...");

#ifndef SMPX_CONFIG_DIST
	Log::Shutdown();
#endif
}

void App::Run()
{
	m_Running = true;
	
	OnStart();

	m_Window->SetVisible(true);

	while (m_Running)
	{
		OnUpdate();

#ifdef SMPX_IMGUI
		m_Gui->BeginFrame();
		OnImGui();
		m_Gui->EndFrame();
#endif

		m_Window->Update();
	}

	OnStop();
}
