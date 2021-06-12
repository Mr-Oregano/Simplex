#pragma once

enum class RendererAPI
{
	SXG_OPENGL,
	SXG_DX11
};

namespace SXG
{

enum Clear
{
	COLOR_BUFFER_BIT = 1,
	DEPTH_BUFFER_BIT = 2
};

enum class Topology
{
	TRIANGLES
};

enum class Types
{
	FLOAT,
	FLOAT2,
	FLOAT3,
	FLOAT4
};

enum class ShaderStageType
{
	VERTEX,
	FRAGMENT
};

inline int TypeComponentCount(Types type)
{
	switch (type)
	{
		case Types::FLOAT:  return 1;
		case Types::FLOAT2: return 2;
		case Types::FLOAT3: return 3;
		case Types::FLOAT4: return 4;
		default: return 0;
	}
}

inline int TypeSize(Types type)
{
	switch (type)
	{
		case Types::FLOAT:  return 1 * sizeof(float);
		case Types::FLOAT2: return 2 * sizeof(float);
		case Types::FLOAT3: return 3 * sizeof(float);
		case Types::FLOAT4: return 4 * sizeof(float);
		default: return 0;
	}
}

}

