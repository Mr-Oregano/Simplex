#pragma once

#include <SmpxImGui.h>

class LinuxGuiBackend : public ImGuiBackend
{
public:
	LinuxGuiBackend(Window& window);
	~LinuxGuiBackend();

	virtual void BeginFrame() override;
	virtual void EndFrame() override;

private:
	ImVec2 m_DisplaySize;
	ImFont *m_Font = nullptr;
};