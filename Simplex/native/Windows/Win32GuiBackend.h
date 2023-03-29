#pragma once

#include <SmpxImGui.h>

class Win32GuiBackend : public ImGuiBackend
{
public:
	Win32GuiBackend(Window& window);
	~Win32GuiBackend();

	virtual void BeginFrame() override;
	virtual void EndFrame() override;

private:
	ImVec2 m_DisplaySize;
	ImFont *m_Font = nullptr;
};