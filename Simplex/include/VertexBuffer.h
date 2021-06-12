#pragma once

#include <string>

#include <initializer_list>
#include <vector>

#include <Sxg.h>

struct VertexAttribute
{
	SXG_TYPES type;
	std::string name;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout(std::initializer_list<VertexAttribute> attributes);
	
	int GetStride() const;
	const std::vector<VertexAttribute> &GetAttributes() const;

private:
	int CalcStride();

private:
	std::vector<VertexAttribute> m_Attributes;
	int m_Stride;
};

struct VertexBufferProps
{
	std::vector<float> &data;
	VertexBufferLayout layout;
};

class VertexBuffer
{
public:
	virtual void BufferSubdata() = 0;
};