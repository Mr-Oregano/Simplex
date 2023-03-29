
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <GLFW/glfw3.h>

#include "Win32GuiBackend.h"
#include "Win32Window.h"

// TODO: Use a UI config file instead.
void Config()
{
	ImVec4 *colors = ImGui::GetStyle().Colors;

	colors[ImGuiCol_Text] = { 1.00f, 1.00f, 1.00f, 1.00f };
	colors[ImGuiCol_TextDisabled] = { 0.50f, 0.50f, 0.50f, 1.00f };
	colors[ImGuiCol_WindowBg] = { 0.17f, 0.18f, 0.19f, 0.94f };
	colors[ImGuiCol_ChildBg] = { 0.17f, 0.18f, 0.19f, 0.94f };
	colors[ImGuiCol_PopupBg] = { 0.17f, 0.18f, 0.19f, 0.94f };
	colors[ImGuiCol_Border] = { 0.41f, 0.43f, 0.48f, 0.48f };
	colors[ImGuiCol_BorderShadow] = { 0.00f, 0.00f, 0.00f, 0.00f };
	colors[ImGuiCol_FrameBg] = { 0.38f, 0.42f, 0.48f, 0.54f };
	colors[ImGuiCol_FrameBgHovered] = { 0.75f, 0.79f, 0.83f, 0.40f };
	colors[ImGuiCol_FrameBgActive] = { 0.90f, 0.91f, 0.93f, 0.67f };
	colors[ImGuiCol_TitleBg] = { 0.17f, 0.18f, 0.19f, 0.94f };
	colors[ImGuiCol_TitleBgActive] = { 0.25f, 0.26f, 0.28f, 0.94f };
	colors[ImGuiCol_TitleBgCollapsed] = { 0.17f, 0.18f, 0.19f, 0.94f };
	colors[ImGuiCol_MenuBarBg] = { 0.14f, 0.14f, 0.14f, 1.00f };
	colors[ImGuiCol_ScrollbarBg] = { 0.02f, 0.02f, 0.02f, 0.00f };
	colors[ImGuiCol_ScrollbarGrab] = { 0.31f, 0.31f, 0.31f, 1.00f };
	colors[ImGuiCol_ScrollbarGrabHovered] = { 0.41f, 0.41f, 0.41f, 1.00f };
	colors[ImGuiCol_ScrollbarGrabActive] = { 0.51f, 0.51f, 0.51f, 1.00f };
	colors[ImGuiCol_CheckMark] = { 0.69f, 0.83f, 1.00f, 1.00f };
	colors[ImGuiCol_SliderGrab] = { 0.34f, 0.50f, 0.70f, 1.00f };
	colors[ImGuiCol_SliderGrabActive] = { 0.58f, 0.75f, 0.94f, 1.00f };
	colors[ImGuiCol_Header] = { 0.13f, 0.14f, 0.14f, 1.00f };
	colors[ImGuiCol_HeaderHovered] = { 0.42f, 0.54f, 0.67f, 0.43f };
	colors[ImGuiCol_HeaderActive] = { 0.59f, 0.70f, 0.83f, 0.42f };
	colors[ImGuiCol_Separator] = { 0.43f, 0.43f, 0.50f, 0.50f };
	colors[ImGuiCol_SeparatorHovered] = { 0.43f, 0.43f, 0.50f, 0.50f };
	colors[ImGuiCol_SeparatorActive] = { 0.43f, 0.43f, 0.50f, 0.50f };
	colors[ImGuiCol_ResizeGrip] = { 0.26f, 0.59f, 0.98f, 0.25f };
	colors[ImGuiCol_ResizeGripHovered] = { 0.26f, 0.59f, 0.98f, 0.67f };
	colors[ImGuiCol_ResizeGripActive] = { 0.26f, 0.59f, 0.98f, 0.95f };
	colors[ImGuiCol_Tab] = { 0.35f, 0.35f, 0.35f, 0.86f };
	colors[ImGuiCol_TabHovered] = { 0.51f, 0.51f, 0.51f, 0.80f };
	colors[ImGuiCol_TabActive] = { 0.52f, 0.52f, 0.52f, 1.00f };
	colors[ImGuiCol_TabUnfocused] = { 0.35f, 0.35f, 0.35f, 0.86f };
	colors[ImGuiCol_TabUnfocusedActive] = { 0.52f, 0.52f, 0.52f, 1.00f };
	colors[ImGuiCol_DockingPreview] = { 0.26f, 0.59f, 0.98f, 0.70f };
	colors[ImGuiCol_DockingEmptyBg] = { 0.20f, 0.20f, 0.20f, 1.00f };
	colors[ImGuiCol_PlotLines] = { 0.90f, 0.70f, 0.00f, 1.00f };
	colors[ImGuiCol_PlotLinesHovered] = { 1.00f, 0.43f, 0.35f, 1.00f };
	colors[ImGuiCol_PlotHistogram] = { 0.90f, 0.70f, 0.00f, 1.00f };
	colors[ImGuiCol_PlotHistogramHovered] = { 1.00f, 0.60f, 0.00f, 1.00f };
	colors[ImGuiCol_TextSelectedBg] = { 0.26f, 0.59f, 0.98f, 0.35f };
	colors[ImGuiCol_DragDropTarget] = { 1.00f, 1.00f, 0.00f, 0.90f };
	colors[ImGuiCol_NavHighlight] = { 0.26f, 0.59f, 0.98f, 1.00f };
	colors[ImGuiCol_NavWindowingHighlight] = { 1.00f, 1.00f, 1.00f, 0.70f };
	colors[ImGuiCol_NavWindowingDimBg] = { 0.80f, 0.80f, 0.80f, 0.20f };
	colors[ImGuiCol_ModalWindowDimBg] = { 0.80f, 0.80f, 0.80f, 0.35f };

	//ImGui::SetColorEditOptions(ImGui::ImGuiColorEditFlags_HEX);

	ImGuiStyle &style = ImGui::GetStyle();
	ImGuiIO &io = ImGui::GetIO();

	style.WindowPadding = { 6, 6 };
	style.FramePadding = { 15,  7 };
	style.ItemSpacing = { 12,  2 };
	style.ItemInnerSpacing = { 2,  2 };
	style.TouchExtraPadding = { 3,  3 };

	style.SelectableTextAlign = { 0.0f, 0.5f };

	style.ScrollbarSize = 11;
	style.GrabMinSize = 13;
	style.ChildBorderSize = 0;
	style.ScrollbarRounding = 12;
	style.TabRounding = 2;

	style.WindowMenuButtonPosition = ImGuiDir_Right;
	style.ColorButtonPosition = ImGuiDir_Left;

}

Win32GuiBackend::Win32GuiBackend(Window& window)
	: ImGuiBackend(window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	Config();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle &style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer bindings
	Win32Window &win32window = static_cast<Win32Window&>(window);
	ImGui_ImplGlfw_InitForOpenGL(win32window.GetNativeHandle(), true);
	ImGui_ImplOpenGL3_Init("#version 450");

	int width, height;
	glfwGetWindowSize(win32window.GetNativeHandle(), &width, &height);
	m_DisplaySize = ImVec2((float) width, (float) height);

	// TODO: May need to adjust relative path for built binary or change working directory, 
	//		 perhaps save some resources in executable.
	//
	m_Font = io.Fonts->AddFontFromFileTTF("../Simplex/res/fonts/opensans/OpenSans-Regular.ttf", 16.0f);
	io.Fonts->Build();
}

Win32GuiBackend::~Win32GuiBackend()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Win32GuiBackend::BeginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();
	ImGui::PushFont(m_Font);
}

void Win32GuiBackend::EndFrame()
{
	ImGui::PopFont();

	ImGuiIO &io = ImGui::GetIO();
	io.DisplaySize = m_DisplaySize;

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow *backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}
