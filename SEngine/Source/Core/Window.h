#pragma once
#include <string>
#include "Core.h"
#include "Events/Event.h"
#include "Renderer/GraphicsContext.h"


namespace SE
{
	struct WindowProps
	{
		WindowProps(const std::string& _title = "SEngine",
			unsigned int _width = 1280,
			unsigned int _height = 720)
			: m_Title(_title), m_Width(_width), m_Height(_height)
		{

		}

		std::string m_Title;
		unsigned int m_Width;
		unsigned int m_Height;
	};

	class Window
	{
	public:

		using EventCallbackFn = std::function<void(Event&)>; 

		virtual ~Window() {}

		virtual bool Init() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& _callback) = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual GraphicsContext* GetGraphicContext() const = 0;

		//Gets implemented per platform, in their respective cpp
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}