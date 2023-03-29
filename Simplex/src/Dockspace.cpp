
// Precompiled
#include <sxpch.h>
//

#include <Sxg.h>
#include <SmpxImGui.h>

#include "Dockspace.h"

Dockspace::Dockspace(Ref<GraphicsContext> gfx, std::uint32_t width, std::uint32_t height)
	: m_Gfx(gfx), m_FrameBuffers(gfx->GetFrameBufferManager())
{
	FrameBufferProps props;
	props.width = width;
	props.height = height;
	m_FrameBufferHandle = m_Gfx->GetFrameBufferManager().Create(props);

	m_Width = props.width;
	m_Height = props.height;
}

void Dockspace::BeginCapture() const
{
	m_FrameBuffers.Bind(m_FrameBufferHandle);
	m_Gfx->ClearRenderTarget(SXG::Clear::COLOR_BUFFER_BIT);
	m_Gfx->SetViewport(0, 0, m_Width, m_Height);
}

void Dockspace::EndCapture() const
{
	m_FrameBuffers.Unbind(m_FrameBufferHandle);
}

void Dockspace::Resize(unsigned int width, unsigned int height)
{
	m_Width = width;
	m_Height = height;
	m_FrameBuffers.Resize(m_FrameBufferHandle, width, height);
}

void Dockspace::Begin()
{
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiViewport *viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
	ImGui::Begin("DockSpace", nullptr, window_flags);
	ImGui::PopStyleVar(3);

	// DockSpace
	ImGuiID dockspace_id = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspace_id, { 0.0f, 0.0f }, dockspace_flags);
}

void Dockspace::Update()
{
	// Retrieve the current window position (relative to desktop) of the dockspace.
	m_ViewportContentProps.x = ImGui::GetWindowPos().x;
	m_ViewportContentProps.y = ImGui::GetWindowPos().y;

	ImGuiID dockspace_id = ImGui::GetID("DockSpace");
	ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_Always);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
	ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration);

	m_Focused = ImGui::IsWindowFocused();

	size_t textureID = m_FrameBuffers.GetColorAttachmentID(m_FrameBufferHandle);
	ImVec2 drawRegion = ImGui::GetContentRegionAvail();
	drawRegion.x = drawRegion.y * (float) m_Width / (float) m_Height;

	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - drawRegion.x) * 0.5f);

	// TODO: Ideally, use a child window containing the image (make mouse mapping/event handling easier).
	m_ViewportContentProps.width = drawRegion.x;
	m_ViewportContentProps.height = drawRegion.y;
	m_ViewportContentProps.x = (double) ImGui::GetWindowPos().x - m_ViewportContentProps.x + ImGui::GetCursorPosX();
	m_ViewportContentProps.y = (double) ImGui::GetWindowPos().y - m_ViewportContentProps.y + ImGui::GetCursorPosY();

	ImGui::Image((void *) textureID, drawRegion, { 0, 1 }, { 1, 0 });

	ImGui::End();
	ImGui::PopStyleVar();
}

void Dockspace::End()
{
	ImGui::End();
}

void Dockspace::OnEvent(Event &e) {}
