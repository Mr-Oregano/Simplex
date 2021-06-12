
// Precompiled Header
#include "sxpch.h"
//

#include <Simplex.h>

#include "OpenGLShaderProgram.h"

#include "OpenGLUtility.h"

using namespace SXG;

OpenGLShaderProgram::OpenGLShaderProgram(const std::string &vert_src, const std::string &frag_src)
{
    m_ContextID = glCreateProgram();

    GLuint vertex = Compile(vert_src, ShaderStageType::VERTEX);
    GLuint fragment = Compile(frag_src, ShaderStageType::FRAGMENT);

    glAttachShader(m_ContextID, vertex);
    glAttachShader(m_ContextID, fragment);

    glLinkProgram(m_ContextID);

    GLint success = 0;
    glGetProgramiv(m_ContextID, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_ContextID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(m_ContextID, maxLength, &maxLength, &errorLog[0]);

        glDeleteProgram(m_ContextID);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        m_ContextID = 0;

        LOG_ERROR("Failed to link program.\n{0}", std::string(errorLog.begin(), errorLog.end()));
        return;
    }

    glDetachShader(m_ContextID, vertex);
    glDetachShader(m_ContextID, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

OpenGLShaderProgram::~OpenGLShaderProgram()
{
    glDeleteProgram(m_ContextID);
}

GLuint OpenGLShaderProgram::Compile(const std::string &src, ShaderStageType type)
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

GLuint OpenGLShaderProgram::ContextID() const
{
    return m_ContextID;
}

GLint OpenGLShaderProgram::GetUniformLocation(const std::string &name)
{
    auto it_location = m_Uniforms.find(name);

    if (it_location != m_Uniforms.end())
        return it_location->second;

    GLint location = glGetUniformLocation(m_ContextID, name.c_str());
    if (location != -1)
        m_Uniforms.insert(std::pair(name, location));
    else
        LOG_WARN("Attempting to modify uniform \"{0}\", however, the uniform was never found!", name);

    return location;
}

void OpenGLShaderProgram::SetUniformFloat1(const std::string &name, float v1)
{
    glUniform1f(GetUniformLocation(name), v1);
}

void OpenGLShaderProgram::SetUniformFloat2(const std::string &name, float v1, float v2)
{
    glUniform2f(GetUniformLocation(name), v1, v2);
}

void OpenGLShaderProgram::SetUniformFloat3(const std::string &name, float v1, float v2, float v3)
{
    glUniform3f(GetUniformLocation(name), v1, v2, v3);
}

void OpenGLShaderProgram::SetUniformFloat4(const std::string &name, float v1, float v2, float v3, float v4)
{
    glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
}

void OpenGLShaderProgram::SetUniformInt1(const std::string &name, int v1)
{
    glUniform1i(GetUniformLocation(name), v1);
}

void OpenGLShaderProgram::SetUniformInt2(const std::string &name, int v1, int v2)
{
    glUniform2i(GetUniformLocation(name), v1, v2);
}

void OpenGLShaderProgram::SetUniformInt3(const std::string &name, int v1, int v2, int v3)
{
    glUniform3i(GetUniformLocation(name), v1, v2, v3);
}

void OpenGLShaderProgram::SetUniformInt4(const std::string &name, int v1, int v2, int v3, int v4)
{
    glUniform4i(GetUniformLocation(name), v1, v2, v3, v4);
}

void OpenGLShaderProgram::SetUniformMat4(const std::string &name, const float *m)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, m);
}
