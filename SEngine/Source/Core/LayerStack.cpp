#include "sepch.h" 
#include "LayerStack.h"

SE::LayerStack::LayerStack()
{
}

SE::LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
		delete layer;
}

void SE::LayerStack::PushLayer(Layer* _layer)
{
	m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, _layer);
	++m_LayerInsertIndex;
}

void SE::LayerStack::PushOverlay(Layer* _overlay)
{
	m_Layers.emplace_back(_overlay);
}

void SE::LayerStack::PopLayer(Layer* _layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), _layer);
	if (it != m_Layers.end())
	{
		_layer->OnDetach();
		m_Layers.erase(it);
		m_LayerInsertIndex--;
	}
}

void SE::LayerStack::PopOverlay(Layer* _overlay)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), _overlay);
	if (it != m_Layers.end())
	{
		_overlay->OnDetach();
		m_Layers.erase(it);
	}
}
