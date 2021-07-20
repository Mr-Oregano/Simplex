#pragma once

#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>

#include <glad/glad.h>

#include <vector>

struct VertexArrayDrawInfo
{
	SXG::Topology topology;
	SXG::Types indexType;
};

class OpenGLVertexArray : public VertexArray
{
public:
	virtual void AddBuffer(Ref<VertexBuffer> vb) override;
	virtual void SetIndexBuffer(Ref<IndexBuffer> ib) override;

	virtual int GetVertexCount() const override;

// Native
public:
	OpenGLVertexArray(VertexArrayProps props);
	virtual ~OpenGLVertexArray();
	
	GLuint ContextID() const;
	VertexArrayDrawInfo GetDrawInfo() const;
	bool HasIndexBuffer() const;

private:
	std::vector<Ref<VertexBuffer>> m_Buffers;
	Ref<IndexBuffer> m_IndexBuffer;

	VertexArrayProps m_Props;
	GLuint m_ContextID = 0;

	int m_AttributeCount = 0;
//
};