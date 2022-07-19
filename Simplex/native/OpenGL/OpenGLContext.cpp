
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>
#include <FileSystem.h>

#include <utility>

#include "OpenGLUtility.h"

#include "OpenGLContext.h"
#include "Resources/OpenGLVertexBuffer.h"
#include "Resources/OpenGLIndexBuffer.h"
#include "Resources/OpenGLUniformBuffer.h"
#include "Resources/OpenGLVertexArray.h"
#include "Resources/OpenGLShaderProgram.h"
#include "Resources/OpenGLTexture2D.h"

using namespace SXG;

OpenGLContext::OpenGLContext()
	: m_VertexArrayManager(&m_VertexBufferManager, &m_IndexBufferManager)
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

void OpenGLContext::Draw(int count, int start_offset)
{
	VertexArrayHandle va = m_VertexArrayManager.GetSelected();

	ASSERT_CRITICAL(va, "No vertex array has been selected!");
	OpenGLVertexArray glva = m_VertexArrayManager.Get(va);
	
	GLenum topology = SXGTopologyToGL(glva.props.topology);

	glDrawArrays(topology, start_offset, count);
}

void OpenGLContext::DrawInstanced(int instances, int count, int start_offset)
{
	VertexArrayHandle va = m_VertexArrayManager.GetSelected();

	ASSERT_CRITICAL(va, "No vertex array has been selected!");
	OpenGLVertexArray glva = m_VertexArrayManager.Get(va);
	GLenum topology = SXGTopologyToGL(glva.props.topology);

	glDrawArraysInstanced(topology, start_offset, count, instances);
}

void OpenGLContext::DrawIndexed(int count)
{
	VertexArrayHandle va = m_VertexArrayManager.GetSelected();

	ASSERT_CRITICAL(va, "No vertex array has been selected!");
	OpenGLVertexArray glva = m_VertexArrayManager.Get(va);

	ASSERT_CRITICAL(glva.HasIndexBuffer(), "Vertex array must have a set index buffer for DrawIndexed!");
	OpenGLIndexBuffer glib = m_IndexBufferManager.Get(glva.indexBuffer);

	GLenum topology = SXGTopologyToGL(glva.props.topology);
	GLenum type = SXGTypeToGL(glib.indexType);

	glDrawElements(topology, count, type, nullptr);
}

void OpenGLContext::DrawIndexedInstanced(int instances, int count)
{
	VertexArrayHandle va = m_VertexArrayManager.GetSelected();

	ASSERT_CRITICAL(va, "No vertex array has been selected!");
	OpenGLVertexArray glva = m_VertexArrayManager.Get(va);

	ASSERT_CRITICAL(glva.HasIndexBuffer(), "Vertex array must have a set index buffer for DrawIndexed!");
	OpenGLIndexBuffer glib = m_IndexBufferManager.Get(glva.indexBuffer);

	GLenum topology = SXGTopologyToGL(glva.props.topology);
	GLenum type = SXGTypeToGL(glib.indexType);

	glDrawElementsInstanced(topology, count, type, nullptr, instances);
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
