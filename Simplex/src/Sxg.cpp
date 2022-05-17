
// Precompiled Header
#include "sxpch.h"
//

#include <Sxg.h>

#include <Simplex.h>

namespace SXG
{

int TypeComponentCount(Types type)
{
	switch (type)
	{
	case Types::INT_NORM:
	case Types::INT:
	case Types::UINT:
	case Types::FLOAT:  return 1;

	case Types::INT_NORM2:
	case Types::INT2:
	case Types::UINT2:
	case Types::FLOAT2: return 2;

	case Types::INT_NORM3:
	case Types::INT3:
	case Types::UINT3:
	case Types::FLOAT3: return 3;

	case Types::INT_NORM4:
	case Types::INT4:
	case Types::UINT4:
	case Types::FLOAT4: return 4;
	}

	LOG_WARN("Unknown component count of type");
	return 0;
}

int TypeSize(Types type)
{
	switch (type)
	{
	case Types::UINT: return 1 * sizeof(unsigned int);
	case Types::INT_NORM:
	case Types::INT: return 1 * sizeof(int);
	case Types::FLOAT:  return 1 * sizeof(float);
	
	case Types::UINT2: return 2 * sizeof(unsigned int);
	case Types::INT_NORM2:
	case Types::INT2: return 2 * sizeof(int);
	case Types::FLOAT2: return 2 * sizeof(float);
	
	case Types::UINT3: return 3 * sizeof(unsigned int);
	case Types::INT_NORM3:
	case Types::INT3: return 3 * sizeof(int);
	case Types::FLOAT3: return 3 * sizeof(float);
	
	case Types::UINT4: return 4 * sizeof(unsigned int);
	case Types::INT_NORM4:
	case Types::INT4: return 4 * sizeof(int);
	case Types::FLOAT4: return 4 * sizeof(float);
	}

	LOG_WARN("Unknown size of type");
	return 0;
}

bool TypeIsNormalized(Types type)
{
	switch (type)
	{
	case Types::INT_NORM:
	case Types::INT_NORM2:
	case Types::INT_NORM3:
	case Types::INT_NORM4: return true;
	}

	return false;
}

bool TypeIsInteger(Types type)
{
	switch (type)
	{
	case Types::UINT:
	case Types::UINT2:
	case Types::UINT3:
	case Types::UINT4:
	case Types::INT:
	case Types::INT2:
	case Types::INT3:
	case Types::INT4: return true;
	}

	return false;
}

bool TypeIsFloat(Types type)
{
	return !TypeIsInteger(type) && type != Types::NONE;
}

APIVersion MakeOpenGLVersion(int major, int minor)
{
	return ((major & 0xff) << 8) | (minor & 0xff);
}

}