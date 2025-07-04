#include "sepch.h"
#include "OGLModel.h"

namespace SE
{
	void OGLModel::Init()
	{
		m_VertexData.Vertices.resize(6);

		m_VertexData.Vertices[0].Position = glm::vec3(-0.5f, -0.5f, 0.5f);
		m_VertexData.Vertices[1].Position = glm::vec3(0.5f, 0.5f, 0.5f);
		m_VertexData.Vertices[2].Position = glm::vec3(-0.5f, 0.5f, 0.5f);
		m_VertexData.Vertices[3].Position = glm::vec3(-0.5f, -0.5f, 0.5f);
		m_VertexData.Vertices[4].Position = glm::vec3(0.5f, -0.5f, 0.5f);
		m_VertexData.Vertices[5].Position = glm::vec3(0.5f, 0.5f, 0.5f);

		m_VertexData.Vertices[0].UVCoord = glm::vec2(0.0, 0.0);
		m_VertexData.Vertices[1].UVCoord = glm::vec2(1.0, 1.0);
		m_VertexData.Vertices[2].UVCoord = glm::vec2(0.0, 1.0);
		m_VertexData.Vertices[3].UVCoord = glm::vec2(0.0, 0.0);
		m_VertexData.Vertices[4].UVCoord = glm::vec2(1.0, 0.0);
		m_VertexData.Vertices[5].UVCoord = glm::vec2(1.0, 1.0);
	}

	OGLMesh OGLModel::GetVertexData()
	{
		return m_VertexData;  
	}
}