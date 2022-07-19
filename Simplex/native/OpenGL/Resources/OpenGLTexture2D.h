#pragma once

#include <Texture2D.h>

#include <Sxg.h>

#include <glad/glad.h>

struct OpenGLTexture2D
{
	friend class OpenGLTexture2DManager;

	GLuint id = 0;

	int width = 0;
	int height = 0;
	int channels = 0;

	SXG::TexFilter filter;
	SXG::TexWrapMode wrap;
	SXG::TexMipmapMode mipmap;

private:
	void PremultiplyAlpha(unsigned char *data);
	void LoadTexture(unsigned char *data);
};

class OpenGLTexture2DManager : public Texture2DManager
{
public:
	virtual TextureHandle Create(const TextureProps &) override;
	virtual void Destroy(TextureHandle) override;

	virtual void Bind(TextureHandle, int unit = 0) const override;

public:
	const OpenGLTexture2D &Get(TextureHandle) const;

private:
	ResourcePool<OpenGLTexture2D> m_Pool;
};