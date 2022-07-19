#pragma once

#include <GraphicsContext.h>

#include "Resources/OpenGLShaderProgram.h"
#include "Resources/OpenGLVertexArray.h"
#include "Resources/OpenGLVertexBuffer.h"
#include "Resources/OpenGLIndexBuffer.h"
#include "Resources/OpenGLUniformBuffer.h"
#include "Resources/OpenGLTexture2D.h"

class OpenGLContext : public GraphicsContext
{
public:
	virtual VertexBufferManager &GetVertexBufferManager() override { return m_VertexBufferManager; }
	virtual IndexBufferManager &GetIndexBufferManager() override { return m_IndexBufferManager; }
	virtual UniformBufferManager &GetUniformBufferManager() override { return m_UniformBufferManager; }
	virtual VertexArrayManager &GetVertexArrayManager() override { return m_VertexArrayManager; }
	virtual Texture2DManager &GetTexture2DManager() override { return m_Texture2DManager; }
	virtual ShaderProgramManager &GetShaderManager() override { return m_ShaderProgramManager; }

	virtual void Draw(int count, int start_offset) override;
	virtual void DrawInstanced(int instances, int count, int start_offset = 0) override;
	virtual void DrawIndexed(int count) override;
	virtual void DrawIndexedInstanced(int instances, int count) override;

	virtual void ClearColor(float r, float g, float b, float a) override;
	virtual void ClearRenderTarget(SXG::Clear flags) override;
	virtual void SetViewport(int x, int y, int width, int height) override;

	virtual SXG::API CurrentRenderer() override { return SXG::API::OPENGL; }

// Native
public:
	OpenGLContext();
	virtual ~OpenGLContext();

private:
	OpenGLVertexBufferManager m_VertexBufferManager;
	OpenGLIndexBufferManager m_IndexBufferManager;
	OpenGLUniformBufferManager m_UniformBufferManager;
	OpenGLVertexArrayManager m_VertexArrayManager;
	OpenGLTexture2DManager m_Texture2DManager;
	OpenGLShaderProgramManager m_ShaderProgramManager;
};