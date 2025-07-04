#include "sepch.h"
#include "OGLTexture.h"
#include "stb_image.h"


namespace SE
{
	bool OGLTexture::LoadTexture(std::string TexturePath)
	{
		int TexWidth, TexHeight, NumberOfChannels; 

		stbi_set_flip_vertically_on_load(true); 
		unsigned char* textureData = stbi_load(TexturePath.c_str(), &TexWidth, &TexHeight, &NumberOfChannels, 0); 

		if (!textureData) 
		{
			SE_CORE_INFO("{0} error: could not load file {1}", TexturePath.c_str(), TexturePath.c_str()); 
			stbi_image_free(textureData); 
			return false; 
		}

		glGenTextures(1, &m_Texture); 
		glBindTexture(GL_TEXTURE_2D, m_Texture); 

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TexWidth, TexHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData); 
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(textureData);

		SE_CORE_INFO("{0}: texture loaded. Width: {1}, Height: {2}, NumOfChannels: {3}", 
			TexturePath, TexWidth, TexHeight, NumberOfChannels);  

		return true;
	}

	void OGLTexture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_Texture); 
	}

	void OGLTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0); 
	}

	void OGLTexture::CleanUp()
	{
		glDeleteTextures(1, &m_Texture);  
	}
}