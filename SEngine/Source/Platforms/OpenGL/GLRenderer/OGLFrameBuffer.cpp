#include "sepch.h"
#include "OGLFrameBuffer.h"

namespace SE
{
	bool OGLFrameBuffer::Init(unsigned int width, unsigned int height)
	{
		m_BufferWidth = width;
		m_BufferHeight = height;

		glGenFramebuffers(1, &m_Buffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Buffer); 

		{	//Create a 2D texture and set all the parameters it needs
			glGenTextures(1, &m_ColorTex);
			glBindTexture(GL_TEXTURE_2D, m_ColorTex);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			//Downscaling the texture if draw far away, or upscaling if its close
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//What happens when we draw outside the defined are of the texture
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		//Bind the created texture to the created framebuffer
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_ColorTex, 0); 
		
		{	//Create a RenderBuffer
			glGenRenderbuffers(1, &m_DepthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer); 
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height); 
		}

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer); 

		glBindRenderbuffer(GL_RENDERBUFFER, 0); 
		glBindFramebuffer(GL_FRAMEBUFFER, 0); 

		return CheckComplete(); 
	}

	bool OGLFrameBuffer::Resize(unsigned int width, unsigned int height)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glDeleteTextures(1, &m_ColorTex);
		glDeleteRenderbuffers(1, &m_DepthBuffer);
		glDeleteFramebuffers(1, &m_Buffer);;
		return Init(width, height); 
	}

	void OGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Buffer);  
	}

	void OGLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); 
	}

	void OGLFrameBuffer::DrawToScreen()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Buffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); 
		glBlitFramebuffer(0, 0, m_BufferWidth, m_BufferHeight, 0, 0, 
			m_BufferWidth, m_BufferHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0); 
	}

	void OGLFrameBuffer::CleanUp()
	{
		Unbind();
		glDeleteTextures(1, &m_ColorTex);  
		glDeleteRenderbuffers(1, &m_DepthBuffer); 
		glDeleteFramebuffers(1, &m_Buffer);; 
	}

	bool OGLFrameBuffer::CheckComplete()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Buffer); 
		GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER); 
		if (result != GL_FRAMEBUFFER_COMPLETE)
		{
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0); 
		return true; 
	}
}