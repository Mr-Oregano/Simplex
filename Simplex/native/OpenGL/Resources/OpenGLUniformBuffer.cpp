
// Precompiled Header
#include "sxpch.h"
//

#include "OpenGLUniformBuffer.h"

#include "../OpenGLUtility.h"

#include <Simplex.h>

UniformBufferHandle OpenGLUniformBufferManager::Create(const UniformBufferProps &props)
{
	OpenGLUniformBuffer buffer{};

	glCreateBuffers(1, &buffer.id);
	glNamedBufferStorage(buffer.id, props.size, props.data, SXGUsageToBufferStorageFlag(props.usage));

	return static_cast<UniformBufferHandle>(m_Pool.Emplace(std::move(buffer)));
}

void OpenGLUniformBufferManager::Destroy(UniformBufferHandle handle)
{
	OpenGLUniformBuffer &ub = m_Pool.Get(handle);

	LOG_INFO("Deleting resource: Uniform Buffer {0}", ub.id);
	glDeleteBuffers(1, &ub.id);

	m_Pool.Release(handle);
}

void OpenGLUniformBufferManager::Bind(UniformBufferHandle handle, int slot, SXG::ShaderStageType stage) const
{
	ASSERT_CRITICAL(-1 < slot && slot < m_MaxUniformBufferBindings, "UBO slot must be between [0, {0}] for this hardware!", m_MaxUniformBufferBindings - 1);

	const OpenGLUniformBuffer &glub = m_Pool.GetConst(handle);

	// NOTE: The passed shader stage enum is ignored for OpenGL implementations. This is for use with DX11.
	
	glUniformBlockBinding(glub.id, slot, slot);
	glBindBufferBase(GL_UNIFORM_BUFFER, slot, glub.id);
}

void OpenGLUniformBufferManager::BufferSubdata(UniformBufferHandle handle, std::uint32_t offset, std::uint32_t size, void *data)
{
	OpenGLUniformBuffer &ub = m_Pool.Get(handle);

	glNamedBufferSubData(ub.id, offset, size, data);
}

OpenGLUniformBufferManager::OpenGLUniformBufferManager()
{
	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &m_MaxUniformBufferBindings);
}

const OpenGLUniformBuffer &OpenGLUniformBufferManager::Get(UniformBufferHandle handle) const
{
	return m_Pool.GetConst(handle);
}
