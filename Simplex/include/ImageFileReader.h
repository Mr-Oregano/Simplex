#pragma once

#include <Ref.h>

#include <string>

class ImageFileReader
{
public:
	ImageFileReader(const std::string &path);
	virtual ~ImageFileReader() = default;

	virtual unsigned char *ReadAllBytes() = 0;

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	int GetNumChannels() const { return m_Channels; }

	operator bool() const { return m_Loaded; }

protected:
	std::string m_Path;
	bool m_Loaded = false;
	
	int m_Width = 0;
	int m_Height = 0;
	int m_Channels = 0;

public:
	static Scope<ImageFileReader> Load(const std::string &path);
};