#pragma once
#include "Renderer/GraphicsContext.h"
#include <string>
#include <vulkan/vulkan.h> 
#include <GLFW/glfw3.h>

namespace SE
{
	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(GLFWwindow* InWindow, const std::string& InAppName); 

		virtual bool Init(unsigned int width, unsigned int height) override; 
		virtual void Update() override; 
		virtual void Shutdown() override;
		virtual Renderer* GetRenderer() const override { return nullptr; }

	private:
		bool InitVulkan();

	private:
		GLFWwindow* m_Window = nullptr;
		std::string m_AppName;

		VkInstance m_Instance; 
		VkSurfaceKHR m_Surface;  
	};
}
