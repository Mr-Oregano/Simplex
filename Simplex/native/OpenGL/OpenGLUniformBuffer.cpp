
// Precompiled Header
#include "sxpch.h"
//

#include "OpenGLUniformBuffer.h"

#include "OpenGLUtility.h"

#include <Simplex.h>

OpenGLUniformBuffer::OpenGLUniformBuffer(UniformBufferProps props)
{
	glCreateBuffers(1, &m_ContextID);
	glNamedBufferStorage(m_ContextID, props.size, props.data, SXGUsageToBufferStorageFlag(props.usage));
}

OpenGLUniformBuffer::~OpenGLUniformBuffer()
{
	LOG_INFO("Deleting resource: Uniform Buffer {0}", m_ContextID);
	glDeleteBuffers(1, &m_ContextID);
}

void OpenGLUniformBuffer::BufferSubdata()
{
	// TODO: Complete UniformBuffer sub data/map.
}

GLuint OpenGLUniformBuffer::ContextID() const
{
	return m_ContextID;
}
