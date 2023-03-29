#pragma once

#include <GraphicsContext.h>
#include <FrameBuffer.h>

#include <Event.h>
#include <Ref.h>

#include <cstdint>

struct ViewportContentProps
{
	double width;
	double height;
	double x;
	double y;
};

class Dockspace
{
public:
	Dockspace(Ref<GraphicsContext> gfx, std::uint32_t width, std::uint32_t height);

	void Begin();
	void End();

	void BeginCapture() const;
	void EndCapture() const;
	void Resize(unsigned int width, unsigned int height);

	void Update();
	void OnEvent(Event &e);

private:
	Ref<GraphicsContext> m_Gfx;
	FrameBufferManager &m_FrameBuffers;
	FrameBufferHandle m_FrameBufferHandle;

	bool m_Focused = false;
	std::uint32_t m_Width = 0;
	std::uint32_t m_Height = 0;

	ViewportContentProps m_ViewportContentProps{};
};