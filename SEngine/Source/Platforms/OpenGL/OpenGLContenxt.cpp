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

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Logger::log(1, "Failed to initialize GLAD\n");
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}