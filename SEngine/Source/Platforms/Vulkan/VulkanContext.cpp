#include "sepch.h" 
#include "VulkanContext.h"
#include "Core/Logger.h"
#include "vec2.hpp"

namespace SE
{
    VulkanContext::VulkanContext(GLFWwindow* InWindow, const std::string& InAppName)
        : m_Window(InWindow), m_AppName(InAppName), m_Instance(), m_Surface()
    {

    }

    void VulkanContext::Init()
    {
        if (!glfwVulkanSupported())
        {
            Logger::log(1, "%s: Vulkan is not supported\n", __FUNCTION__);
            return;
        }

        if (!InitVulkan())
        {
            Logger::log(1, "%s: Failed to Init Vulkan Context\n", __FUNCTION__);
            return;
        }
    }

    bool VulkanContext::InitVulkan()
    {
        //Result of trying to init vulkan
        VkResult result = VK_ERROR_UNKNOWN;

        VkApplicationInfo AppInfo;
        //What type of data structure is it? 
        AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        //Does it link to other vulkan data structure?
        AppInfo.pNext = nullptr;
        //AppInfo.pApplicationName = m_Data.m_Title.c_str();
        AppInfo.pApplicationName = m_AppName.c_str();
        AppInfo.applicationVersion = VK_MAKE_API_VERSION(0, 0, 0, 1);
        AppInfo.pEngineName = "SEngine GameProgramming";
        AppInfo.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
        //Version of the Vulkan API we use
        AppInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 1, 0);

        //Check if we have required extensions to run Vulkan
        uint32_t extensionCount = 0;
        const char** extensions = glfwGetRequiredInstanceExtensions(&extensionCount);

        if (extensionCount == 0)
        {
            Logger::log(1, "%s error: no Vulkan extensions found, need at least 'VK_KHR_surface'\n", __FUNCTION__);
            return false;
        }

        Logger::log(1, "%s: Found %u Vulkan extensions\n", __FUNCTION__, extensionCount);
        for (int i = 0; i < extensionCount; ++i)
        {
            Logger::log(1, "%s: %s\n", __FUNCTION__, std::string(extensions[i]).c_str());
        }

        VkInstanceCreateInfo CreateInfo{};
        CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        CreateInfo.pNext = nullptr;
        CreateInfo.pApplicationInfo = &AppInfo;
        CreateInfo.enabledExtensionCount = extensionCount;
        CreateInfo.ppEnabledExtensionNames = extensions;
        CreateInfo.enabledLayerCount = 0;

        //Create a vulkan instance that stores the Vulkan state on the application level 
        // - (No longer a global state (context) like in OpenGL) -
        result = vkCreateInstance(&CreateInfo, nullptr, &m_Instance);
        if (result != VK_SUCCESS)
        {
            Logger::log(1, "%s: Could not create Vulkan instance (%i)\n", __FUNCTION__, result);
            return false;
        }

        //Check to see how many graphics card we can find, and if they work with Vulkan
        uint32_t physicalDeviceCount = 0;
        vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCount, nullptr);
        if (physicalDeviceCount == 0)
        {
            Logger::log(1, "%s: No Vulkan capable GPU found\n", __FUNCTION__);
            return false;
        }

        std::vector<VkPhysicalDevice> devices;
        devices.resize(physicalDeviceCount);
        vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCount, devices.data());
        Logger::log(1, "%s: Found %u physical device(s)\n", __FUNCTION__, physicalDeviceCount);

        //Create the Vulkan Surface
        result = glfwCreateWindowSurface(m_Instance, m_Window, nullptr, &m_Surface);
        if (result != VK_SUCCESS)
        {
            Logger::log(1, "%s: Could not create Vulkan surface\n", __FUNCTION__);
            return false;
        }

        return true;
    }

    void VulkanContext::SwapBuffers()
    {
    }

    void VulkanContext::Shutdown()
    {
        Logger::log(1, "%s: Terminating Vulkan Context\n", __FUNCTION__);

        vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
        vkDestroyInstance(m_Instance, nullptr);
    }
}