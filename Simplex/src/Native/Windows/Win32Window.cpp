
// Precompiled Header
#include "sxpch.h"
//

#include "Window.h"
#include "Win32Window.h"

Scope<Window> Window::Create(WindowProps props)
{
	return CreateScope<Win32Window>(props);
}

bool Win32Window::s_InitializedGLFW = false;

Win32Window::Win32Window(WindowProps props)
{
	m_Data.props = props;
	InitWindow();
}
	
Win32Window::~Win32Window()
{
	DestroyWindow();
}
	
void Win32Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Handle);
}

void Win32Window::InitWindow()
{
	if (!s_InitializedGLFW)
	{
		int status = glfwInit();
		ASSERT_CRITICAL(status, "Failed to initialize the GLFW library!");
		s_InitializedGLFW = true;
	}

	CreateWindowHandle();
	SetVsync(m_Data.props.vysnc);
}
	
void Win32Window::DestroyWindow()
{
	glfwDestroyWindow(m_Handle);
}
	
void Win32Window::CreateWindowHandle()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, m_Data.props.resizable);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, m_Data.props.mode == WindowMode::Maximized);

	switch (m_Data.props.mode)
	{
		case WindowMode::Fullscreen:
		{
			GLFWmonitor *monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

			m_Handle = glfwCreateWindow(
				m_Data.props.width, 
				m_Data.props.height,
				m_Data.props.title,
				monitor,
				nullptr);
		}
		break;

		case WindowMode::WindowedFullscreen:
		{
			// In WindowedFullscreen mode, width and height variables are ignored and instead
			// Re-assigned to the width and height of the the primary mointor's 
			// video mode.

			GLFWmonitor *monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);

			m_Data.props.width = vidmode->width;
			m_Data.props.height = vidmode->height + 1; 
			// Bug? Video mode for the monitor changes unless height is +1 unit taller.

			glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

			glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
			glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

			m_Handle = glfwCreateWindow(
				m_Data.props.width,
				m_Data.props.height,
				m_Data.props.title,
				nullptr,
				nullptr);
		}
		break;

		default:
		{
			m_Handle = glfwCreateWindow(
				m_Data.props.width,
				m_Data.props.height,
				m_Data.props.title,
				nullptr,
				nullptr);
		}
	}

	ASSERT_CRITICAL(m_Handle, "Failed to create the window");
	glfwMakeContextCurrent(m_Handle);
}
	
void Win32Window::SetVisible(bool visible)
{
	m_Visible = visible;

	if (m_Visible)
	{
		glfwShowWindow(m_Handle);
		return;
	}

	glfwHideWindow(m_Handle);
}

void Win32Window::SetWindowMode(WindowMode mode)
{
	// TODO: Implement SetWindowMode functionality
}

void Win32Window::SetVsync(bool vsync)
{
	m_Data.props.vysnc = vsync; 
	glfwSwapInterval(vsync ? 1 : 0);
}
