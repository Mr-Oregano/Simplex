
// Precompiled Header
#include "sxpch.h"
//

#include "PNGFileReader.h"

#include <Simplex.h>

#include <stb_image.h>

// TODO: Use custom cross-platform file system
#include <filesystem>

PNGFileReader::PNGFileReader(const std::string &path)
    : ImageFileReader(path)
{
    std::filesystem::path file(path);
    m_Loaded = std::filesystem::exists(file);

    if (!m_Loaded)
        LOG_ERROR("File '{0}' could not be opened!", m_Path);

}

PNGFileReader::~PNGFileReader()
{
    stbi_image_free(m_ByteData);
    m_ByteData = nullptr;
}

unsigned char *PNGFileReader::ReadAllBytes()
{
    if (!m_Loaded)
    {
        LOG_ERROR("Attempting to read from file that wasn't loaded! '{0}'", m_Path);
        return nullptr;
    }

    if (m_ByteData)
        LOG_WARN("Reading from file again! '{0}'", m_Path);

    m_ByteData = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
    return m_ByteData;
}
