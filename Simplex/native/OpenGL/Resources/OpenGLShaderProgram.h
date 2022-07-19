#pragma once

#include <Sxg.h>
#include <ShaderProgram.h>

#include <glad/glad.h>

#include <string>
#include <unordered_map>

struct OpenGLShaderProgram
{
	std::unordered_map<std::string, GLint> uniforms;
	GLuint id;

public:
	GLint GetUniformLocation(const std::string &name);
};

class OpenGLShaderProgramManager : public ShaderProgramManager
{
public:
	virtual ShaderProgramHandle Create(const std::string &vert_src, const std::string &frag_src) override;
	virtual ShaderProgramHandle CreateFromFiles(const std::string &vert_path, const std::string &frag_path) override;
	virtual void Destroy(ShaderProgramHandle handle) override;

	virtual void Bind(ShaderProgramHandle) const override;

	virtual void SetUniformFloat1(ShaderProgramHandle shader, const std::string &name, float v1) override;
	virtual void SetUniformFloat2(ShaderProgramHandle shader, const std::string &name, float v1, float v2) override;
	virtual void SetUniformFloat3(ShaderProgramHandle shader, const std::string &name, float v1, float v2, float v3) override;
	virtual void SetUniformFloat4(ShaderProgramHandle shader, const std::string &name, float v1, float v2, float v3, float v4) override;

	virtual void SetUniformInt1(ShaderProgramHandle shader, const std::string &name, int v1) override;
	virtual void SetUniformInt2(ShaderProgramHandle shader, const std::string &name, int v1, int v2) override;
	virtual void SetUniformInt3(ShaderProgramHandle shader, const std::string &name, int v1, int v2, int v3) override;
	virtual void SetUniformInt4(ShaderProgramHandle shader, const std::string &name, int v1, int v2, int v3, int v4) override;

	virtual void SetUniformMat4(ShaderProgramHandle shader, const std::string &name, const float *m) override;

// Native
private:
	GLuint Compile(const std::string &src, SXG::ShaderStageType type);

public:
	const OpenGLShaderProgram &Get(ShaderProgramHandle) const;

private:
	ResourcePool<OpenGLShaderProgram> m_Pool;
};

