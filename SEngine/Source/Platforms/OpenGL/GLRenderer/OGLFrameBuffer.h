#pragma once
#include "Renderer/FrameBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace SE
{
	class OGLFrameBuffer : public FrameBuffer
	{
	public:
		bool Init(unsigned int width, unsigned int height);
		bool Resize(unsigned int width, unsigned int height);
		void Bind();
		void Unbind();
		void DrawToScreen();
		void CleanUp();

	private:
		//has all components required to draw?
		bool CheckComplete();

	private:
		//Store dimensions of the buffer
		unsigned int m_BufferWidth = 640;
		unsigned int m_BufferHeight = 480;

		//Overall framebuffer we draw to
		GLuint m_Buffer = 0;
		//Color texture we use as data storage for the framebuffer
		GLuint m_ColorTex = 0; 
		//Depth buffer stores the distance from the viewver for every pixel and 
		//ensures that only the color value nearest to the viewer will be drawn.
		GLuint m_DepthBuffer = 0; 
	};
}
