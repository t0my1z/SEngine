#pragma once
#include "Renderer/Renderer.h"

namespace SE
{
	class VulkanRenderer : public Renderer
	{
		virtual void SetSize(unsigned int width, unsigned int height) override; 
	};
}