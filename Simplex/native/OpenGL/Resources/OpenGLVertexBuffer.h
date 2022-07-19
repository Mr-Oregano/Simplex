#pragma once

#include <VertexBuffer.h>

#include <glad/glad.h>

struct OpenGLVertexBuffer
{
	VertexBufferLayout layout;
	SXG::InputDataClass inputClass;
	int instanceDataRate;
	GLuint id = 0;
	int size = 0;
};

class OpenGLVertexBufferManager : public VertexBufferManager
{
public:
	virtual VertexBufferHandle Create(const VertexBufferProps &) override;
	virtual void Destroy(VertexBufferHandle) override;
	virtual void BufferSubData(VertexBufferHandle, std::uint32_t offset, std::uint32_t size, void *data) override;

// Native
public:
	const OpenGLVertexBuffer& Get(VertexBufferHandle) const;

public:
	ResourcePool<OpenGLVertexBuffer> m_Pool;
};

