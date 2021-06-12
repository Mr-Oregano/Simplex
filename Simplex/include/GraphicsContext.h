#pragma once

#include <Ref.h>

#include <Sxg.h>
#include <VertexBuffer.h>
#include <VertexArray.h>
#include <Pipeline.h>

#include <vector>
#include <string>

struct GraphicsConfig
{
	RendererAPI desiredAPI = RendererAPI::SXG_OPENGL;
};

class GraphicsContext
{
public:
	virtual Ref<VertexBuffer> CreateBuffer(VertexBufferProps props) = 0;
	virtual Ref<VertexArray> CreateArray(VertexArrayProps props) = 0;
	virtual Ref<Pipeline> CreatePipelineFromFiles(const std::string &vertpath, const std::string &fragpath) = 0;

	virtual void Draw(int count, int start_offset = 0) = 0;
	virtual void SetArray(Ref<VertexArray> va) = 0;
	virtual void SetPipeline(Ref<Pipeline> shader) = 0;
	virtual void ClearColor(float r, float g, float b, float a) = 0;
	virtual void ClearRenderTarget(SXG flags) = 0;

	virtual RendererAPI CurrentRenderer() = 0;

public:
	static Ref<GraphicsContext> Create(GraphicsConfig config = GraphicsConfig());
};