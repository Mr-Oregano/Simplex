#pragma once

#include <Window.h>
#include <Simplex.h>

#include <GLFW/glfw3.h>

class Win32Window : public Window
{

public:
	Win32Window(WindowProps props);
	virtual ~Win32Window();

	virtual void Update() override;

	virtual int GetWidth() const override { return m_Data.props.width; }
	virtual int GetHeight() const override { return m_Data.props.height; }
	virtual void *GetNativeWindowHandle() const override { return (void*) m_Handle; }

	virtual void SetVsync(bool vsync) override;
	virtual void SetVisible(bool visible) override;
	virtual void SetWindowMode(WindowMode mode) override;

	virtual bool IsVysncEnabled() const override { return m_Data.props.vysnc; }
	virtual bool IsVisible() const override { return m_Visible; }

private:
	void InitWindow();
	void DestroyWindow();
	void CreateWindowHandle();

private:
	GLFWwindow *m_Handle = nullptr;

	struct WindowData
	{
		WindowProps props;

	} m_Data;

	bool m_Visible = false;

private:
	static bool s_InitializedGLFW;
};