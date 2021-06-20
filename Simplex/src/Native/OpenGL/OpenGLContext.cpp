
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>
#include <FileSystem.h>

#include "OpenGLUtility.h"

#include "OpenGLContext.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShaderProgram.h"

using namespace SXG;

OpenGLContext::OpenGLContext()
{
#ifndef SMPX_CONFIG_DIST
	glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_LOW:
		case GL_DEBUG_SEVERITY_MEDIUM: LOG_WARN(message); break;
		case GL_DEBUG_SEVERITY_HIGH: LOG_ERROR(message); break;
		}
	}, nullptr);
#endif
}

OpenGLContext::~OpenGLContext()
{
	LOG_INFO("Deleting resource: Graphics Context");
}

Ref<VertexBuffer> OpenGLContext::CreateBuffer(VertexBufferProps props)
{
	return CreateRef<OpenGLVertexBuffer>(props);
}

Ref<IndexBuffer> OpenGLContext::CreateIndexBuffer(IndexBufferProps props)
{
	return CreateRef<OpenGLIndexBuffer>(props);
}

Ref<VertexArray> OpenGLContext::CreateArray(VertexArrayProps props)
{
	return CreateRef<OpenGLVertexArray>(props);
}

Ref<ShaderProgram> OpenGLContext::CreateShaderFromFiles(const std::string &vert_path, const std::string &frag_path)
{
	std::string vert_src = ReadFileToString(vert_path);
	std::string frag_src = ReadFileToString(frag_path);

	return CreateRef<OpenGLShaderProgram>(vert_src, frag_src);
}

void OpenGLContext::Draw(int count, int start_offset)
{
	ASSERT_CRITICAL(m_SelectedVA != nullptr, "No vertex array has been selected!");
	OpenGLVertexArray *glva = static_cast<OpenGLVertexArray *>(m_SelectedVA.get());

	VertexArrayDrawInfo drawInfo = glva->GetDrawInfo();
	GLenum topology = SXGTopologyToGL(drawInfo.topology);

	glDrawArrays(topology, start_offset, count);
}

void OpenGLContext::DrawInstanced(int instances, int count, int start_offset)
{
	ASSERT_CRITICAL(m_SelectedVA != nullptr, "No vertex array has been selected!");
	OpenGLVertexArray *glva = static_cast<OpenGLVertexArray *>(m_SelectedVA.get());

	VertexArrayDrawInfo drawInfo = glva->GetDrawInfo();
	GLenum topology = SXGTopologyToGL(drawInfo.topology);

	glDrawArraysInstanced(topology, start_offset, count, instances);
}

void OpenGLContext::DrawIndexed(int count)
{
	ASSERT_CRITICAL(m_SelectedVA != nullptr, "No vertex array has been selected!");
	OpenGLVertexArray *glva = static_cast<OpenGLVertexArray*>(m_SelectedVA.get());

	ASSERT_CRITICAL(glva->HasIndexBuffer(), "Vertex array must have a set index buffer for DrawIndexed!");
	
	VertexArrayDrawInfo drawInfo = glva->GetDrawInfo();
	GLenum topology = SXGTopologyToGL(drawInfo.topology);
	GLenum type = SXGTypeToGL(drawInfo.indexType);

	glDrawElements(topology, count, type, nullptr);
}

void OpenGLContext::DrawIndexedInstanced(int instances, int count)
{
	ASSERT_CRITICAL(m_SelectedVA != nullptr, "No vertex array has been selected!");
	OpenGLVertexArray *glva = static_cast<OpenGLVertexArray *>(m_SelectedVA.get());

	ASSERT_CRITICAL(glva->HasIndexBuffer(), "Vertex array must have a set index buffer for DrawIndexed!");

	VertexArrayDrawInfo drawInfo = glva->GetDrawInfo();
	GLenum topology = SXGTopologyToGL(drawInfo.topology);
	GLenum type = SXGTypeToGL(drawInfo.indexType);

	glDrawElementsInstanced(topology, count, type, nullptr, instances);
}

void OpenGLContext::BindArray(Ref<VertexArray> va)
{
	ASSERT_CRITICAL(va != nullptr, "Vertex Array is null!");

	// The passed buffer better be an opengl buffer, otherwise
	// I will be disappointed >:(
	//
	OpenGLVertexArray *glva = static_cast<OpenGLVertexArray*>(va.get());
	glBindVertexArray(glva->ContextID());

	m_SelectedVA = va;
}

void OpenGLContext::SetShaderProgram(Ref<ShaderProgram> shader)
{
	ASSERT_CRITICAL(shader != nullptr, "Shader Program is null!");

	// The passed shader better be an opengl shader, otherwise
	// I will be disappointed >:(
	//
	OpenGLShaderProgram *glsp = static_cast<OpenGLShaderProgram*>(shader.get());
	glUseProgram(glsp->ContextID());
}

void OpenGLContext::ClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void OpenGLContext::ClearRenderTarget(Clear flags)
{
	GLbitfield bitfield = 0;

	bitfield |= (!!(flags & Clear::COLOR_BUFFER_BIT)) * GL_COLOR_BUFFER_BIT;
	bitfield |= (!!(flags & Clear::DEPTH_BUFFER_BIT)) * GL_DEPTH_BUFFER_BIT;

	glClear(bitfield);
}

void OpenGLContext::SetViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}
