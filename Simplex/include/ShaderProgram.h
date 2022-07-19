#pragma once

#include <Resource.h>

struct ShaderProgramHandle : public ResourceHandle {};

class ShaderProgramManager
{
public:
	virtual ~ShaderProgramManager() = default;

	virtual ShaderProgramHandle Create(const std::string &vert_src, const std::string &frag_src) = 0;
	virtual ShaderProgramHandle CreateFromFiles(const std::string &vert_path, const std::string &frag_path) = 0;
	virtual void Destroy(ShaderProgramHandle handle) = 0;

	virtual void Bind(ShaderProgramHandle) const = 0;

	virtual void SetUniformFloat1(ShaderProgramHandle handle, const std::string &name, float v1) = 0;
	virtual void SetUniformFloat2(ShaderProgramHandle handle, const std::string &name, float v1, float v2) = 0;
	virtual void SetUniformFloat3(ShaderProgramHandle handle, const std::string &name, float v1, float v2, float v3) = 0;
	virtual void SetUniformFloat4(ShaderProgramHandle handle, const std::string &name, float v1, float v2, float v3, float v4) = 0;

	virtual void SetUniformInt1(ShaderProgramHandle handle, const std::string &name, int v1) = 0;
	virtual void SetUniformInt2(ShaderProgramHandle handle, const std::string &name, int v1, int v2) = 0;
	virtual void SetUniformInt3(ShaderProgramHandle handle, const std::string &name, int v1, int v2, int v3) = 0;
	virtual void SetUniformInt4(ShaderProgramHandle handle, const std::string &name, int v1, int v2, int v3, int v4) = 0;

	virtual void SetUniformMat4(ShaderProgramHandle handle, const std::string &name, const float *m) = 0;
};
