#pragma once

#include <Sxg.h>

#include <glad/glad.h>

inline GLenum SXGTypeToGL(SXG::Types type)
{
	using namespace SXG;

	switch (type)
	{
		case Types::INT_NORM:
		case Types::INT_NORM2:
		case Types::INT_NORM3:
		case Types::INT_NORM4:
		case Types::FLOAT:
		case Types::FLOAT2: 
		case Types::FLOAT3:
		case Types::FLOAT4: return GL_FLOAT;

		case Types::INT:
		case Types::INT2:
		case Types::INT3:
		case Types::INT4: return GL_INT;
	}

	return 0;
}

inline GLenum SXGTopologyToGL(SXG::Topology topology)
{
	using namespace SXG;

	switch (topology)
	{
		case Topology::TRIANGLES: return GL_TRIANGLES;
	}

	return 0;
}

inline GLenum SXGShaderStageToGL(SXG::ShaderStageType type)
{
	using namespace SXG;

	switch (type)
	{
		case ShaderStageType::VERTEX: return GL_VERTEX_SHADER;
		case ShaderStageType::FRAGMENT: return GL_FRAGMENT_SHADER;
	}

	return 0;
}