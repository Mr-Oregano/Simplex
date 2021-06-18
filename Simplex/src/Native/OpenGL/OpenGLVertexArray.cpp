
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>

#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLUtility.h"

using namespace SXG;

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
    int bindingIndex = (int) m_Buffers.size();
    
    glVertexArrayVertexBuffer(m_ContextID, bindingIndex, glvb_id, 0, layout.GetStride());

    ASSERT_WARN(layout.GetStride() != 0, "Vertex Buffer stride is zero.");
    ASSERT_WARN(glvb->Size() % layout.GetStride() == 0, "Vertex Buffer size is not a multiple of its stride.");

    int newVertexCount = glvb->Size() / layout.GetStride();
    int instanceDataRate = 0;
    
    if (glvb->GetInputDataClass() == InputDataClass::PER_INSTANCE)
    {
        instanceDataRate = glvb->GetInstanceDataRate();
        newVertexCount = m_Props.vertexCount;
        
        ASSERT_WARN(newVertexCount != 0, "Can't determine the vertex count with per-instance data.");
        ASSERT_WARN(instanceDataRate > 0, "Per-instance data rate must be positive and non-zero!");
        glVertexArrayBindingDivisor(m_ContextID, bindingIndex, instanceDataRate);
    }

    int offset = 0;
    for (const auto &attribute : layout.GetAttributes())
    {
        int components = SXG::TypeComponentCount(attribute.type);
        GLenum type = SXGTypeToGL(attribute.type);
        int normalized = SXG::TypeIsNormalized(attribute.type) ? GL_TRUE : GL_FALSE;

        if (SXG::TypeIsInteger(attribute.type))
            glVertexArrayAttribIFormat(m_ContextID, m_AttributeCount, components, type, offset);
        else
            glVertexArrayAttribFormat(m_ContextID, m_AttributeCount, components, type, normalized, offset);
            
        glVertexArrayAttribBinding(m_ContextID, m_AttributeCount, bindingIndex);
        glEnableVertexArrayAttrib(m_ContextID, m_AttributeCount);

        offset += SXG::TypeSize(attribute.type);
        ++m_AttributeCount;
    }

    ASSERT_WARN(m_Props.vertexCount == 0 || newVertexCount == m_Props.vertexCount, "Vertex Array Buffer sizes are inconsistent.");

    m_Props.vertexCount = newVertexCount;
    m_Buffers.push_back(vb);
}

GLuint OpenGLVertexArray::ContextID() const
{
    return m_ContextID;
}

Topology OpenGLVertexArray::GetTopology()const
{
    return m_Props.topology;
}

int OpenGLVertexArray::GetVertexCount() const
{
    return m_Props.vertexCount;
}
