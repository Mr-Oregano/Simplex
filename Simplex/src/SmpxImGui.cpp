// Precompiled
#include <sxpch.h>
//

#include <SmpxImGui.h>
#include <Window.h>

ImGuiBackend::ImGuiBackend(Window& window)
	: m_Dockspace(CreateScope<Dockspace>(window.GetGraphicsContext(), window.GetWidth(), window.GetHeight()))
{}

Dockspace& ImGuiBackend::GetDockspace()
{
	return *m_Dockspace;
}
