#pragma once

#include <App.h>
#include <Ref.h>
#include <Window.h>

#include <GraphicsContext.h>
#include <VertexBuffer.h>
#include <VertexArray.h>
#include <Pipeline.h>

class SandboxApp : public App
{
public:
	SandboxApp();
	~SandboxApp();

private:
	void Run() override;

	void OnEvent(Event &e);
	void OnUpdate();

private:
	Scope<Window> m_Window;
	bool m_Running;
	
	Ref<GraphicsContext> gfx;
	Ref<VertexBuffer> vb;
	Ref<VertexArray> va;
};