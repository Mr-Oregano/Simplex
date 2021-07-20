
// Precompiled Header
#include "sxpch.h"
//

#include "OpenGLVertexBuffer.h"

#include "OpenGLUtility.h"

#include <Simplex.h>

OpenGLVertexBuffer::OpenGLVertexBuffer(VertexBufferProps props)
	: m_Layout(*props.layout)
{
	m_Size = (int) (props.size);
	m_InputDataClass = props.inputDataClass;
	m_InstanceDataRate = props.instanceDataRate;

	glCreateBuffers(1, &m_ContextID);
	glNamedBufferStorage(m_ContextID, m_Size, props.data, SXGUsageToBufferStorageFlag(props.usage));
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	LOG_INFO("Deleting resource: Vertex Buffer {0}", m_ContextID);
	glDeleteBuffers(1, &m_ContextID);
}

GLuint OpenGLVertexBuffer::ContextID() const
{
	return m_ContextID;
}

SXG::InputDataClass OpenGLVertexBuffer::GetInputDataClass() const
{
	return m_InputDataClass;
}

int OpenGLVertexBuffer::GetInstanceDataRate() const
{
	return m_InstanceDataRate;
}

int OpenGLVertexBuffer::Size() const
{
	return m_Size;
}

const VertexBufferLayout &OpenGLVertexBuffer::GetLayout() const
{
	return m_Layout;
}

void OpenGLVertexBuffer::BufferSubdata()
{
	// TODO: Complete VertexBuffer sub data/map.
}
