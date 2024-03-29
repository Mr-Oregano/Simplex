
// Precompiled Header
#include "sxpch.h"
//

#include "OpenGLUtility.h"

#include <Simplex.h>

GLenum SXGTypeToGL(SXG::Types type)
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

	case Types::UINT:
	case Types::UINT2:
	case Types::UINT3:
	case Types::UINT4: return GL_UNSIGNED_INT;
	}

	LOG_WARN("Unknown conversion to GL type, default to GL_FLOAT");
	return GL_FLOAT;
}

GLenum SXGTopologyToGL(SXG::Topology topology)
{
	using namespace SXG;

	switch (topology)
	{
	case Topology::TRIANGLES: return GL_TRIANGLES;
	}

	LOG_WARN("Unknown conversion to GL topology, default to GL_TRIANGLES");
	return GL_TRIANGLES;
}

GLenum SXGShaderStageToGL(SXG::ShaderStageType type)
{
	using namespace SXG;

	switch (type)
	{
	case ShaderStageType::VERTEX: return GL_VERTEX_SHADER;
	case ShaderStageType::FRAGMENT: return GL_FRAGMENT_SHADER;
	}

	LOG_WARN("Unknown conversion to GL shader stage, default to GL_VERTEX_SHADER");
	return GL_VERTEX_SHADER;
}

GLenum ChannelsToFormatGL(int channels)
{
	switch (channels)
	{
	case 1: return GL_RED;
	case 2: return GL_RG;
	case 3: return GL_RGB;
	case 4: return GL_RGBA;
	}

	LOG_WARN("Unsupported texture format (channels = {0})", channels);
	return 0;
}

GLenum SXGFilterToGL(SXG::TexFilter filter, SXG::TexMipmapMode mipmap)
{
	using namespace SXG;

	switch (filter)
	{
	case TexFilter::Linear:
		switch (mipmap)
		{
		case TexMipmapMode::None: return GL_LINEAR;
		case TexMipmapMode::Nearest: return GL_LINEAR_MIPMAP_NEAREST;
		default: return GL_LINEAR_MIPMAP_LINEAR;
		}
	case TexFilter::Nearest:
		switch (mipmap)
		{
		case TexMipmapMode::None: return GL_NEAREST;
		case TexMipmapMode::Nearest: return GL_NEAREST_MIPMAP_NEAREST;
		default: return GL_NEAREST_MIPMAP_LINEAR;
		}
	}

	LOG_WARN("Unknown conversion to GL texture filter, default to GL_LINEAR");
	return GL_LINEAR;

}

GLenum SXGWrapModeToGL(SXG::TexWrapMode wrap)
{
	using namespace SXG;

	switch (wrap)
	{
	case TexWrapMode::ClampToBorder: return GL_CLAMP_TO_BORDER;
	case TexWrapMode::ClampToEdge: return GL_CLAMP_TO_EDGE;
	case TexWrapMode::Mirror: return GL_MIRRORED_REPEAT;
	case TexWrapMode::Repeat: return GL_REPEAT;
	}

	LOG_WARN("Unknown conversion to GL texture wrap mode, default to GL_CLAMP_TO_EDGE");
	return GL_CLAMP_TO_EDGE;
}

GLbitfield SXGUsageToBufferStorageFlag(SXG::BufferUsage usage)
{
	using namespace SXG;

	switch (usage)
	{
	case BufferUsage::DYNAMIC: return GL_DYNAMIC_STORAGE_BIT;
	default: return 0;
	}
}