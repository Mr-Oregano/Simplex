
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>

#include "OpenGLTexture2D.h"
#include "../OpenGLUtility.h"

using namespace SXG;

TextureHandle OpenGLTexture2DManager::Create(const TextureProps &props)
{
    OpenGLTexture2D texture{};

    texture.width = props.width;
    texture.height = props.height;
    texture.channels = props.channels;

    texture.filter = props.filter;
    texture.wrap = props.wrap;
    texture.mipmap = props.mipmap;

    glCreateTextures(GL_TEXTURE_2D, 1, &texture.id);
    texture.LoadTexture(props.data);

    return static_cast<TextureHandle>(m_Pool.Emplace(std::move(texture)));
}

void OpenGLTexture2DManager::Destroy(TextureHandle handle)
{
    OpenGLTexture2D &texture = m_Pool.Get(handle);

    LOG_INFO("Deleting resource: Texture {0}", texture.id);
    glDeleteTextures(1, &texture.id);

    m_Pool.Release(handle);
}

void OpenGLTexture2DManager::Bind(TextureHandle handle, int unit) const
{
    // TODO: Dynamically query the number of texture slots available on this system.
    ASSERT_CRITICAL(-1 < unit && unit < 16, "Texture unit must be between [0, {0}] for this hardware!", 15);

    const OpenGLTexture2D &gltx = m_Pool.GetConst(handle);
    glBindTextureUnit(unit, gltx.id);
}

const OpenGLTexture2D &OpenGLTexture2DManager::Get(TextureHandle handle) const
{
    return m_Pool.GetConst(handle);
}

void OpenGLTexture2D::PremultiplyAlpha(unsigned char *data)
{
    for (int i = 0; i < width * height * 4; i += 4)
    {
        float alpha = data[i + 3] / 255.0f;
        data[i + 0] = (unsigned char)(data[i + 0] * alpha);
        data[i + 1] = (unsigned char)(data[i + 1] * alpha);
        data[i + 2] = (unsigned char)(data[i + 2] * alpha);
    }
}

void OpenGLTexture2D::LoadTexture(unsigned char *data)
{
    GLenum format = ChannelsToFormatGL(channels);

    if (format == GL_RGBA)
        PremultiplyAlpha(data);

    glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, SXGFilterToGL(filter, TexMipmapMode::None)); // Mag filter will never use mipmaps
    glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, SXGFilterToGL(filter, mipmap));
    glTextureParameteri(id, GL_TEXTURE_WRAP_S, SXGWrapModeToGL(wrap));
    glTextureParameteri(id, GL_TEXTURE_WRAP_T, SXGWrapModeToGL(wrap));

    glPixelStorei(GL_UNPACK_ALIGNMENT, channels);

    glTextureStorage2D(id, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(id, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);

    if (mipmap == TexMipmapMode::Anisotropic)
    {
        if (GLAD_GL_EXT_texture_filter_anisotropic)
        {
            float anisotropy_max = 0;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropy_max);
            float amount = anisotropy_max > 4.0f ? anisotropy_max : 4.0f;
            glTextureParameterf(id, GL_TEXTURE_MAX_ANISOTROPY_EXT, amount);
        }
        else
            LOG_WARN("Anisotropic filtering not supported! Using default mipmapping instead.");
    }

    if (mipmap != TexMipmapMode::None)
        glGenerateTextureMipmap(id);
}