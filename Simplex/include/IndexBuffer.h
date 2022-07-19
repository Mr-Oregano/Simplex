#pragma once

#include <Resource.h>
#include <Sxg.h>

struct IndexBufferProps
{
	void *data;
	size_t size;
	SXG::Types indexType;
};

struct IndexBufferHandle : public ResourceHandle {};

class IndexBufferManager
{
public:
	virtual ~IndexBufferManager() = default;

	virtual IndexBufferHandle Create(const IndexBufferProps&) = 0;
	virtual void Destroy(IndexBufferHandle) = 0;
	
	virtual void BufferSubdata(IndexBufferHandle, std::uint32_t offset, std::uint32_t size, const void *data) = 0;
};