#pragma once

class ShaderProgram
{
public:
	virtual ~ShaderProgram() = default;

	virtual void SetUniformFloat1(const std::string &name, float v1) = 0;
	virtual void SetUniformFloat2(const std::string &name, float v1, float v2) = 0;
	virtual void SetUniformFloat3(const std::string &name, float v1, float v2, float v3) = 0;
	virtual void SetUniformFloat4(const std::string &name, float v1, float v2, float v3, float v4) = 0;

	virtual void SetUniformInt1(const std::string &name, int v1) = 0;
	virtual void SetUniformInt2(const std::string &name, int v1, int v2) = 0;
	virtual void SetUniformInt3(const std::string &name, int v1, int v2, int v3) = 0;
	virtual void SetUniformInt4(const std::string &name, int v1, int v2, int v3, int v4) = 0;

	virtual void SetUniformMat4(const std::string &name, const float *m) = 0;
};