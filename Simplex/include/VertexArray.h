#pragma once

#include <Ref.h>

#include <Sxg.h>
#include <VertexBuffer.h>

struct VertexArrayProps
{
	SXG::Topology topology;
};

class VertexArray
{
public:
	virtual void AddBuffer(Ref<VertexBuffer> vb) = 0;

	virtual SXG::Topology GetTopology() const = 0;
	virtual int GetVertexCount() const = 0;
};