
#include "SandboxApp.h"

#include <Simplex.h>
#include <Ref.h>
#include <Event.h>

#include <ImageFileReader.h>
#include <Texture2D.h>

#include <functional>

#include <SmpxImGui.h>

using namespace SXG;

Scope<App> App::CreateApp()
{
	AppProps props;

	props.name = "The Simplex Sandbox";
	props.version = MAKE_APP_VERSION(1, 0);
	props.windowProps.title = "Simplex Sandbox";
	props.windowProps.width = 1920;
	props.windowProps.height = 1080;
	props.windowProps.resizable = true;
	props.windowProps.vysnc = false;
	props.windowProps.mode = WindowMode::Maximized;
	props.windowProps.graphics.desiredAPI = API::OPENGL;
	props.windowProps.graphics.desiredVersion = MakeOpenGLVersion(4, 6);
	props.windowProps.graphics.minVersion = MakeOpenGLVersion(4, 5);

	return CreateScope<SandboxApp>(props);
}

SandboxApp::SandboxApp(const AppProps &props) : App(props) {}

SandboxApp::~SandboxApp() {}

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

void SandboxApp::OnStart()
{
	m_Window->RegisterEventCallback([&](Event &e) { OnEvent(e); });
	gfx = m_Window->GetGraphicsContext();
	gfx->ClearColor(0.15f, 0.15f, 0.18f, 1.0f);

	VertexArrayProps va_create;
	va_create.topology = Topology::TRIANGLES;

	va = gfx->GetVertexArrayManager().Create(va_create);

	// First buffer
	std::vector<float> vertices = 
	{
		-0.5f, -0.5f,	1.0f, 0.0f, 1.0f, 1.0f,	  0.0f, 0.0f,
		-0.5f,  0.5f,	0.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		 0.5f,  0.5f,	0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f, -0.5f,	0.0f, 1.0f, 0.0f, 1.0f,	  1.0f, 0.0f
	};

	std::vector<float> uniforms = 
	{
		0.5f, 0.8f, 1.0f, 1.0f
	};

	std::vector<float> vs_uniforms = 
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
	};

	VertexBufferLayout layout = 
	{
		{ "a_Position", Types::FLOAT2 },
		{ "a_Color", Types::FLOAT4 },
		{ "a_TexCoords", Types::FLOAT2 }
	};

	VertexBufferProps vb_create;
	vb_create.data = vertices.data();
	vb_create.size = vertices.size() * sizeof(float);
	vb_create.layout = &layout;

	VertexBufferHandle vb = gfx->GetVertexBufferManager().Create(vb_create);
	gfx->GetVertexArrayManager().AddBuffer(va, vb);
	//

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	IndexBufferProps ib_create;
	ib_create.data = indices.data();
	ib_create.size = indices.size() * sizeof(unsigned int);
	ib_create.indexType = Types::UINT;

	IndexBufferHandle ib = gfx->GetIndexBufferManager().Create(ib_create);
	gfx->GetVertexArrayManager().SetIndexBuffer(va, ib);

	ShaderProgramHandle shader = gfx->GetShaderManager().CreateFromFiles("res/shaders/vert.glsl", "res/shaders/frag.glsl");

	UniformBufferProps ub_create;
	ub_create.data = uniforms.data();
	ub_create.size = uniforms.size() * sizeof(float);
	ub_create.usage = BufferUsage::STATIC;

	UniformBufferHandle ub = gfx->GetUniformBufferManager().Create(ub_create);

	ub_create.data = vs_uniforms.data();
	ub_create.size = vs_uniforms.size() * sizeof(float);

	UniformBufferHandle ub2 = gfx->GetUniformBufferManager().Create(ub_create);

	Scope<ImageFileReader> imageReader = ImageFileReader::Load("res/textures/logo.png");
	unsigned char *texData = imageReader->ReadAllBytes();

	TextureProps tex_create;
	tex_create.data = texData;
	tex_create.width = imageReader->GetWidth();
	tex_create.height = imageReader->GetHeight();
	tex_create.channels = imageReader->GetNumChannels();

	TextureHandle texture = gfx->GetTexture2DManager().Create(tex_create);

	gfx->GetShaderManager().Bind(shader);
	gfx->GetTexture2DManager().Bind(texture);
	gfx->GetUniformBufferManager().Bind(ub, 1, ShaderStageType::FRAGMENT);
	gfx->GetUniformBufferManager().Bind(ub2, 0, ShaderStageType::VERTEX);
}

void SandboxApp::OnUpdate()
{
	m_Gui->GetDockspace().BeginCapture();

	gfx->GetVertexArrayManager().Bind(va);

	gfx->ClearRenderTarget(Clear::COLOR_BUFFER_BIT);
	gfx->DrawIndexed(gfx->GetVertexArrayManager().GetVertexCount(va));

	m_Gui->GetDockspace().EndCapture();
}

void SandboxApp::OnStop() {}

void SandboxApp::OnImGui()
{
	m_Gui->GetDockspace().Begin();

	m_Gui->GetDockspace().Update();
	ImGui::ShowDemoWindow();
	
	m_Gui->GetDockspace().End();
}