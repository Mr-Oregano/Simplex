#pragma once

#include <GraphicsContext.h>

#include "OpenGLVertexArray.h"

class OpenGLContext : public GraphicsContext
{
public:
	virtual Ref<VertexBuffer> CreateBuffer(VertexBufferProps props) override;
	virtual Ref<IndexBuffer> CreateIndexBuffer(IndexBufferProps props) override;
	virtual Ref<UniformBuffer> CreateUniformBuffer(UniformBufferProps props) override;
	virtual Ref<VertexArray> CreateArray(VertexArrayProps props) override;
	virtual Ref<Texture2D> CreateTexture2D(TextureProps props) override;
	virtual Ref<ShaderProgram> CreateShaderFromFiles(const std::string &vertpath, const std::string &fragpath) override;

	virtual void Draw(int count, int start_offset) override;
	virtual void DrawInstanced(int instances, int count, int start_offset = 0) override;
	virtual void DrawIndexed(int count) override;
	virtual void DrawIndexedInstanced(int instances, int count) override;

	virtual void BindArray(Ref<VertexArray> va) override;
	virtual void BindShaderProgram(Ref<ShaderProgram> shader) override;
	virtual void BindUniformBuffer(Ref<UniformBuffer> ub, int slot, SXG::ShaderStageType shader) override;
	virtual void BindTexture2D(Ref<Texture2D> texture, int unit) override;

	virtual void ClearColor(float r, float g, float b, float a) override;
	virtual void ClearRenderTarget(SXG::Clear flags) override;
	virtual void SetViewport(int x, int y, int width, int height) override;

	virtual SXG::API CurrentRenderer() override { return SXG::API::OPENGL; }

// Native
public:
	OpenGLContext();
	virtual ~OpenGLContext();

private:
	Ref<VertexArray> m_SelectedVA = nullptr;
	Ref<ShaderProgram> m_SelectedShaderProgram = nullptr;

	std::vector<Ref<Texture2D>> m_SelectedTexture2Ds;
	std::vector<Ref<UniformBuffer>> m_SelectedUBOs;
//
};