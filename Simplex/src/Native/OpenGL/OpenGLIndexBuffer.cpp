
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>

#include "OpenGLIndexBuffer.h"

OpenGLIndexBuffer::OpenGLIndexBuffer(IndexBufferProps props)
{
    if (!SXG::TypeIsInteger(props.indexType))
        LOG_ERROR("Index buffer should consist of integral type.");

    m_Count = (unsigned int) (props.size / SXG::TypeSize(props.indexType));
    m_Type = props.indexType;

    glCreateBuffers(1, &m_ContextID);
    glNamedBufferStorage(m_ContextID, props.size, props.data, GL_DYNAMIC_STORAGE_BIT);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    LOG_INFO("Deleting resource: Index Buffer {0}", m_ContextID);
    glDeleteBuffers(1, &m_ContextID);
}

GLuint OpenGLIndexBuffer::ContextID() const
{
    return m_ContextID;
}

unsigned int OpenGLIndexBuffer::GetVertexCount() const
{
    return m_Count;
}

SXG::Types OpenGLIndexBuffer::GetType() const
{
    return m_Type;
}

void OpenGLIndexBuffer::BufferSubdata()
{
    // TODO: Complete IndexBuffer sub data/map.
}