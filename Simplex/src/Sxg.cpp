
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
	case Types::FLOAT:  return 1;

	case Types::INT_NORM2:
	case Types::INT2:
	case Types::FLOAT2: return 2;

	case Types::INT_NORM3:
	case Types::INT3:
	case Types::FLOAT3: return 3;

	case Types::INT_NORM4:
	case Types::INT4:
	case Types::FLOAT4: return 4;
	}

	LOG_WARN("Unknown component count of type {0}", type);
	return 0;
}

int TypeSize(Types type)
{
	switch (type)
	{
	case Types::INT_NORM:
	case Types::INT: return 1 * sizeof(int);
	case Types::FLOAT:  return 1 * sizeof(float);
	
	case Types::INT_NORM2:
	case Types::INT2: return 2 * sizeof(int);
	case Types::FLOAT2: return 2 * sizeof(float);
	
	case Types::INT_NORM3:
	case Types::INT3: return 3 * sizeof(int);
	case Types::FLOAT3: return 3 * sizeof(float);
	
	case Types::INT_NORM4:
	case Types::INT4: return 4 * sizeof(int);
	case Types::FLOAT4: return 4 * sizeof(float);
	}

	LOG_WARN("Unknown size of type {0}", type);
	return 0;
}

bool TypeIsNormalized(SXG::Types type)
{
	using namespace SXG;

	switch (type)
	{
	case Types::INT_NORM:
	case Types::INT_NORM2:
	case Types::INT_NORM3:
	case Types::INT_NORM4: return true;
	}

	return false;
}

bool TypeIsInteger(SXG::Types type)
{
	using namespace SXG;

	switch (type)
	{
	case Types::INT:
	case Types::INT2:
	case Types::INT3:
	case Types::INT4: return true;
	}

	return false;
}

bool TypeIsFloat(SXG::Types type)
{
	return !TypeIsInteger(type);
}

}