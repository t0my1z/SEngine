#include "sepch.h" 
#include "Application.h"
#include "Timestep.h"
#include "Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace SE
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->Init(); 
		m_Window->SetEventCallback(SE_BIND_EVENT_FN(Application::OnEvent));  
	}

	Application::~Application()
	{
		m_Window->Shutdown(); 
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime(); //Platform::GetTime()    
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
				

				//m_ImGuiLayer->Begin();
				
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
				
				//m_ImGuiLayer->End();
			}

			m_Window->Update(); 
		}
	}

	void Application::OnEvent(Event& _event)
	{
		EventDispatcher dispatcher(_event);
		dispatcher.Dispatch<WindowCloseEvent>(SE_BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(SE_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(_event);
			if (_event.Handled())
				break;
		}
	}

	void Application::PushLayer(Layer* _layer)
	{
		m_LayerStack.PushLayer(_layer);
		_layer->OnAttach();
	}

	void Application::PushOverlay(Layer* _overlay)
	{
		m_LayerStack.PushOverlay(_overlay);
		_overlay->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent& _event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& _event)
	{
		if (_event.GetWidth() == 0 || _event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		//Renderer::OnWindowResize(_event.GetWidth(), _event.GetHeight());
		m_Window->GetGraphicContext()->GetRenderer()->SetSize(_event.GetWidth(), _event.GetHeight()); 

		return false;
	}
}