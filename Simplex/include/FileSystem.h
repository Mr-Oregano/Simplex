#pragma once

#include <Simplex.h>

#include <string>
#include <fstream>
#include <iostream>

// TODO: In the future will need to create an
// interface service for cross platform file system IO.
//
class FileSystem
{

};

inline std::string ReadFileToString(const std::string &path)
{
	std::ifstream ifs(path);

	ASSERT_CRITICAL(ifs.is_open(), "File: '{0}' was not found or could not be opened!", path);

	return std::string(std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{});
}