#pragma once

#include <App.h>
#include <Ref.h>
#include <Window.h>

#include <GraphicsContext.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <UniformBuffer.h>
#include <VertexArray.h>
#include <ShaderProgram.h>

class SandboxApp : public App
{
public:
	SandboxApp(const AppProps &props);
	~SandboxApp();

private:
	void OnStart() override;
	void OnUpdate() override;
	void OnStop() override;
	void OnImGui() override;

	void OnEvent(Event &e);

private:
	Ref<VertexArray> va;
	Ref<GraphicsContext> gfx;
};