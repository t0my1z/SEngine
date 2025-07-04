#include "sepch.h" 
#include "VulkanContext.h"
#include "glm/vec2.hpp" 

namespace SE
{
    VulkanContext::VulkanContext(GLFWwindow* InWindow, const std::string& InAppName)
        : m_Window(InWindow), m_AppName(InAppName), m_Instance(), m_Surface()
    {

    }

    bool VulkanContext::Init(unsigned int width, unsigned int height)
    {
        if (!glfwVulkanSupported())
        {
            SE_CORE_INFO("Vulkan is not supported");
            return false;
        }

        if (!InitVulkan())
        {
            SE_CORE_INFO("Failed to Init Vulkan Context");
            return false;
        }

        return true;
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
            SE_CORE_INFO("No Vulkan extensions found, need at least 'VK_KHR_surface'");
            return false;
        }

        SE_CORE_INFO("Found {0} Vulkan extensions:", extensionCount);

        for (unsigned int i = 0; i < extensionCount; ++i)
        {
            SE_CORE_INFO("Vulkan Extension: {0}", std::string(extensions[i]).c_str());    
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
            SE_CORE_INFO("Could not create Vulkan instance");
            return false;
        }

        //Check to see how many graphics card we can find, and if they work with Vulkan
        uint32_t physicalDeviceCount = 0;
        vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCount, nullptr);
        if (physicalDeviceCount == 0)
        {
            SE_CORE_INFO("No Vulkan capable GPU found");
            return false;
        }

        std::vector<VkPhysicalDevice> devices;
        devices.resize(physicalDeviceCount);
        vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCount, devices.data());
        SE_CORE_INFO("Found {0} physical devices", physicalDeviceCount); 

        //Create the Vulkan Surface
        result = glfwCreateWindowSurface(m_Instance, m_Window, nullptr, &m_Surface);
        if (result != VK_SUCCESS)
        {
            SE_CORE_INFO("Could not create Vulkan surface");
            return false;
        }

        return true;
    }

    void VulkanContext::Update()
    {
    }

    void VulkanContext::Shutdown()
    {
        SE_CORE_INFO("Terminating Vulkan Context");
        vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
        vkDestroyInstance(m_Instance, nullptr);
    }
}