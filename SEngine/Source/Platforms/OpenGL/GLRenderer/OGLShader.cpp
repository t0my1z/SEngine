#include "sepch.h"
#include "OGLShader.h"
#include <fstream> 

namespace SE
{
	bool OGLShader::LoadShader(const std::string& VertexShaderPath, const std::string& FragmentShaderPath)
	{
		GLuint VertexShader = ReadShader(VertexShaderPath, GL_VERTEX_SHADER);
		if (!VertexShader)
		{
			SE_CORE_WARN("Failed to load Vertex Shader");
			return false;
		}

		GLuint FragmentShader = ReadShader(FragmentShaderPath, GL_FRAGMENT_SHADER);
		if (!FragmentShader)
		{
			SE_CORE_WARN("Failed to load Fragment Shader");
			return false;
		}

		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, VertexShader);
		glAttachShader(m_ShaderProgram, FragmentShader);
		glLinkProgram(m_ShaderProgram);

		GLint IsProgramLinked;
		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &IsProgramLinked);
		if (!IsProgramLinked)
		{
			int logMessageLength;
			std::vector<char> programLog;
			glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &logMessageLength);
			programLog = std::vector<char>(logMessageLength + 1);
			glGetProgramInfoLog(m_ShaderProgram, logMessageLength, &logMessageLength, programLog.data());
			programLog.at(logMessageLength) = '\0';
			SE_CORE_WARN("Error: Linking of shaders {0} and {1} failed", VertexShaderPath, FragmentShaderPath);
			SE_CORE_WARN("Compile log for shader was: {0}", programLog.data());

			glDeleteShader(VertexShader);
			glDeleteShader(FragmentShader);

			return false;
		}

		glDeleteShader(VertexShader);
		glDeleteShader(FragmentShader);

		return true;
	}

	void OGLShader::Use()
	{
		glUseProgram(m_ShaderProgram);
	}

	void OGLShader::CleanUp()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	GLuint OGLShader::ReadShader(const std::string& ShaderFileName, GLuint ShaderType)
	{
		GLuint Shader;
		std::string ShaderAsText;
		std::ifstream InFile(ShaderFileName);

		if (InFile.is_open())
		{
			InFile.seekg(0, std::ios::end);
			ShaderAsText.reserve(InFile.tellg());
			InFile.seekg(0, std::ios::beg);
			ShaderAsText.assign(std::istreambuf_iterator<char>(InFile), std::istreambuf_iterator<char>());
			InFile.close();
		}
		else
		{
			SE_CORE_WARN("Error: Could not open file {}", InFile);
			return 0;
		}
		if (InFile.bad() || InFile.fail())
		{
			InFile.close();
			SE_CORE_WARN("Error: Error while reading file {}", InFile);
			return 0;
		}

		const char* ShaderSource = ShaderAsText.c_str();
		Shader = glCreateShader(ShaderType);
		glShaderSource(Shader, 1, (const GLchar**)&ShaderSource, 0);
		glCompileShader(Shader);

		GLint IsShaderCompiled;
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &IsShaderCompiled);
		if (!IsShaderCompiled)
		{
			int logMessageLength;
			std::vector<char> shaderLog;
			glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &logMessageLength);
			shaderLog = std::vector<char>(logMessageLength + 1);
			glGetShaderInfoLog(Shader, logMessageLength, &logMessageLength, shaderLog.data());
			shaderLog.at(logMessageLength) = '\0';
			SE_CORE_WARN("Error: Compile of shader {0} failed", ShaderFileName);
			SE_CORE_WARN("Compile log for shader was: {0}", shaderLog.data());
			return false;
		}

		return Shader;
	}
}