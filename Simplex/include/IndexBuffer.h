#pragma once

#include <Sxg.h>

struct IndexBufferProps
{
	void *data;
	size_t size;
	SXG::Types indexType;
};

class IndexBuffer
{
public:
	virtual ~IndexBuffer() = default;

	virtual void BufferSubdata() = 0;
};