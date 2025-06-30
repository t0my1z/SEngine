#include "sepch.h" 
#include "Window.h"
#include "Platforms/Windows/WindowsWindow.h"

namespace SE
{
    Scope<Window> Window::Create(const WindowProps& props)
    {
		return CreateScope<WindowsWindow>(props);
    }
}