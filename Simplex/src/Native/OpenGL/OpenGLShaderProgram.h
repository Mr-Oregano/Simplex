#pragma once

#include <Sxg.h>
#include <ShaderProgram.h>

#include <glad/glad.h>

#include <string>
#include <unordered_map>

class OpenGLShaderProgram : public ShaderProgram
{
public:
	virtual void SetUniformFloat1(const std::string &name, float v1) override;
	virtual void SetUniformFloat2(const std::string &name, float v1, float v2) override;
	virtual void SetUniformFloat3(const std::string &name, float v1, float v2, float v3) override;
	virtual void SetUniformFloat4(const std::string &name, float v1, float v2, float v3, float v4) override;

	virtual void SetUniformInt1(const std::string &name, int v1) override;
	virtual void SetUniformInt2(const std::string &name, int v1, int v2) override;
	virtual void SetUniformInt3(const std::string &name, int v1, int v2, int v3) override;
	virtual void SetUniformInt4(const std::string &name, int v1, int v2, int v3, int v4) override;

	virtual void SetUniformMat4(const std::string &name, const float *m) override;

// Native
public:
	OpenGLShaderProgram(const std::string &vert_src, const std::string &frag_src);
	virtual ~OpenGLShaderProgram();

	GLuint Compile(const std::string &src, SXG::ShaderStageType type);
	GLint GetUniformLocation(const std::string &name);

	GLuint ContextID() const;

private:
	GLuint m_ContextID;
	std::unordered_map<std::string, GLint> m_Uniforms;
//
};