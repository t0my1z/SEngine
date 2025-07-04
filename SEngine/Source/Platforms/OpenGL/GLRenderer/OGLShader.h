#pragma once
#include "Renderer/Shader.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SE
{
	class OGLShader : public Shader
	{
	public:
		bool LoadShader(const std::string& VertexShaderPath, const std::string& FragmentShaderPath); 
		void Use();
		void CleanUp();

	private:
		GLuint ReadShader(const std::string& ShaderFileName, GLuint ShaderType); 

	private:
		GLuint m_ShaderProgram = 0;
	};
}
