#pragma once
#include "Renderer/GraphicsContext.h"
#include "Core/Core.h"

#include "Platforms/OpenGL/GLRenderer/OGLRenderer.h"
#include "Platforms/OpenGL/GLRenderer/Advanced/OGLModel.h"

struct GLFWwindow; 

namespace SE
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* InWindow);

		virtual bool Init(unsigned int width, unsigned int height) override;
		virtual void Update() override;
		virtual void Shutdown() override; 
		virtual Renderer* GetRenderer() const override;

	private:
		GLFWwindow* m_Window;
		Scope<OGLRenderer> m_Renderer;
		Scope<OGLModel> m_Model; 
	};
}
