#pragma once

#include <FrameBuffer.h>
#include <Sxg.h>

#include <glad/glad.h>

struct OpenGLFrameBuffer
{
	friend class OpenGLFrameBufferManager;

	GLuint id = 0;
	GLuint color = 0;
	GLuint depth = 0;
	FrameBufferProps props;

private:
	void GenerateAttachments();
};

class OpenGLFrameBufferManager : public FrameBufferManager
{
public:
	virtual FrameBufferHandle Create(const FrameBufferProps &) override;
	virtual void Destroy(FrameBufferHandle) override;

	virtual void Bind(FrameBufferHandle) const override;
	virtual void Unbind(FrameBufferHandle) const override;
	virtual int GetColorAttachmentID(FrameBufferHandle) const override;

	virtual void Resize(FrameBufferHandle, std::uint32_t width, std::uint32_t height) override;

// Native
public:
	const OpenGLFrameBuffer &Get(FrameBufferHandle) const;

private:
	mutable FrameBufferHandle m_SelectedFBO;
	ResourcePool<OpenGLFrameBuffer> m_Pool;
};