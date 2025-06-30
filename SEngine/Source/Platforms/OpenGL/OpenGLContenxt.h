#pragma once
#include "Renderer/GraphicsContext.h"

struct GLFWwindow; 

namespace SE
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* InWindow);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;
	};
}
