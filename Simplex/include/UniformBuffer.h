#pragma once

#include <Sxg.h>

struct UniformBufferProps
{
	void *data;
	size_t size;
	SXG::BufferUsage usage = SXG::BufferUsage::STATIC;
};

class UniformBuffer
{
public:
	virtual ~UniformBuffer() = default;

	virtual void BufferSubdata() = 0;
};