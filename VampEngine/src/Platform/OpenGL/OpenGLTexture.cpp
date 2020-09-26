#include "pch.h"
#include "VampAssert.h"
#include "OpenGLTexture.h"
#include "OpenGLError.h"
#include <glad/glad.h>
#include <stb_image/stb_image.h>

namespace VampEngine
{
	OpenGLTexture2D::OpenGLTexture2D(const Texture2DProps& props)
		: m_props(props), m_id(0)
	{

		//Set the flipping.
		stbi_set_flip_vertically_on_load(m_props.flipped ? 1 : 0);

		//Generate an Open GL Texture.
		VAMP_GLCALL(glGenTextures(1, &m_id));

		//Bind The Texture.
		VAMP_GLCALL(glBindTexture(GL_TEXTURE_2D, m_id));

		//Set Wrapping and Filtering Options.
		VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->ConvertWrap(m_props.wrap)));
		VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->ConvertWrap(m_props.wrap)));
		VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->ConvertFilter(m_props.filter)));
		VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->ConvertMipmapFilter(m_props.filter)));

		//Unbind The Texture.
		VAMP_GLCALL(glBindTexture(GL_TEXTURE_2D, 0));


		//Load Texture From File, if the filepath is not an empty string.
		if (!props.filepath.empty())
			this->LoadTextureFromFile();

		//Else, create an empty texture.
		else
			this->CreateEmptyTexture();
	}



	OpenGLTexture2D::~OpenGLTexture2D()
	{
		VAMP_GLCALL(glDeleteTextures(1, &m_id));
	}



	void OpenGLTexture2D::Bind() const
	{
		VAMP_GLCALL(glBindTexture(GL_TEXTURE_2D, m_id));
	}



	void OpenGLTexture2D::Unbind() const
	{
		VAMP_GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
	}



	void OpenGLTexture2D::UploadData(const void* data, unsigned int size) const
	{

		//Assert size with the actual texture size.
		VAMP_ASSERT(size == m_props.width * m_props.height * this->GetFormatSize(m_props.externalFormat),
			"The size is not right!");

		//Bind.
		this->Bind();

		//Upload the data to the GPU.
		VAMP_GLCALL(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_props.width, m_props.height,
			this->ConvertFormat(m_props.externalFormat), GL_UNSIGNED_BYTE, data));

		//Unbind.
		this->Unbind();
	}



	const Texture2DProps& OpenGLTexture2D::GetProps() const
	{
		return m_props;
	}



	void OpenGLTexture2D::LoadTextureFromFile()
	{
		//Load the Texture from the image file.
		int width, height, channels;
		unsigned char* data = stbi_load(m_props.filepath.c_str(), &width, &height, &channels, 0);
		VAMP_ASSERT(data, "[LoadTextureFromFile] => File could not open: %s", m_props.filepath.c_str());

		//Set the width and the height.
		m_props.width  = width;
		m_props.height = height;

		//Detect the source format.
		unsigned int source_format = GL_RGB;
		switch (channels)
		{
			case 1:
				source_format = GL_R;
				break;

			case 2:
				source_format = GL_RG;
				break;

			case 3:
				source_format = GL_RGB;
				break;

			case 4:
				source_format = GL_RGBA;
				break;

			default:
			{
				VAMP_ASSERT(0, "Unsupported Format.");
				break;
			}
		}


		//Override the external format with the actual format of the texture file image.
		m_props.externalFormat = this->ConvertFormat(source_format);


		//Bind.
		this->Bind();

		//Data successfully loaded!
		if (data)
		{

			//Upload the data to the GPU.
			VAMP_GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, this->ConvertFormat(m_props.internalFormat), m_props.width, m_props.height,
				0, source_format, GL_UNSIGNED_BYTE, data));


			//Generate Mipmaps.
			VAMP_GLCALL(glGenerateMipmap(GL_TEXTURE_2D));

			//Free the image from the RAM.
			stbi_image_free(data);
		}

		//Unbind.
		this->Unbind();
	}



	void OpenGLTexture2D::CreateEmptyTexture()
	{

		//Bind.
		this->Bind();

		//Allocate memory in the GPU.
		VAMP_GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, this->ConvertFormat(m_props.internalFormat), m_props.width, m_props.height,
			0, this->ConvertFormat(m_props.externalFormat), GL_UNSIGNED_BYTE, NULL));

		//Unbind.
		this->Unbind();
	}



	unsigned int OpenGLTexture2D::ConvertFormat(TextureFormat format) const
	{
		switch (format)
		{
			case VampEngine::TextureFormat::R		: return GL_R;
			case VampEngine::TextureFormat::RG		: return GL_RG;
			case VampEngine::TextureFormat::RGB		: return GL_RGB;
			case VampEngine::TextureFormat::RGBA	: return GL_RGBA;
			case VampEngine::TextureFormat::RGBA8	: return GL_RGBA8;
		}

		VAMP_ASSERT(0, "Uknown TextureFormat.");
		return 0;
	}




	TextureFormat OpenGLTexture2D::ConvertFormat(unsigned int gl_format) const
	{
		switch (gl_format)
		{
			case GL_R	: return TextureFormat::R;
			case GL_RG	: return TextureFormat::RG;
			case GL_RGB	: return TextureFormat::RGB;
			case GL_RGBA: return TextureFormat::RGBA;
		}

		VAMP_ASSERT(0, "Uknown OpenGL Texture Format.");
		return TextureFormat::NONE;
	}



	unsigned int OpenGLTexture2D::ConvertWrap(TextureWrap wrap) const
	{
		switch (wrap)
		{
			case VampEngine::TextureWrap::REPEAT			: return GL_REPEAT;
			case VampEngine::TextureWrap::MIRROR_REPEAT		: return GL_MIRRORED_REPEAT;
			case VampEngine::TextureWrap::CLAMP_TO_EDGE		: return GL_CLAMP_TO_EDGE;
			case VampEngine::TextureWrap::CLAMP_TO_BORDER	: return GL_CLAMP_TO_BORDER;
		}

		VAMP_ASSERT(0, "Uknown TextureWrap.");
		return 0;
	}



	unsigned int OpenGLTexture2D::ConvertFilter(TextureFilter filter) const
	{
		switch (filter)
		{
			case VampEngine::TextureFilter::LINEAR : return GL_LINEAR;
			case VampEngine::TextureFilter::NEAREST: return GL_NEAREST;
		}

		VAMP_ASSERT(0, "Uknown TextureFilter.");
		return 0;
	}




	unsigned int OpenGLTexture2D::ConvertMipmapFilter(TextureFilter filter) const
	{
		switch (filter)
		{
			case VampEngine::TextureFilter::LINEAR	: return GL_LINEAR_MIPMAP_LINEAR;
			case VampEngine::TextureFilter::NEAREST	: return GL_NEAREST_MIPMAP_LINEAR;
		}

		VAMP_ASSERT(0, "Uknown TextureFilter.");
		return 0;
	}



	unsigned int OpenGLTexture2D::GetFormatCount(TextureFormat format) const
	{
		switch (format)
		{
			case VampEngine::TextureFormat::R: return 1;
			case VampEngine::TextureFormat::RG: return 2;
			case VampEngine::TextureFormat::RGB: return 3;
			case VampEngine::TextureFormat::RGBA: return 4;
			case VampEngine::TextureFormat::RGBA8: return 4;
		}

		VAMP_ASSERT(0, "Uknown TextureFormat.");
		return 0;
	}



	unsigned int OpenGLTexture2D::GetFormatSize(TextureFormat format) const
	{
		switch (format)
		{
			case VampEngine::TextureFormat::R: return 1;
			case VampEngine::TextureFormat::RG: return 2;
			case VampEngine::TextureFormat::RGB: return 3;
			case VampEngine::TextureFormat::RGBA: return 4;
			case VampEngine::TextureFormat::RGBA8: return 4;
		}

		VAMP_ASSERT(0, "Uknown TextureFormat.");
		return 0;
	}
}