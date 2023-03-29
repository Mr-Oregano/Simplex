
// Precompiled Header
#include "sxpch.h"
//

#include <Sxg.h>

#include "Window.h"
#include "Win32Window.h"

#include <glad/glad.h>

#include "../OpenGL/OpenGLContext.h"
#include "Win32GuiBackend.h"

using namespace SXG;

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

void Win32Window::RegisterEventCallback(std::function<void(Event&)> callback)
{
	m_Data.event_cb = callback;
}

void Win32Window::InitWindow()
{
	if (!s_InitializedGLFW)
	{
		int status = glfwInit();
		ASSERT_CRITICAL(status, "Failed to initialize the GLFW library!");
		s_InitializedGLFW = true;
	}

	switch (m_Data.props.graphics.desiredAPI)
	{
		case API::OPENGL:
		{
			int versionMajor = m_Data.props.graphics.minVersion >> 8;
			int versionMinor = m_Data.props.graphics.minVersion & 0xff;

			ASSERT_CRITICAL(versionMajor >= 4 && versionMinor >= 5, "Only OpenGL 4.5+ is currently supported");

			// Cross platform APIs need to be initialized in a platform dependent way.
			//
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

			CreateWindowHandle();
			
			glfwMakeContextCurrent(m_Handle);
			bool success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			//

			ASSERT_CRITICAL(success, "Could not initialize the OpenGL context!");
			m_Gfx = CreateRef<OpenGLContext>();

			LOG_INFO("Backend API selected: OpenGL {0}", 
				reinterpret_cast<const char*>(glGetString(GL_VERSION)));
			
			LOG_INFO("Using physical device: {0}\t({1})", 
				reinterpret_cast<const char *>(glGetString(GL_RENDERER)), 
				reinterpret_cast<const char *>(glGetString(GL_VENDOR)));

			break;
		}
	}

	ASSERT_CRITICAL(m_Gfx != nullptr, "The desired graphics API is not available on this platform.");

	SetupEventHandling();

	SetVsync(m_Data.props.vysnc);
}

void Win32Window::DestroyWindow()
{
	glfwDestroyWindow(m_Handle);
}
	
void Win32Window::CreateWindowHandle()
{
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
}

void Win32Window::SetupEventHandling()
{
	glfwSetWindowUserPointer(m_Handle, &m_Data);

	glfwSetKeyCallback(m_Handle, [](GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		auto &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		auto &call = data.event_cb;

		if (!call)
			return;

		if (action == GLFW_RELEASE)
		{
			KeyUp e = {};
			e.keyCode = key;
			call(e);
			return;
		}

		KeyDown e = {};
		e.keyCode = key;
		call(e);

	});

	glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow *window, int button, int action, int mods)
	{
		auto &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		auto &call = data.event_cb;

		if (!call)
			return;

		if  (action == GLFW_PRESS)
		{
			MouseButtonDown e = {};
			glfwGetCursorPos(window, &e.x, &e.y);
			e.mouseButton = button;
			call(e);
			return;
		}

		MouseButtonUp e = {};
		glfwGetCursorPos(window, &e.x, &e.y);
		e.mouseButton = button;
		call(e);
	});

	glfwSetCursorPosCallback(m_Handle, [](GLFWwindow *window, double xpos, double ypos)
	{
		auto &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
		auto &call = data.event_cb;

		if (!call)
			return;

		MouseMove e = {};

		e.dx = xpos - e.lastX;
		e.dy = ypos - e.lastY;
		e.lastX = e.x;
		e.lastY = e.y;
		e.x = xpos;
		e.y = ypos;

		call(e);
	});

	glfwSetScrollCallback(m_Handle, [](GLFWwindow *window, double xoffset, double yoffset)
	{
		auto &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
		auto &call = data.event_cb;

		if (!call)
			return;

		MouseScroll e = {};

		e.velocityX = xoffset;
		e.velocityY = yoffset;

		call(e);
	});

	glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow *window)
	{
		auto &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
		auto &call = data.event_cb;

		if (!call)
			return;

		WindowClose e = {};
		call(e);
	});

	glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow *window, int width, int height)
	{
		auto &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
		auto &call = data.event_cb;

		if (!call)
			return;

		WindowResize e = {};
		e.newWidth = width;
		e.newHeight = height;
		call(e);

	});
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

Ref<GraphicsContext> Win32Window::GetGraphicsContext()
{
	return m_Gfx;
}

Scope<ImGuiBackend> Win32Window::CreateGuiBackend()
{
	ASSERT_CRITICAL(m_Data.props.graphics.desiredAPI == API::OPENGL, "ImGui backend currently requires OpenGL.");

	return CreateScope<Win32GuiBackend>(*this);
}
