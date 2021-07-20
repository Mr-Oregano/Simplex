#pragma once

#include <Sxg.h>
#include <Texture2D.h>

#include <glad/glad.h>

GLenum SXGTypeToGL(SXG::Types type);

GLenum SXGTopologyToGL(SXG::Topology topology);

GLenum SXGShaderStageToGL(SXG::ShaderStageType type);

GLenum ChannelsToFormatGL(int channels);

GLenum SXGFilterToGL(SXG::TexFilter filter, SXG::TexMipmapMode mipmap);

GLenum SXGWrapModeToGL(SXG::TexWrapMode wrap);

GLbitfield SXGUsageToBufferStorageFlag(SXG::BufferUsage usage);