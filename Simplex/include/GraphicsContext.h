#pragma once

#include <Ref.h>

#include <Sxg.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <UniformBuffer.h>
#include <VertexArray.h>
#include <ShaderProgram.h>
#include <Texture2D.h>

#include <vector>
#include <string>

struct GraphicsProps
{
	SXG::API desiredAPI = SXG::API::OPENGL;
	SXG::APIVersion minVersion = SXG::MakeOpenGLVersion(4, 5);
	SXG::APIVersion desiredVersion = SXG::MakeOpenGLVersion(4, 6);
};

class GraphicsContext
{
public:
	virtual ~GraphicsContext() = default;

	virtual VertexBufferManager& GetVertexBufferManager() = 0;
	virtual IndexBufferManager& GetIndexBufferManager() = 0;
	virtual UniformBufferManager& GetUniformBufferManager() = 0;
	virtual VertexArrayManager& GetVertexArrayManager() = 0;
	virtual Texture2DManager& GetTexture2DManager() = 0;
	virtual ShaderProgramManager& GetShaderManager() = 0;

	virtual void Draw(int count, int start_offset = 0) = 0;
	virtual void DrawInstanced(int instances, int count, int start_offset = 0) = 0;
	virtual void DrawIndexed(int count) = 0;
	virtual void DrawIndexedInstanced(int instances, int count) = 0;

	virtual void ClearColor(float r, float g, float b, float a) = 0;
	virtual void ClearRenderTarget(SXG::Clear flags) = 0;
	virtual void SetViewport(int x, int y, int width, int height) = 0;

	virtual SXG::API CurrentRenderer() = 0;
};