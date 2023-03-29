
// Precompiled Header
#include "sxpch.h"
//

#include "OpenGLFrameBuffer.h"

void OpenGLFrameBuffer::GenerateAttachments()
{
	if (id != 0)
	{
		glDeleteTextures(1, &color);
		glDeleteTextures(1, &depth);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, id);

	glCreateTextures(GL_TEXTURE_2D, 1, &color);
	glBindTexture(GL_TEXTURE_2D, color);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, props.width, props.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &depth);
	glBindTexture(GL_TEXTURE_2D, depth);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, props.width, props.height);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth, 0);

	ASSERT_ERROR(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer has not been completed!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBufferHandle OpenGLFrameBufferManager::Create(const FrameBufferProps &props)
{
    ASSERT_CRITICAL(props.width > 0 && props.height > 0, "Framebuffer width and height must be positive");

    OpenGLFrameBuffer fb{};
	fb.props = props;
    glCreateFramebuffers(1, &fb.id);

    fb.GenerateAttachments();

    return static_cast<FrameBufferHandle>(m_Pool.Emplace(std::move(fb)));
}

void OpenGLFrameBufferManager::Destroy(FrameBufferHandle handle)
{
	OpenGLFrameBuffer &fb = m_Pool.Get(handle);
	LOG_INFO("Deleting resource: Frame Buffer {0}", fb.id);
	
	glDeleteFramebuffers(1, &fb.id);
	glDeleteTextures(1, &fb.color);
	glDeleteTextures(1, &fb.depth);
	fb.id = 0;

	m_Pool.Release(handle);
}

void OpenGLFrameBufferManager::Bind(FrameBufferHandle handle) const
{
	const OpenGLFrameBuffer &fb = m_Pool.GetConst(handle);

	glBindFramebuffer(GL_FRAMEBUFFER, fb.id);
	glViewport(0, 0, fb.props.width, fb.props.height);

	m_SelectedFBO = handle;
}

void OpenGLFrameBufferManager::Unbind(FrameBufferHandle handle) const
{
	ASSERT_ERROR(m_SelectedFBO == handle, "Trying to unbind a frame buffer that has not been selected!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_SelectedFBO = FrameBufferHandle{};
}

int OpenGLFrameBufferManager::GetColorAttachmentID(FrameBufferHandle handle) const
{
	const OpenGLFrameBuffer &fb = m_Pool.GetConst(handle);

	return (int) fb.color;
}

void OpenGLFrameBufferManager::Resize(FrameBufferHandle handle, std::uint32_t width, std::uint32_t height)
{
	OpenGLFrameBuffer &fb = m_Pool.Get(handle);
	
	glViewport(0, 0, fb.props.width, fb.props.height);
	fb.props.width = width;
	fb.props.height = height;

	fb.GenerateAttachments();
	
	glBindFramebuffer(GL_FRAMEBUFFER, fb.id);
	m_SelectedFBO = handle;
}

const OpenGLFrameBuffer &OpenGLFrameBufferManager::Get(FrameBufferHandle handle) const
{
	return m_Pool.GetConst(handle);
}
