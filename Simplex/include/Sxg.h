#pragma once

namespace SXG
{

typedef int APIVersion;

enum class API
{
	OPENGL,
	DIRECTX
};

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
	NONE,

	FLOAT,
	FLOAT2,
	FLOAT3,
	FLOAT4,

	INT_NORM,
	INT_NORM2,
	INT_NORM3,
	INT_NORM4,

	INT,
	INT2,
	INT3,
	INT4,

	UINT,
	UINT2,
	UINT3,
	UINT4
};

enum class InputDataClass
{
	PER_INSTANCE,
	PER_VERTEX
};

enum class BufferUsage
{
	STATIC,
	DYNAMIC
};

enum class ShaderStageType
{
	VERTEX,
	FRAGMENT
};

enum class TexFilter
{
	Nearest = 0,
	Linear
};

enum class TexWrapMode
{
	ClampToEdge = 0,
	ClampToBorder,
	Repeat,
	Mirror
};

enum class TexMipmapMode
{
	None = 0,
	Nearest,
	Linear,
	Anisotropic
};

int TypeComponentCount(Types type);

int TypeSize(Types type);

bool TypeIsNormalized(Types type);

bool TypeIsInteger(Types type);

bool TypeIsFloat(Types type);

APIVersion MakeOpenGLVersion(int major, int minor);

}

