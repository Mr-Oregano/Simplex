
#include "SandboxApp.h"

#include <Simplex.h>
#include <Ref.h>
#include <Event.h>

#include <ImageFileReader.h>
#include <Texture2D.h>

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
	LOG_INFO("Test");
	m_Running = true;

	WindowProps win_create;
	win_create.title = "Simplex Sandbox";
	win_create.width = 1280;
	win_create.height = 720;
	win_create.resizable = true;
	win_create.vysnc = false;
	win_create.mode = WindowMode::Windowed;
	win_create.graphics.desiredAPI = API::OPENGL;
	win_create.graphics.desiredVersion = MakeOpenGLVersion(4, 6);
	win_create.graphics.minVersion = MakeOpenGLVersion(4, 5);

	m_Window = Window::Create(win_create);

	gfx = m_Window->GetGraphicsContext();

	VertexArrayProps va_create;
	va_create.topology = Topology::TRIANGLES;
	va = gfx->CreateArray(va_create);

	// First buffer
	std::vector<float> vertices = {
		-0.5f, -0.5f,	1.0f, 0.0f, 1.0f, 1.0f,	  0.0f, 0.0f,
		-0.5f,  0.5f,	0.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		 0.5f,  0.5f,	0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f, -0.5f,	0.0f, 1.0f, 0.0f, 1.0f,	  1.0f, 0.0f
	};

	VertexBufferLayout layout = {
		{ "a_Position", Types::FLOAT2 },
		{ "a_Color", Types::FLOAT4 },
		{ "a_TexCoords", Types::FLOAT2 }
	};

	VertexBufferProps vb_create;
	vb_create.data = vertices.data();
	vb_create.size = vertices.size() * sizeof(float);
	vb_create.layout = &layout;

	Ref<VertexBuffer> vb = gfx->CreateBuffer(vb_create);
	va->AddBuffer(vb);
	//

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	IndexBufferProps ib_create;
	ib_create.data = indices.data();
	ib_create.size = indices.size() * sizeof(unsigned int);
	ib_create.indexType = Types::UINT;

	Ref<IndexBuffer> ib = gfx->CreateIndexBuffer(ib_create);
	va->SetIndexBuffer(ib);

	Ref<ShaderProgram> shader = gfx->CreateShaderFromFiles("res/shaders/vert.glsl", "res/shaders/frag.glsl");

	gfx->BindShaderProgram(shader);

	Scope<ImageFileReader> imageReader = ImageFileReader::Load("res/textures/logo.png");
	unsigned char *texData = imageReader->ReadAllBytes();

	TextureProps tex_create;
	tex_create.data = texData;
	tex_create.width = imageReader->GetWidth();
	tex_create.height = imageReader->GetHeight();
	tex_create.channels = imageReader->GetNumChannels();

	Ref<Texture2D> texture = gfx->CreateTexture2D(tex_create);
	gfx->BindTexture2D(texture);

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
	gfx->DrawIndexed(va->GetVertexCount());
}
