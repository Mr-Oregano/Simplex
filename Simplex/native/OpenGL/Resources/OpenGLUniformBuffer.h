#pragma once

#include <UniformBuffer.h>

#include <glad/glad.h>

struct OpenGLUniformBuffer
{
	GLuint id = 0;
};

class OpenGLUniformBufferManager : public UniformBufferManager
{
public:
	virtual UniformBufferHandle Create(const UniformBufferProps &) override;
	virtual void Destroy(UniformBufferHandle) override;

	virtual void Bind(UniformBufferHandle, int slot, SXG::ShaderStageType stage) const override;
	virtual void BufferSubdata(UniformBufferHandle, std::uint32_t offset, std::uint32_t size, void *data) override;

// Native:
public:
	OpenGLUniformBufferManager();
	const OpenGLUniformBuffer &Get(UniformBufferHandle) const;

private:
	ResourcePool<OpenGLUniformBuffer> m_Pool;
	GLint m_MaxUniformBufferBindings;
};