#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace SE
{
	//Single vertex 
	struct OGLVertex 
	{
		glm::vec3 Position;
		glm::vec2 UVCoord; 
	};

	//Collection of vertices
	struct OGLMesh
	{
		std::vector<OGLVertex> Vertices; 
	};
}