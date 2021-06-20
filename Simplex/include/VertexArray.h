#pragma once

#include <Ref.h>

#include <Sxg.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>

struct VertexArrayProps
{
	SXG::Topology topology;
	int vertexCount = 0; // If 0, will be calculated.
};

class VertexArray
{
public:
	virtual ~VertexArray() = default;

	virtual void AddBuffer(Ref<VertexBuffer> vb) = 0;
	virtual void SetIndexBuffer(Ref<IndexBuffer> ib) = 0;

	virtual int GetVertexCount() const = 0;
};