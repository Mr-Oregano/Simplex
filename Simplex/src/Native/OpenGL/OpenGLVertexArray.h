#pragma once

#include <VertexArray.h>
#include <VertexBuffer.h>

#include <glad/glad.h>

class OpenGLVertexArray : public VertexArray
{
public:
	virtual void AddBuffer(Ref<VertexBuffer> vb) override;

	virtual SXG::Topology GetTopology() const override;
	virtual int GetVertexCount() const override;

// Native
public:
	OpenGLVertexArray(VertexArrayProps props);
	virtual ~OpenGLVertexArray();
	
	GLuint ContextID() const;

private:
	VertexArrayProps m_Props;
	GLuint m_ContextID = 0;

	int m_AttributeCount = 0;
	int m_BindCount = 0;
	int m_VertexCount = 0;
//
};