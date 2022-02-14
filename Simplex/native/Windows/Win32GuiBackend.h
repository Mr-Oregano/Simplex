#pragma once

#include <SmpxImGui.h>

class Win32GuiBackend : public ImGuiBackend
{
public:
	Win32GuiBackend(GLFWwindow *window);
	~Win32GuiBackend();

	virtual void StartFrame() override;
	virtual void EndFrame() override;
};