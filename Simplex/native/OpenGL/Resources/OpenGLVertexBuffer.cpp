
// Precompiled Header
#include "sxpch.h"
//

#include "OpenGLVertexBuffer.h"

#include "../OpenGLUtility.h"

#include <Simplex.h>

VertexBufferHandle OpenGLVertexBufferManager::Create(const VertexBufferProps &props)
{
	OpenGLVertexBuffer data{};
	data.size = (int)(props.size);
	data.inputClass = props.inputDataClass;
	data.instanceDataRate = props.instanceDataRate;
	data.layout = *props.layout;

	glCreateBuffers(1, &data.id);
	glNamedBufferStorage(data.id, data.size, props.data, SXGUsageToBufferStorageFlag(props.usage));

	return static_cast<VertexBufferHandle>(m_Pool.Emplace(std::move(data)));
}

void OpenGLVertexBufferManager::Destroy(VertexBufferHandle handle)
{
	OpenGLVertexBuffer &vb = m_Pool.Get(handle);

	LOG_INFO("Deleting resource: Vertex Buffer {0}", vb.id);
	glDeleteBuffers(1, &vb.id);

	m_Pool.Release(handle);
}

void OpenGLVertexBufferManager::BufferSubData(VertexBufferHandle handle, std::uint32_t offset, std::uint32_t size, void *data)
{
	OpenGLVertexBuffer &vb = m_Pool.Get(handle);

	glNamedBufferSubData(vb.id, offset, size, data);
}

const OpenGLVertexBuffer &OpenGLVertexBufferManager::Get(VertexBufferHandle handle) const
{
	return m_Pool.GetConst(handle);
}
