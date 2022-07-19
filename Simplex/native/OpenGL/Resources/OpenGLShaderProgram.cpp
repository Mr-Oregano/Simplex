
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>
#include <FileSystem.h>

#include "OpenGLShaderProgram.h"

#include "../OpenGLUtility.h"

using namespace SXG;

GLint OpenGLShaderProgram::GetUniformLocation(const std::string &name)
{
    auto it_location = uniforms.find(name);

    if (it_location != uniforms.end())
        return it_location->second;

    GLint location = glGetUniformLocation(id, name.c_str());
    if (location != -1)
        uniforms.insert(std::pair(name, location));
    else
        LOG_WARN("Attempting to modify uniform \"{0}\", however, the uniform was never found!", name);

    return location;
}

ShaderProgramHandle OpenGLShaderProgramManager::Create(const std::string &vert_src, const std::string &frag_src)
{
    OpenGLShaderProgram program{};

    program.id = glCreateProgram();

    GLuint vertex = Compile(vert_src, ShaderStageType::VERTEX);
    GLuint fragment = Compile(frag_src, ShaderStageType::FRAGMENT);

    glAttachShader(program.id, vertex);
    glAttachShader(program.id, fragment);

    glLinkProgram(program.id);

    GLint success = 0;
    glGetProgramiv(program.id, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program.id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(program.id, maxLength, &maxLength, &errorLog[0]);

        glDeleteProgram(program.id);
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        LOG_ERROR("Failed to link program.\n{0}", std::string(errorLog.begin(), errorLog.end()));
        return ShaderProgramHandle{};
    }

    glDetachShader(program.id, vertex);
    glDetachShader(program.id, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return static_cast<ShaderProgramHandle>(m_Pool.Emplace(std::move(program)));
}

ShaderProgramHandle OpenGLShaderProgramManager::CreateFromFiles(const std::string &vert_path, const std::string &frag_path)
{
    std::string vert_src = ReadFileToString(vert_path);
    std::string frag_src = ReadFileToString(frag_path);

    return Create(vert_src, frag_src);
}

void OpenGLShaderProgramManager::Destroy(ShaderProgramHandle handle)
{
    OpenGLShaderProgram &program = m_Pool.Get(handle);

    LOG_INFO("Deleting resource: Shader Program {0}", program.id);
    glDeleteProgram(program.id);

    m_Pool.Release(handle);
}

void OpenGLShaderProgramManager::Bind(ShaderProgramHandle handle) const
{
    glUseProgram(m_Pool.GetConst(handle).id);
}

GLuint OpenGLShaderProgramManager::Compile(const std::string &src, ShaderStageType type)
{
    GLuint shader = glCreateShader(SXGShaderStageToGL(type));

    const char *src_c = src.c_str();
    glShaderSource(shader, 1, &src_c, nullptr);
    glCompileShader(shader);
   
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        LOG_ERROR("Failed to compile shader.\n{0}", std::string(errorLog.begin(), errorLog.end()));

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

const OpenGLShaderProgram &OpenGLShaderProgramManager::Get(ShaderProgramHandle handle) const
{
    return m_Pool.GetConst(handle);
}

void OpenGLShaderProgramManager::SetUniformFloat1(ShaderProgramHandle handle, const std::string &name, float v1)
{
    OpenGLShaderProgram &program = m_Pool.Get(handle);

    glProgramUniform1f(program.id, program.GetUniformLocation(name), v1);
}

void OpenGLShaderProgramManager::SetUniformFloat2(ShaderProgramHandle handle, const std::string &name, float v1, float v2)
{
    OpenGLShaderProgram &program = m_Pool.Get(handle);

    glProgramUniform2f(program.id, program.GetUniformLocation(name), v1, v2);
}

void OpenGLShaderProgramManager::SetUniformFloat3(ShaderProgramHandle handle, const std::string &name, float v1, float v2, float v3)
{
    OpenGLShaderProgram &program = m_Pool.Get(handle);

    glProgramUniform3f(program.id, program.GetUniformLocation(name), v1, v2, v3);
}

void OpenGLShaderProgramManager::SetUniformFloat4(ShaderProgramHandle handle, const std::string &name, float v1, float v2, float v3, float v4)
{
    OpenGLShaderProgram &program = m_Pool.Get(handle);

    glProgramUniform4f(program.id, program.GetUniformLocation(name), v1, v2, v3, v4);
}

void OpenGLShaderProgramManager::SetUniformInt1(ShaderProgramHandle handle, const std::string &name, int v1)
{
    OpenGLShaderProgram &program = m_Pool.Get(handle);

    glProgramUniform1i(program.id, program.GetUniformLocation(name), v1);
}

void OpenGLShaderProgramManager::SetUniformInt2(ShaderProgramHandle handle, const std::string &name, int v1, int v2)
{
    OpenGLShaderProgram &program = m_Pool.Get(handle);

    glProgramUniform2i(program.id, program.GetUniformLocation(name), v1, v2);
}

void OpenGLShaderProgramManager::SetUniformInt3(ShaderProgramHandle handle, const std::string &name, int v1, int v2, int v3)
{
    OpenGLShaderProgram &program = m_Pool.Get(handle);

    glProgramUniform3i(program.id, program.GetUniformLocation(name), v1, v2, v3);
}

void OpenGLShaderProgramManager::SetUniformInt4(ShaderProgramHandle handle, const std::string &name, int v1, int v2, int v3, int v4)
{
    OpenGLShaderProgram &program = m_Pool.Get(handle);

    glProgramUniform4i(program.id, program.GetUniformLocation(name), v1, v2, v3, v4);
}

void OpenGLShaderProgramManager::SetUniformMat4(ShaderProgramHandle handle, const std::string &name, const float *m)
{
    OpenGLShaderProgram &program = m_Pool.Get(handle);

    glProgramUniformMatrix4fv(program.id, program.GetUniformLocation(name), 1, GL_FALSE, m);
}