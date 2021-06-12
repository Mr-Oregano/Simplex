
// Precompiled Header
#include "sxpch.h"
//

#include "OpenGLVertexBuffer.h"

OpenGLVertexBuffer::OpenGLVertexBuffer(VertexBufferProps props)
	: m_Props(props)
{
	m_Size = (int) (m_Props.data.size() * sizeof(float));

	glCreateBuffers(1, &m_ContextID);
	glNamedBufferStorage(m_ContextID, m_Size, m_Props.data.data(), GL_DYNAMIC_STORAGE_BIT);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_ContextID);
}

GLuint OpenGLVertexBuffer::ContextID() const
{
	return m_ContextID;
}

int OpenGLVertexBuffer::Size() const
{
	return m_Size;
}

const VertexBufferLayout &OpenGLVertexBuffer::GetLayout() const
{
	return m_Props.layout;
}

void OpenGLVertexBuffer::BufferSubdata()
{
	// TODO:
	glNamedBufferSubData(m_ContextID, 0, 0, nullptr);
}
