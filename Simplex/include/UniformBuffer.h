#pragma once

#include <Sxg.h>

struct UniformBufferProps
{
	// NOTE: For now, users MUST comply with OpenGL's std140
	//		 layout for uniform buffers. 
	//
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