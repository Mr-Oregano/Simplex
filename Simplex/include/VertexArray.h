#pragma once

#include <Resource.h>
#include <Ref.h>

#include <Sxg.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>

struct VertexArrayProps
{
	SXG::Topology topology;
	int vertexCount = 0; // If 0, will be calculated.
};

struct VertexArrayHandle : public ResourceHandle {};

class VertexArrayManager
{
public:
	virtual ~VertexArrayManager() = default;

	virtual VertexArrayHandle Create(const VertexArrayProps&) = 0;
	virtual void Destroy(VertexArrayHandle) = 0;

	virtual void Bind(VertexArrayHandle) const = 0;

	virtual void AddBuffer(VertexArrayHandle, VertexBufferHandle) = 0;
	virtual void SetIndexBuffer(VertexArrayHandle, IndexBufferHandle) = 0;
	virtual int GetVertexCount(VertexArrayHandle) const = 0;
};