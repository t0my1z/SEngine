#include "sepch.h"
#include "OGLRenderer.h"

#include "OGLFrameBuffer.h"
#include "OGLVertexArray.h"
#include "OGLTexture.h"
#include "OGLShader.h"

namespace SE
{
	bool OGLRenderer::Init(unsigned int width, unsigned int height)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Logger::log(1, "Failed to initialize GLAD\n");
			return false;
		}

		if (!GLAD_GL_VERSION_4_6)    
		{
			return false;
		}

		m_FrameBuffer = CreateScope<OGLFrameBuffer>(); 
		if (!m_FrameBuffer->Init(width, height)) return false;

		m_Texture = CreateScope<OGLTexture>();
		if (!m_Texture->LoadTexture("Resources/Textures/crate.png")) return false;

		m_VertexArray = CreateScope<OGLVertexArray>();
		m_VertexArray->Init();

		m_BasicShader = CreateScope<OGLShader>();  
		if (!m_BasicShader->LoadShader("Resources/Shaders/basic.vert", "Resources/Shaders/basic.frag")) return false;

		return true; 
	}

	void OGLRenderer::SetSize(unsigned int width, unsigned int height)
	{
		m_FrameBuffer->Resize(width, height);
		glViewport(0, 0, width, height);
	}

	void OGLRenderer::CleanUp()
	{
		m_Shader->CleanUp(); 
		m_Texture->CleanUp();
		m_VertexArray->CleanUp();
		m_FrameBuffer->CleanUp(); 
	}

	void OGLRenderer::UploadData(OGLMesh vertexData)
	{
		m_TriangleCount = vertexData->m_Vertices.size();
		m_VertexArray->UploadData(vertexData); 
	}

	void OGLRenderer::Draw()
	{
		m_FrameBuffer->Bind();
		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		glEnable(GL_CULL_FACE); 

		m_BasicShader->Bind();
		m_Texture->Bind();
		m_VertexArray->Bind();
		m_VertexArray->Draw(GL_TRIANGLES, 0, m_TriangleCount); 
		m_Texture->Unbind(); 
		m_FrameBuffer->Unbind(); 
		m_FrameBuffer->DrawToScreen(); 
	}
}