#include "sepch.h" 
#include "OpenGLContenxt.h"
#include "Core/Logger.h" 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SE
{
	OpenGLContext::OpenGLContext(GLFWwindow* InWindow) 
		: m_Window(InWindow)
	{
	}

	bool OpenGLContext::Init(unsigned int width, unsigned int height)
	{
		glfwMakeContextCurrent(m_Window);

		m_Renderer = CreateScope<OGLRenderer>();
		if (!m_Renderer->Init(width, height)) 
		{
			return false; 
		}

		m_Model = CreateScope<OGLModel>(); 
		m_Model->Init(); 

		m_Renderer->UploadData(m_Model->GetVertexData()); 

		return true; 
	}

	void OpenGLContext::Update() 
	{
		m_Renderer->Draw();

		glfwSwapBuffers(m_Window);
	}

	void OpenGLContext::Shutdown()
	{
		m_Renderer->CleanUp();
	}

	Renderer* OpenGLContext::GetRenderer() const
	{
		return m_Renderer.get();  
	}
}