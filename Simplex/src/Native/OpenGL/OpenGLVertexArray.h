#pragma once

#include <VertexArray.h>
#include <VertexBuffer.h>

#include <glad/glad.h>

#include <vector>

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
	std::vector<Ref<VertexBuffer>> m_Buffers;

	VertexArrayProps m_Props;
	GLuint m_ContextID = 0;

	int m_AttributeCount = 0;
//
};