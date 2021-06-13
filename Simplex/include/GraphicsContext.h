#pragma once

#include <Ref.h>

#include <Sxg.h>
#include <VertexBuffer.h>
#include <VertexArray.h>
#include <ShaderProgram.h>

#include <vector>
#include <string>

typedef int Version;

inline Version MakeOpenGLVersion(int major, int minor)
{
	return ((major & 0xff) << 8) | (minor & 0xff);
}

struct GraphicsConfig
{
	SXG::API desiredAPI = SXG::API::OPENGL;
	Version minVersion = MakeOpenGLVersion(3, 3);
	Version desiredVersion = MakeOpenGLVersion(4, 6);
};

class GraphicsContext
{
public:
	virtual Ref<VertexBuffer> CreateBuffer(VertexBufferProps props) = 0;
	virtual Ref<VertexArray> CreateArray(VertexArrayProps props) = 0;
	virtual Ref<ShaderProgram> CreateShaderFromFiles(const std::string &vertpath, const std::string &fragpath) = 0;

	virtual void Draw(int count, int start_offset = 0) = 0;
	virtual void SetArray(Ref<VertexArray> va) = 0;
	virtual void SetShaderProgram(Ref<ShaderProgram> shader) = 0;
	virtual void ClearColor(float r, float g, float b, float a) = 0;
	virtual void ClearRenderTarget(SXG::Clear flags) = 0;

	virtual SXG::API CurrentRenderer() = 0;
};