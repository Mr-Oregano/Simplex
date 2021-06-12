#pragma once

#include <VertexBuffer.h>

#include <glad/glad.h>

class OpenGLVertexBuffer : public VertexBuffer
{
public:
	virtual void BufferSubdata() override;

// Native
public:
	OpenGLVertexBuffer(VertexBufferProps props);
	virtual ~OpenGLVertexBuffer();
	
	GLuint ContextID() const;
	int Size() const;
	const VertexBufferLayout &GetLayout() const;

private:
	VertexBufferProps m_Props;
	GLuint m_ContextID;

	int m_Size = 0;
//
};

