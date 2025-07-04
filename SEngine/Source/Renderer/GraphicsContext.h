#pragma once
#include "Core/Core.h"
#include "Renderer/Renderer.h"

namespace SE
{
	class GraphicsContext
	{
	public:

		virtual bool Init(unsigned int width, unsigned int height) = 0;
		virtual void Update() = 0;  
		virtual void Shutdown() {} 
		virtual Renderer* GetRenderer() const = 0; 
	};
}