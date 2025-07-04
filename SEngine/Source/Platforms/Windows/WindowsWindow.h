#pragma once
#include "Core/Window.h"
#include "Core/Core.h"

struct GLFWwindow; 

namespace SE
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props); 

		virtual bool Init();
		virtual void Update();
		virtual void Shutdown();

		virtual unsigned int GetWidth() const;
		virtual unsigned int GetHeight() const;

		virtual void* GetNativeWindow() const;
		virtual void SetEventCallback(const EventCallbackFn& _callback) override { m_Data.EventCallback = _callback; }

		virtual void SetVSync(bool enabled);
		virtual bool IsVSync() const;

		virtual GraphicsContext* GetGraphicContext() const override;

	private:
		GLFWwindow* m_Window = nullptr; 
		Scope<GraphicsContext> m_GraphicContext; 

		struct WindowData
		{
			std::string m_Title = "";
			unsigned int m_Width = 0;
			unsigned int m_Height = 0;
			bool m_VSync = true;

			EventCallbackFn EventCallback; 
		};

		WindowData m_Data;
	};
}
