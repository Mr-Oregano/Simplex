#pragma once

#include <GraphicsContext.h>

#include "OpenGLVertexArray.h"

class OpenGLContext : public GraphicsContext
{
public:
	virtual Ref<VertexBuffer> CreateBuffer(VertexBufferProps props) override;
	virtual Ref<VertexArray> CreateArray(VertexArrayProps props) override;
	virtual Ref<ShaderProgram> CreateShaderFromFiles(const std::string &vertpath, const std::string &fragpath) override;

	virtual void Draw(int count, int start_offset) override;
	virtual void SetArray(Ref<VertexArray> va) override;
	virtual void SetShaderProgram(Ref<ShaderProgram> shader) override;
	virtual void ClearColor(float r, float g, float b, float a) override;
	virtual void ClearRenderTarget(SXG::Clear flags) override;

	virtual RendererAPI CurrentRenderer() override;

// Native
private:
	Ref<VertexArray> m_SelectedVA = nullptr;
//
};