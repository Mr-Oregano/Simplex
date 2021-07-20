
// Precompiled Header
#include "sxpch.h"
//

#include "ImageFileReader.h"

// TODO: Should not be including native files in CORE
//
#include "../native/FileSystem/PNGFileReader.h"

#include <Simplex.h>

// TODO: Use custom cross-platform file system
#include <iostream>
#include <fstream>

// TODO: The file signatures are hardcoded in little endian
// however it is possible on some platforms that it
// may need to be big endian.
//
#define PNG_SIG 0x0a1a0a0d474e5089U 

ImageFileReader::ImageFileReader(const std::string &path)
    : m_Path(path)
{}

Scope<ImageFileReader> ImageFileReader::Load(const std::string &path)
{
    std::ifstream file(path, std::ios_base::in | std::ios_base::binary);
    if (!file.is_open())
    {
        LOG_ERROR("File '{0}' could not be opened!", path);
        return nullptr;
    }
    
    unsigned long long header = 0;
    file.read((char*) &header, sizeof(header));
    file.close();

    if (header == PNG_SIG) // Passes PNG test?
        return CreateScope<PNGFileReader>(path);
    
    LOG_ERROR("File type of '{0}' is currently unsupported!", path);
    return nullptr;
}
