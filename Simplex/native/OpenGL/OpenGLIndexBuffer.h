#pragma once

#include <Sxg.h>

#include <IndexBuffer.h>

#include <glad/glad.h>

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	virtual void BufferSubdata() override;

// Native
public:
	OpenGLIndexBuffer(IndexBufferProps props);
	virtual ~OpenGLIndexBuffer();
	
	GLuint ContextID() const;
	unsigned int GetVertexCount() const;
	SXG::Types GetType() const;

private:
	GLuint m_ContextID = 0;
	
	unsigned int m_Count = 0;
	SXG::Types m_Type;

};