
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>

#include "OpenGLVertexArray.h"

#include "../OpenGLUtility.h"

using namespace SXG;

OpenGLVertexArrayManager::OpenGLVertexArrayManager(OpenGLVertexBufferManager *vb_manager, OpenGLIndexBufferManager *ib_manager)
    : m_VertexBufferManager(vb_manager), m_IndexBufferManager(ib_manager)
{}

VertexArrayHandle OpenGLVertexArrayManager::Create(const VertexArrayProps &props)
{
    OpenGLVertexArray va{};
    va.props = props;

    glCreateVertexArrays(1, &va.id);
    return static_cast<VertexArrayHandle>(m_Pool.Emplace(std::move(va)));
}

void OpenGLVertexArrayManager::Destroy(VertexArrayHandle handle)
{
    OpenGLVertexArray &va = m_Pool.Get(handle);

    LOG_INFO("Deleting resource: Vertex Array {0}", va.id);
    glDeleteVertexArrays(1, &va.id);

    m_Pool.Release(handle);
}

void OpenGLVertexArrayManager::Bind(VertexArrayHandle handle) const
{
    m_Selected = handle;

    glBindVertexArray(m_Pool.GetConst(handle).id);
}

const OpenGLVertexArray &OpenGLVertexArrayManager::Get(VertexArrayHandle handle) const
{
    return m_Pool.GetConst(handle);
}

const VertexArrayHandle OpenGLVertexArrayManager::GetSelected() const
{
    return m_Selected;
}

void OpenGLVertexArrayManager::AddBuffer(VertexArrayHandle va_handle, VertexBufferHandle vb_handle)
{
    OpenGLVertexArray &va = m_Pool.Get(va_handle);
    const OpenGLVertexBuffer &vb = m_VertexBufferManager->Get(vb_handle);

    int bindingIndex = (int) va.buffers.size();
    
    glVertexArrayVertexBuffer(va.id, bindingIndex, vb.id, 0, vb.layout.GetStride());

    ASSERT_WARN(vb.layout.GetStride() != 0, "Vertex Buffer stride is zero.");
    ASSERT_WARN(vb.size % vb.layout.GetStride() == 0, "Vertex Buffer size is not a multiple of its stride.");

    int newVertexCount = vb.size / vb.layout.GetStride();
    int instanceDataRate = 0;
    
    if (vb.inputClass == InputDataClass::PER_INSTANCE)
    {
        instanceDataRate = vb.instanceDataRate;
        newVertexCount = va.props.vertexCount;
        
        ASSERT_WARN(newVertexCount != 0, "Can't determine the vertex count with per-instance data.");
        ASSERT_WARN(instanceDataRate > 0, "Per-instance data rate must be positive and non-zero!");
        glVertexArrayBindingDivisor(va.id, bindingIndex, instanceDataRate);
    }

    int offset = 0;
    for (const auto &attribute : vb.layout.GetAttributes())
    {
        int components = SXG::TypeComponentCount(attribute.type);
        GLenum type = SXGTypeToGL(attribute.type);
        int normalized = SXG::TypeIsNormalized(attribute.type) ? GL_TRUE : GL_FALSE;

        if (SXG::TypeIsInteger(attribute.type))
            glVertexArrayAttribIFormat(va.id, va.attributeCount, components, type, offset);
        else
            glVertexArrayAttribFormat(va.id, va.attributeCount, components, type, normalized, offset);
            
        glVertexArrayAttribBinding(va.id, va.attributeCount, bindingIndex);
        glEnableVertexArrayAttrib(va.id, va.attributeCount);

        offset += SXG::TypeSize(attribute.type);
        ++va.attributeCount;
    }

    ASSERT_WARN(va.props.vertexCount == 0 || newVertexCount == va.props.vertexCount, "Vertex Array Buffer sizes are inconsistent.");

    va.props.vertexCount = newVertexCount;
    va.buffers.push_back(vb_handle);
}

void OpenGLVertexArrayManager::SetIndexBuffer(VertexArrayHandle va_handle, IndexBufferHandle ib_handle)
{
    OpenGLVertexArray &va = m_Pool.Get(va_handle);
    va.indexBuffer = ib_handle;

    if (va.HasIndexBuffer())
    {
        const OpenGLIndexBuffer &ib = m_IndexBufferManager->Get(ib_handle);
        glVertexArrayElementBuffer(va.id, ib.id);
        return;
    }

    glVertexArrayElementBuffer(va.id, 0);
}

int OpenGLVertexArrayManager::GetVertexCount(VertexArrayHandle handle) const
{
    const OpenGLVertexArray &va = m_Pool.GetConst(handle);

    if (va.HasIndexBuffer())
    {
        const OpenGLIndexBuffer &ib = m_IndexBufferManager->Get(va.indexBuffer);
        return ib.vertexCount;
    }

    return va.props.vertexCount;
}
