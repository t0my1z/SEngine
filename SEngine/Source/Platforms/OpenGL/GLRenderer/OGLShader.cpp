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
			return false;
		}

		GLuint FragmentShader = ReadShader(FragmentShaderPath, GL_FRAGMENT_SHADER); 
		if (!FragmentShader) 
		{
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
		else return 0; 

		if (InFile.bad() || InFile.fail())
		{
			InFile.close();
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
			return false;
		}

		return Shader; 
	}
}