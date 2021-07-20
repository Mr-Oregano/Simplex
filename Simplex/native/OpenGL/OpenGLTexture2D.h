#pragma once

#include <Texture2D.h>

#include <Sxg.h>

#include <glad/glad.h>

class OpenGLTexture2D : public Texture2D
{
public:
	virtual int GetWidth() const override;
	virtual int GetHeight() const override;
	virtual int GetChannels() const override;

// Native
public:
	OpenGLTexture2D(TextureProps props);
	virtual ~OpenGLTexture2D();

	GLuint ContextID() const;

private:
	void PremultiplyAlpha(unsigned char *data);
	void LoadTexture(unsigned char *data);

private:
	GLuint m_ContextID = 0;

	int m_Width = 0;
	int m_Height = 0;
	int m_Channels = 0;

	SXG::TexFilter m_Filter;
	SXG::TexWrapMode m_Wrap;
	SXG::TexMipmapMode m_Mipmap;

};