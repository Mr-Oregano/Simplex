#pragma once

#include <Sxg.h>

struct TextureProps
{
	unsigned char *data;
	int width;
	int height;
	int channels;
	SXG::TexFilter filter = SXG::TexFilter::Linear;
	SXG::TexWrapMode wrap = SXG::TexWrapMode::ClampToEdge;
	SXG::TexMipmapMode mipmap = SXG::TexMipmapMode::Linear;
};

class Texture2D
{
public:
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual int GetChannels() const = 0;
};