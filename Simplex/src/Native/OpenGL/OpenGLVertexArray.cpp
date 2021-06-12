
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>

#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLUtility.h"

OpenGLVertexArray::OpenGLVertexArray(VertexArrayProps props)
    : m_Props(props)
{
    glCreateVertexArrays(1, &m_ContextID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_ContextID);
}

void OpenGLVertexArray::AddBuffer(Ref<VertexBuffer> vb)
{
    OpenGLVertexBuffer *glvb = static_cast<OpenGLVertexBuffer*>(vb.get());
    const VertexBufferLayout& layout = glvb->GetLayout();
    GLuint glvb_id = glvb->ContextID();

    glVertexArrayVertexBuffer(m_ContextID, m_BindCount, glvb_id, 0, layout.GetStride());

    int offset = 0;
    for (const auto &attribute : layout.GetAttributes())
    {
        int components = SXGTypeComponentCount(attribute.type);
        GLenum type = SXGTypeToGL(attribute.type);

        glVertexArrayAttribFormat(m_ContextID, m_AttributeCount, components, type, GL_FALSE, offset);
        glVertexArrayAttribBinding(m_ContextID, m_AttributeCount, m_BindCount);
        glEnableVertexArrayAttrib(m_ContextID, m_AttributeCount);

        offset += SXGTypeSize(attribute.type);
        ++m_AttributeCount;
    }

    ASSERT_WARN(layout.GetStride() != 0, "Vertex Buffer stride is zero.");
    ASSERT_WARN(glvb->Size() % layout.GetStride() == 0, "Vertex Buffer size is not a multiple of its stride.");
    
    int newVertexCount = glvb->Size() / layout.GetStride();

    ASSERT_WARN(m_VertexCount == 0 || newVertexCount == m_VertexCount, "Vertex Array Buffer sizes are inconsistent.");

    m_VertexCount = newVertexCount;
    ++m_BindCount;
}

GLuint OpenGLVertexArray::ContextID() const
{
    return m_ContextID;
}

SXG_TOPOLOGY OpenGLVertexArray::GetTopology()const
{
    return m_Props.topology;
}

int OpenGLVertexArray::GetVertexCount() const
{
    return m_VertexCount;
}
