#pragma once

#include <Resource.h>
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

struct TextureHandle : public ResourceHandle {};

class Texture2DManager
{
public:
	virtual ~Texture2DManager() = default;

	virtual TextureHandle Create(const TextureProps&) = 0;
	virtual void Destroy(TextureHandle) = 0;

	virtual void Bind(TextureHandle, int unit = 0) const = 0;
};