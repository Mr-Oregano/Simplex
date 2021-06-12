#pragma once

#include <Ref.h>

#include <Sxg.h>
#include <VertexBuffer.h>

struct VertexArrayProps
{
	SXG_TOPOLOGY topology;
};

class VertexArray
{
public:
	virtual void AddBuffer(Ref<VertexBuffer> vb) = 0;

	virtual SXG_TOPOLOGY GetTopology() const = 0;
	virtual int GetVertexCount() const = 0;
};