#include "SEngine.h"
#include "Core/EntryPoint.h" 
#include "Events/KeyEvent.h"
#include "stb_image/stb_image.h"


class ExampleLayer : public SE::Layer
{
public:

	ExampleLayer()
		:
		Layer("Example")
	{
		
	}

	void OnUpdate(SE::Timestep ts) override
	{
		
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(SE::Event& e) override
	{
		SE::EventDispatcher dispatcher(e); 
		dispatcher.Dispatch<SE::KeyPressedEvent>(SE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent)); 
	}

	bool OnKeyPressedEvent(SE::KeyPressedEvent& event)
	{
		SE_INFO("Key was pressed: {}", (char)event.GetKeyCode());
		return false;
	}

private:

};

class Sandbox : public SE::Application
{
public:

	Sandbox()
	{
		PushLayer(new ExampleLayer());  
	}

	~Sandbox()
	{

	}
};

SE::Application* SE::CreateApplication()
{
	return new Sandbox(); 
}