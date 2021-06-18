
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>
#include <FileSystem.h>

#include "OpenGLUtility.h"

#include "OpenGLContext.h"
#include "OpenGLVertexBuffer.h"
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
}

Ref<VertexBuffer> OpenGLContext::CreateBuffer(VertexBufferProps props)
{
	return CreateRef<OpenGLVertexBuffer>(props);
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

	GLenum topology = SXGTopologyToGL(m_SelectedVA->GetTopology());

	glDrawArrays(topology, start_offset, count);
}

void OpenGLContext::DrawInstanced(int instances, int count, int start_offset)
{
	ASSERT_CRITICAL(m_SelectedVA != nullptr, "No vertex array has been selected!");

	GLenum topology = SXGTopologyToGL(m_SelectedVA->GetTopology());

	glDrawArraysInstanced(topology, start_offset, count, instances);
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
