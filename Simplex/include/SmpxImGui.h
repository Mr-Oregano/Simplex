#pragma once

#include <imgui.h>

class ImGuiBackend
{
public:
	virtual ~ImGuiBackend() = default;
	virtual void StartFrame() = 0;
	virtual void EndFrame() = 0;
};