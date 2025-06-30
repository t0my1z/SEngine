#pragma once
#include <string> 
#include "Timestep.h"
#include "Events/Event.h"

namespace SE
{
	class Layer
	{
	public:

		Layer(const std::string& InName = "Layer")
			: m_Name(InName)
		{

		}

		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {} 
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& _event) {} 

		inline const std::string& GetName() const { return m_Name; } 

	private:
		std::string m_Name;
	};
}