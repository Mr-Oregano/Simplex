#pragma once

#include <Sxg.h>

#include <glad/glad.h>

inline GLenum SXGTypeToGL(SXG_TYPES type)
{
	switch (type)
	{
		case SXG_TYPES::FLOAT:
		case SXG_TYPES::FLOAT2: 
		case SXG_TYPES::FLOAT3:
		case SXG_TYPES::FLOAT4: return GL_FLOAT;
		default: return 0;
	}
}

inline GLenum SXGTopologyToGL(SXG_TOPOLOGY topology)
{
	switch (topology)
	{
		case SXG_TOPOLOGY::TRIANGLES: return GL_TRIANGLES;
		default: return 0;
	}
}