#pragma once

#include <string>

#include <initializer_list>
#include <vector>

#include <Resource.h>
#include <Sxg.h>

struct VertexAttribute
{
	std::string name;
	SXG::Types type;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() = default;
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
	void *data;
	size_t size;
	VertexBufferLayout *layout;
	SXG::InputDataClass inputDataClass = SXG::InputDataClass::PER_VERTEX;
	SXG::BufferUsage usage = SXG::BufferUsage::STATIC;
	int instanceDataRate = 0;
};

struct VertexBufferHandle : public ResourceHandle {};

class VertexBufferManager
{
public:
	virtual ~VertexBufferManager() = default;

	virtual VertexBufferHandle Create(const VertexBufferProps&) = 0;
	virtual void Destroy(VertexBufferHandle) = 0;

	virtual void BufferSubData(VertexBufferHandle, std::uint32_t offset, std::uint32_t size, void *data) = 0;
};