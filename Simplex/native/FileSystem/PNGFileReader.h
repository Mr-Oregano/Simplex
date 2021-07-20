#pragma once

#include <ImageFileReader.h>

#include <string>

class PNGFileReader : public ImageFileReader
{
public:
	PNGFileReader(const std::string &path);
	virtual ~PNGFileReader();

	virtual unsigned char *ReadAllBytes() override;

private:
	unsigned char *m_ByteData = nullptr;
};