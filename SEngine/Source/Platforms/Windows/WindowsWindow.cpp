#include "sepch.h" 
#include "WindowsWindow.h"
#include "Core/Logger.h"
#include "Renderer/RendererAPI.h"
#include "Platforms/OpenGL/OpenGLContenxt.h"
#include "Platforms/Vulkan/VulkanContext.h"
#include <GLFW/glfw3.h> 

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h" 

namespace SE
{
    SE::WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        m_Data.m_Title = props.m_Title;
        m_Data.m_Height = props.m_Height;
        m_Data.m_Width = props.m_Width;
    }

    bool SE::WindowsWindow::Init()
    {
        //Init GLFW
        if (!glfwInit())
        {
            Logger::log(1, "%s: glfwInit() error\n", __FUNCTION__);

            return false;
        }

        //Set hints based on target Graphics API
        switch (RendererAPI::GetAPI()) 
        {
            case RendererAPI::API::OpenGL:
                glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); 
                break;
            case RendererAPI::API::Vulkan:
                glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); 
                glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); 
                break;
            case RendererAPI::API::None:
                break;
        }

        //Create actual window
        m_Window = glfwCreateWindow(m_Data.m_Width, m_Data.m_Height, m_Data.m_Title.c_str(), nullptr, nullptr);

        if (!m_Window)
        {
            Logger::log(1, "%s: Could not create window\n", __FUNCTION__);
            glfwTerminate();
            return false;
        }

        //Create GraphicContext
        switch (RendererAPI::GetAPI()) 
        {
            case RendererAPI::API::OpenGL:
                m_Context = CreateScope<OpenGLContext>(m_Window); 
                break;
            case RendererAPI::API::Vulkan: 
                m_Context = CreateScope<VulkanContext>(m_Window, m_Data.m_Title); 
                break;
            case RendererAPI::API::None: 
                m_Context = nullptr;
                break;
        }

        m_Context->Init();

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
                data.m_Width = width;
                data.m_Height = height;

                WindowResizeEvent event(width, height);
                data.EventCallback(event);
            });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
            {
                WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
                WindowCloseEvent event;
                data.EventCallback(event);
            });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

                switch (action)
                {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
                default:
                    break;
                }
            });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                KeyTypedEvent event(keycode);
                data.EventCallback(event);
            });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

                switch (action)
                {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                default:
                    break;
                }
            });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
            {
                WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

                MouseScrolledEvent event((float)xOffset, (float)yOffset);
                data.EventCallback(event);
            });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

                MouseMovedEvent event((float)xPos, (float)yPos);
                data.EventCallback(event);
            });

        return true;
    }

    void WindowsWindow::Update()
    {
        while (!glfwWindowShouldClose(m_Window)) 
        { 
            /* swap buffers */
            m_Context->SwapBuffers(); 
            /* poll events in a loop */
            glfwPollEvents();
        }
    }

    void WindowsWindow::Shutdown()
    {
        Logger::log(1, "%s: Terminating Window\n", __FUNCTION__); 
        m_Context->Shutdown(); 
        glfwDestroyWindow(m_Window); 
        glfwTerminate(); 
    }

    unsigned int WindowsWindow::GetWidth() const
    {
        return m_Data.m_Width;
    }

    unsigned int WindowsWindow::GetHeight() const
    {
        return m_Data.m_Height; 
    }

    void* WindowsWindow::GetNativeWindow() const
    {
        return m_Window; 
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.m_VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.m_VSync;
    }
}