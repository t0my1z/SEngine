#pragma once
#include "Renderer/VertexArray.h"

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OGLRenderData.h"

namespace SE
{
	class OGLVertexArray : public VertexArray
	{
	public:
		void Init();
		void UploadData(OGLMesh vertexData);
		void Bind();
		void Unbind();
		void Draw(GLuint mode, unsigned int start, unsigned int num);
		void CleanUp();

	private:
		//Vertex Array Object -> Contains the vertex buffer
		GLuint m_VAO = 0;
		//Vertex Buffer Object -> Contains vertex and texture data
		GLuint m_VertexVBO = 0;
	};

}