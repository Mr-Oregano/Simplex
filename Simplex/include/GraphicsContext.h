#pragma once

#include <Ref.h>

#include <Sxg.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <ShaderProgram.h>
#include <Texture2D.h>

#include <vector>
#include <string>

struct GraphicsProps
{
	SXG::API desiredAPI = SXG::API::OPENGL;
	SXG::APIVersion minVersion = SXG::MakeOpenGLVersion(3, 3);
	SXG::APIVersion desiredVersion = SXG::MakeOpenGLVersion(4, 6);
};

class GraphicsContext
{
public:
	virtual ~GraphicsContext() = default;

	virtual Ref<VertexBuffer> CreateBuffer(VertexBufferProps props) = 0;
	virtual Ref<IndexBuffer> CreateIndexBuffer(IndexBufferProps props) = 0;
	virtual Ref<VertexArray> CreateArray(VertexArrayProps props) = 0;
	virtual Ref<Texture2D> CreateTexture2D(TextureProps props) = 0;
	virtual Ref<ShaderProgram> CreateShaderFromFiles(const std::string &vertpath, const std::string &fragpath) = 0;

	virtual void Draw(int count, int start_offset = 0) = 0;
	virtual void DrawInstanced(int instances, int count, int start_offset = 0) = 0;
	virtual void DrawIndexed(int count) = 0;
	virtual void DrawIndexedInstanced(int instances, int count) = 0;

	virtual void BindArray(Ref<VertexArray> va) = 0;
	virtual void BindShaderProgram(Ref<ShaderProgram> shader) = 0;
	virtual void BindTexture2D(Ref<Texture2D> texture, int unit = 0) = 0;

	virtual void ClearColor(float r, float g, float b, float a) = 0;
	virtual void ClearRenderTarget(SXG::Clear flags) = 0;
	virtual void SetViewport(int x, int y, int width, int height) = 0;

	virtual SXG::API CurrentRenderer() = 0;
};