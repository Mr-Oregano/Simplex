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
	SXG::InputDataClass GetInputDataClass() const;
	int GetInstanceDataRate() const;

	int Size() const;
	const VertexBufferLayout &GetLayout() const;

private:
	VertexBufferLayout m_Layout;
	SXG::InputDataClass m_InputDataClass;
	int m_InstanceDataRate;

	GLuint m_ContextID = 0;

	int m_Size = 0;
//
};

