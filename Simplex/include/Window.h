#pragma once

#include <Simplex.h>
#include <Ref.h>
#include <Event.h>

#include <functional>

enum class WindowMode
{
	Windowed,
	WindowedFullscreen,
	Fullscreen,
	Maximized
};

struct WindowProps
{
	int width = 1280;
	int height = 720;
	const char *title = "Untitled";
	WindowMode mode = WindowMode::Windowed;
	bool vysnc = false;
	bool resizable = true;
};

class Window
{
public:
	virtual void Update() = 0;
	virtual void RegisterEventCallback(std::function<void(Event&)> callback) = 0;

	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void* GetNativeWindowHandle() const = 0;

	virtual void SetVsync(bool vsync) = 0;
	virtual void SetVisible(bool visible = true) = 0;
	virtual void SetWindowMode(WindowMode mode) = 0;

	virtual bool IsVysncEnabled() const = 0;
	virtual bool IsVisible() const = 0;

	static Scope<Window> Create(WindowProps props = WindowProps());
};
