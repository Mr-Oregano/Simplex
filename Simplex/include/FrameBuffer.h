#pragma once

#include <Resource.h>
#include <Sxg.h>

struct FrameBufferProps
{
	int width;
	int height;
};

struct FrameBufferHandle : public ResourceHandle {};

class FrameBufferManager
{
public:
	virtual ~FrameBufferManager() = default;

	virtual FrameBufferHandle Create(const FrameBufferProps&) = 0;
	virtual void Destroy(FrameBufferHandle) = 0;

	virtual void Bind(FrameBufferHandle) const = 0;
	virtual void Unbind(FrameBufferHandle) const = 0;
	virtual int GetColorAttachmentID(FrameBufferHandle) const = 0;
	
	virtual void Resize(FrameBufferHandle, std::uint32_t width, std::uint32_t height) = 0;
};