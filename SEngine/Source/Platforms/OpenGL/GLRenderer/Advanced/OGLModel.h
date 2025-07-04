#pragma once
#include "Renderer/Advanced/Model.h"
#include <vector>
#include <glm/glm.hpp>
#include "Platforms/OpenGL/GLRenderer/OGLRenderData.h"

namespace SE
{
	class OGLModel : public Model 
	{
	public:
		void Init();
		OGLMesh GetVertexData(); 

	private:
		OGLMesh m_VertexData;
	};
}
