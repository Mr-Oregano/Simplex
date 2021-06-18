
#include "SandboxApp.h"

#include <Simplex.h>
#include <Ref.h>
#include <Event.h>

#include <functional>

using namespace SXG;

Scope<App> App::CreateApp()
{
	return CreateScope<SandboxApp>();
}

SandboxApp::SandboxApp()
	: m_Running(false)
{
}

SandboxApp::~SandboxApp()
{
}

void SandboxApp::Run()
{
	m_Running = true;

	m_Window = Window::Create();

	gfx = m_Window->GetGraphicsContext();

	VertexArrayProps va_create;
	va_create.topology = Topology::TRIANGLES;
	va = gfx->CreateArray(va_create);

	// First buffer
	std::vector<float> vertices = {
		-0.25f, -0.5f,	1.0f, 0.0f, 1.0f, 1.0f,
		 0.0f,  0.5f,	0.0f, 1.0f, 1.0f, 1.0f,
		 0.25f, -0.5f,	0.0f, 1.0f, 0.0f, 1.0f
	};

	VertexBufferLayout layout = {
		{ "a_Position", Types::FLOAT2 },
		{ "a_Color", Types::FLOAT4 }
	};

	VertexBufferProps vb_create;
	vb_create.data = vertices.data();
	vb_create.size = vertices.size() * sizeof(float);
	vb_create.layout = &layout;

	Ref<VertexBuffer> vb = gfx->CreateBuffer(vb_create);
	va->AddBuffer(vb);
	//

	// Second Buffer
	std::vector<int> color_indices = {
		0,
		1,
		2
	};

	layout = {
		{ "a_ColorIndex", Types::INT }
	};

	vb_create.data = color_indices.data();
	vb_create.size = color_indices.size() * sizeof(int);
	vb_create.layout = &layout;
	vb_create.inputDataClass = InputDataClass::PER_INSTANCE;
	vb_create.instanceDataRate = 1;

	vb = gfx->CreateBuffer(vb_create);
	va->AddBuffer(vb);
	//

	Ref<ShaderProgram> shader = gfx->CreateShaderFromFiles("res/shaders/vert.glsl", "res/shaders/frag.glsl");

	gfx->SetShaderProgram(shader);

	gfx->ClearColor(0.15f, 0.15f, 0.18f, 1.0f);

	m_Window->RegisterEventCallback([&](Event &e) { OnEvent(e); });

	m_Window->SetVisible();

	// Update
	while (m_Running)
	{
		OnUpdate();
		m_Window->Update();
	}
	//

	LOG_INFO("Terminating...");
}

void SandboxApp::OnEvent(Event &e)
{
	e.Dispatch<WindowClose>([&](auto)
	{
		m_Running = false;
	});

	e.Dispatch<KeyDown>([](KeyDown e)
	{
		LOG_INFO("Key down {0}", (char) e.keyCode);
	});

	e.Dispatch<MouseButtonDown>([](MouseButtonDown e)
	{
		LOG_INFO("Mouse button down {0}", e.mouseButton);
	});

	e.Dispatch<MouseScroll>([](MouseScroll e)
	{
		LOG_INFO("Mouse scrolled {0}", e.velocityY);
	});

	e.Dispatch<WindowResize>([&](WindowResize e)
	{
		gfx->SetViewport(0, 0, e.newWidth, e.newHeight);
	});
}

void SandboxApp::OnUpdate()
{
	gfx->BindArray(va);

	gfx->ClearRenderTarget(Clear::COLOR_BUFFER_BIT);
	gfx->DrawInstanced(3, va->GetVertexCount());
}
