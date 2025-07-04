#pragma once
#include "Renderer/Renderer.h"

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Core.h"
#include "OGLShader.h"
#include "Advanced/OGLModel.h"
#include "OGLFrameBuffer.h"
#include "OGLVertexArray.h"
#include "OGLTexture.h"

namespace SE
{
	class OGLRenderer : public Renderer
	{
	public:
		bool Init(unsigned int width, unsigned int height);
		virtual void SetSize(unsigned int width, unsigned int height) override; 
		void CleanUp();
		void UploadData(OGLMesh vertexData); 
		void Draw();  

	private:
		Scope<OGLShader> m_BasicShader; 
		Scope<OGLFrameBuffer> m_FrameBuffer;
		Scope<OGLVertexArray> m_VertexArray;
		Scope<OGLTexture> m_Texture;
		int m_TriangleCount = 0;
	};
}
