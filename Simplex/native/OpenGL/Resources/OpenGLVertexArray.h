#pragma once

#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>

#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

#include <vector>

struct OpenGLVertexArray
{
	VertexArrayProps props;
	GLuint id = 0;
	
	std::vector<VertexBufferHandle> buffers;
	IndexBufferHandle indexBuffer;
	int attributeCount = 0;

	bool HasIndexBuffer() const { return indexBuffer; }
};

class OpenGLVertexArrayManager : public VertexArrayManager
{
public:
	OpenGLVertexArrayManager(OpenGLVertexBufferManager *vb_manager, OpenGLIndexBufferManager *ib_manager);

	virtual VertexArrayHandle Create(const VertexArrayProps &) override;
	virtual void Destroy(VertexArrayHandle) override;

	virtual void Bind(VertexArrayHandle) const override;

	virtual void AddBuffer(VertexArrayHandle, VertexBufferHandle) override;
	virtual void SetIndexBuffer(VertexArrayHandle, IndexBufferHandle) override;
	virtual int GetVertexCount(VertexArrayHandle) const override;

// Native
public:
	const OpenGLVertexArray &Get(VertexArrayHandle) const;
	const VertexArrayHandle GetSelected() const;

private:
	OpenGLVertexBufferManager* m_VertexBufferManager;
	OpenGLIndexBufferManager* m_IndexBufferManager;

	ResourcePool<OpenGLVertexArray> m_Pool;
	mutable VertexArrayHandle m_Selected;
};