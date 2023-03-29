#pragma once

#include <imgui.h>
#include <functional>

#include <Dockspace.h>
#include <Ref.h>

class Window;

class ImGuiBackend
{
public:
	ImGuiBackend(Window& window);
	virtual ~ImGuiBackend() = default;

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	virtual Dockspace& GetDockspace() final;

private:
	Scope<Dockspace> m_Dockspace;
};