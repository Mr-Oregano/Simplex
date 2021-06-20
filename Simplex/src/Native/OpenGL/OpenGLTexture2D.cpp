
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>

#include "OpenGLTexture2D.h"
#include "OpenGLUtility.h"

using namespace SXG;

OpenGLTexture2D::OpenGLTexture2D(TextureProps props)
    : m_Width(props.width), m_Height(props.height), m_Channels(props.channels)
{
    m_Filter = props.filter;
    m_Wrap = props.wrap;
    m_Mipmap = props.mipmap;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_ContextID);
    LoadTexture(props.data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &m_ContextID);
}

GLuint OpenGLTexture2D::ContextID() const
{
    return m_ContextID;
}

void OpenGLTexture2D::PremultiplyAlpha(unsigned char *data)
{
    for (int i = 0; i < m_Width * m_Height * 4; i += 4)
    {
        float alpha = data[i + 3] / 255.0f;
        data[i + 0] = (unsigned char)(data[i + 0] * alpha);
        data[i + 1] = (unsigned char)(data[i + 1] * alpha);
        data[i + 2] = (unsigned char)(data[i + 2] * alpha);
    }
}

void OpenGLTexture2D::LoadTexture(unsigned char *data)
{
    GLenum format = ChannelsToFormatGL(m_Channels);

    if (format == GL_RGBA)
        PremultiplyAlpha(data);

    glTextureParameteri(m_ContextID, GL_TEXTURE_MAG_FILTER, SXGFilterToGL(m_Filter, TexMipmapMode::None)); // Mag filter will never use mipmaps
    glTextureParameteri(m_ContextID, GL_TEXTURE_MIN_FILTER, SXGFilterToGL(m_Filter, m_Mipmap));
    glTextureParameteri(m_ContextID, GL_TEXTURE_WRAP_S, SXGWrapModeToGL(m_Wrap));
    glTextureParameteri(m_ContextID, GL_TEXTURE_WRAP_T, SXGWrapModeToGL(m_Wrap));

    glPixelStorei(GL_UNPACK_ALIGNMENT, m_Channels);

    // OpenGL does not have a DSA version of glTexImage2D >:(
    //
    glBindTexture(GL_TEXTURE_2D, m_ContextID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_Mipmap == TexMipmapMode::Anisotropic)
    {
        if (GLAD_GL_EXT_texture_filter_anisotropic)
        {
            float anisotropy_max = 0;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropy_max);
            float amount = anisotropy_max > 4.0f ? anisotropy_max : 4.0;
            glTextureParameterf(m_ContextID, GL_TEXTURE_MAX_ANISOTROPY_EXT, amount);
        }
        else
            LOG_WARN("Anisotropic filtering not supported! Using default mipmapping instead.");
    }

    if (m_Mipmap != TexMipmapMode::None)
        glGenerateTextureMipmap(m_ContextID);

}

int OpenGLTexture2D::GetWidth() const
{
    return m_Width;
}

int OpenGLTexture2D::GetHeight() const
{
    return m_Height;
}

int OpenGLTexture2D::GetChannels() const
{
    return m_Channels;
}