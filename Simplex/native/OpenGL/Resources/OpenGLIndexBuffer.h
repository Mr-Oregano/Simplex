#pragma once

#include <IndexBuffer.h>
#include <Sxg.h>

#include <glad/glad.h>

struct OpenGLIndexBuffer
{
	GLuint id = 0;
	unsigned int vertexCount = 0;
	SXG::Types indexType;
};

class OpenGLIndexBufferManager : public IndexBufferManager
{
public:
	virtual IndexBufferHandle Create(const IndexBufferProps &) override;
	virtual void Destroy(IndexBufferHandle) override;

	virtual void BufferSubdata(IndexBufferHandle, std::uint32_t offset, std::uint32_t size, const void *data) override;

// Native
public:
	const OpenGLIndexBuffer& Get(IndexBufferHandle) const;

private:
	ResourcePool<OpenGLIndexBuffer> m_Pool;
};