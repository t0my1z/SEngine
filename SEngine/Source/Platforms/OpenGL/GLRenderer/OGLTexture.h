#pragma once
#include "Renderer/Texture.h"

#include <string> 
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace SE
{
	class OGLTexture : public Texture
	{
	public:
		bool LoadTexture(std::string TexturePath); 
		void Bind();
		void Unbind();
		void CleanUp();

	private:
		GLuint m_Texture = 0;
	};
}
