
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>

#include "OpenGLUtility.h"

#include "OpenGLContext.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexArray.h"

Ref<VertexBuffer> OpenGLContext::CreateBuffer(VertexBufferProps props)
{
	return CreateRef<OpenGLVertexBuffer>(props);
}

Ref<VertexArray> OpenGLContext::CreateArray(VertexArrayProps props)
{
	return CreateRef<OpenGLVertexArray>(props);
}

Ref<Pipeline> OpenGLContext::CreatePipelineFromFiles(const std::string &vertpath, const std::string &fragpath)
{
	return CreateRef<Pipeline>();
}

void OpenGLContext::Draw(int count, int start_offset)
{
	ASSERT_CRITICAL(m_SelectedVA != nullptr, "No vertex array has been selected!");

	GLenum topology = SXGTopologyToGL(m_SelectedVA->GetTopology());

	glDrawArrays(topology, start_offset, count);
}

void OpenGLContext::SetArray(Ref<VertexArray> va)
{
	// The passed buffer better be an opengl buffer, otherwise
	// I will be disappointed >:(
	//
	OpenGLVertexArray *glva = static_cast<OpenGLVertexArray*>(va.get());
	glBindVertexArray(glva->ContextID());

	m_SelectedVA = va;
}

void OpenGLContext::SetPipeline(Ref<Pipeline> shader)
{

}

void OpenGLContext::ClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void OpenGLContext::ClearRenderTarget(SXG flags)
{
	GLbitfield bitfield = 0;

	bitfield |= (!!(flags & SXG::COLOR_BUFFER_BIT)) * GL_COLOR_BUFFER_BIT;
	bitfield |= (!!(flags & SXG::DEPTH_BUFFER_BIT)) * GL_DEPTH_BUFFER_BIT;

	glClear(bitfield);
}

RendererAPI OpenGLContext::CurrentRenderer()
{
	return RendererAPI::SXG_OPENGL;
}
