#pragma once

#include <Resource.h>
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

struct UniformBufferHandle : public ResourceHandle {};

class UniformBufferManager
{
public:
	virtual ~UniformBufferManager() = default;

	virtual UniformBufferHandle Create(const UniformBufferProps &) = 0;
	virtual void Destroy(UniformBufferHandle) = 0;

	virtual void Bind(UniformBufferHandle, int slot, SXG::ShaderStageType stage) const = 0;
	virtual void BufferSubdata(UniformBufferHandle, std::uint32_t offset, std::uint32_t size, void *data) = 0;
};