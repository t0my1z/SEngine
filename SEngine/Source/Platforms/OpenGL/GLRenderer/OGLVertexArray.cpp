#include "sepch.h"
#include "OGLVertexArray.h"

namespace SE
{
	void OGLVertexArray::Init()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VertexVBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO); 

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OGLVertex), (void*)offsetof(OGLVertex, Position));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(OGLVertex), (void*)offsetof(OGLVertex, UVCoord));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void OGLVertexArray::UploadData(OGLMesh vertexData)
	{
		glBindVertexArray(m_VAO);  
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO); 

		glBufferData(GL_ARRAY_BUFFER, vertexData.Vertices.size() * sizeof(OGLVertex),
			&vertexData.Vertices.at(0), GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void OGLVertexArray::Bind()
	{
		glBindVertexArray(m_VAO);  
	}

	void OGLVertexArray::Unbind()
	{
		glBindVertexArray(0); 
	}

	void OGLVertexArray::Draw(GLuint mode, unsigned int start, unsigned int num)
	{
		glDrawArrays(mode, start, num); 
	}

	void OGLVertexArray::CleanUp()
	{
		glDeleteBuffers(1, &m_VertexVBO); 
		glDeleteVertexArrays(1, &m_VAO);  
	}
}