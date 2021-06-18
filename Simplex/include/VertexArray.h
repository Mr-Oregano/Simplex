#pragma once

#include <Ref.h>

#include <Sxg.h>
#include <VertexBuffer.h>

struct VertexArrayProps
{
	SXG::Topology topology;
	int vertexCount = 0; // If 0, will be calculated.
};

class VertexArray
{
public:
	virtual void AddBuffer(Ref<VertexBuffer> vb) = 0;

	virtual SXG::Topology GetTopology() const = 0;
	virtual int GetVertexCount() const = 0;
};