#pragma once

#include <UniformBuffer.h>

#include <glad/glad.h>

class OpenGLUniformBuffer : public UniformBuffer
{
public:
	virtual void BufferSubdata() override;

public:
	OpenGLUniformBuffer(UniformBufferProps props);
	virtual ~OpenGLUniformBuffer();

	GLuint ContextID() const;

private:
	GLuint m_ContextID = 0;
};