
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>

#include "OpenGLIndexBuffer.h"

IndexBufferHandle OpenGLIndexBufferManager::Create(const IndexBufferProps &props)
{
    ASSERT_CRITICAL(SXG::TypeIsInteger(props.indexType), "Index buffer should consist of integral type.");

    OpenGLIndexBuffer ib{};

    ib.vertexCount = (unsigned int) (props.size / SXG::TypeSize(props.indexType));
    ib.indexType = props.indexType;

    glCreateBuffers(1, &ib.id);
    glNamedBufferStorage(ib.id, props.size, props.data, GL_DYNAMIC_STORAGE_BIT);

    return static_cast<IndexBufferHandle>(m_Pool.Emplace(std::move(ib)));
}

void OpenGLIndexBufferManager::Destroy(IndexBufferHandle handle)
{
    OpenGLIndexBuffer &ib = m_Pool.Get(handle);

    LOG_INFO("Deleting resource: Index Buffer {0}", ib.id);
    glDeleteBuffers(1, &ib.id);
    
    m_Pool.Release(handle);
}

void OpenGLIndexBufferManager::BufferSubdata(IndexBufferHandle handle, std::uint32_t offset, std::uint32_t size, const void *data)
{
    OpenGLIndexBuffer &ib = m_Pool.Get(handle);

    glNamedBufferSubData(ib.id, offset, size, data);
}

const OpenGLIndexBuffer &OpenGLIndexBufferManager::Get(IndexBufferHandle handle) const
{
    return m_Pool.GetConst(handle);
}
