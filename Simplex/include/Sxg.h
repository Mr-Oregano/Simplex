#pragma once

enum class RendererAPI
{
	SXG_OPENGL,
	SXG_DX11
};

enum SXG
{
	COLOR_BUFFER_BIT = 1,
	DEPTH_BUFFER_BIT = 2
};

enum class SXG_TOPOLOGY
{
	TRIANGLES
};

enum class SXG_TYPES
{
	FLOAT,
	FLOAT2,
	FLOAT3,
	FLOAT4
};

inline int SXGTypeComponentCount(SXG_TYPES type)
{
	switch (type)
	{
		case SXG_TYPES::FLOAT:  return 1;
		case SXG_TYPES::FLOAT2: return 2;
		case SXG_TYPES::FLOAT3: return 3;
		case SXG_TYPES::FLOAT4: return 4;
		default: return 0;
	}
}

inline int SXGTypeSize(SXG_TYPES type)
{
	switch (type)
	{
		case SXG_TYPES::FLOAT:  return 1 * sizeof(float);
		case SXG_TYPES::FLOAT2: return 2 * sizeof(float);
		case SXG_TYPES::FLOAT3: return 3 * sizeof(float);
		case SXG_TYPES::FLOAT4: return 4 * sizeof(float);
		default: return 0;
	}
}