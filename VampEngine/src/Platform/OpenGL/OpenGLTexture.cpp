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
		VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ConvertWrap(m_props.wrap)));
		VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ConvertWrap(m_props.wrap)));
		VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ConvertFilter(m_props.filter)));
		VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertMipmapFilter(m_props.filter)));

		//Unbind The Texture.
		VAMP_GLCALL(glBindTexture(GL_TEXTURE_2D, 0));


		//Load Texture From File, if the filepath is not an empty string.
		if (!props.filepath.empty())
			this->LoadTextureFromFile();

		//Else, create an empty texture.
		else
			this->CreateEmptyTexture();
	}





	OpenGLTexture2D::OpenGLTexture2D(unsigned width, unsigned int height, TextureAttachment attachment)
		: m_id(0), m_props(width, height, attachment)
	{

		//Create and bind the texture.
		VAMP_GLCALL(glGenTextures(1, &m_id));
		VAMP_GLCALL(glBindTexture(GL_TEXTURE_2D, m_id));

		//Create Color Attachment.
		if (attachment == TextureAttachment::COLOR)
		{

			//Set the props formats.
			m_props.internalFormat = ConvertFormat(GL_RGBA);
			m_props.externalFormat = ConvertFormat(GL_RGBA);

			//Set props wrap and filter options.
			m_props.wrap	= ConvertWrap(GL_REPEAT);
			m_props.filter  = ConvertFilter(GL_LINEAR);

			//Set Wrapping and Filtering Options.
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

			//Allocate Memory for the Attachment texture.
			VAMP_GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
		}




		//Create Depth Attachment.
		else if (attachment == TextureAttachment::DEPTH)
		{

			//Set the props formats.
			m_props.internalFormat = ConvertFormat(GL_DEPTH_COMPONENT);
			m_props.externalFormat = ConvertFormat(GL_DEPTH_COMPONENT);

			//Set props wrap and filter options.
			m_props.wrap   = ConvertWrap(GL_REPEAT);
			m_props.filter = ConvertFilter(GL_LINEAR);

			//Set Wrapping and Filtering Options.
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

			//Allocate Memory for the Attachment texture.
			VAMP_GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
		}



		//Create Depth_Stencil Attachment.
		else if (attachment == TextureAttachment::DEPTH_STENCIL)
		{

			//Set the props formats.
			m_props.internalFormat = ConvertFormat(GL_DEPTH24_STENCIL8);
			m_props.externalFormat = ConvertFormat(GL_DEPTH24_STENCIL8);

			//Set props wrap and filter options.
			m_props.wrap	= ConvertWrap(GL_REPEAT);
			m_props.filter	= ConvertFilter(GL_LINEAR);

			//Set Wrapping and Filtering Options.
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			VAMP_GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

			//Allocate Memory for the Attachment texture.
			VAMP_GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL));
		}

		//Unbind The ID.
		VAMP_GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
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
		VAMP_ASSERT(size == m_props.width * m_props.height * GetFormatSize(m_props.externalFormat),
			"The size is not right!");

		//Bind.
		this->Bind();

		//Upload the data to the GPU.
		VAMP_GLCALL(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_props.width, m_props.height,
			ConvertFormat(m_props.externalFormat), GL_UNSIGNED_BYTE, data));

		//Unbind.
		this->Unbind();
	}





	void OpenGLTexture2D::UpdateAttachment(unsigned int width, unsigned int height)
	{

		//If this is an attachment.
		if (m_props.attachment != TextureAttachment::NONE)
		{
			m_props.width  = width;
			m_props.height = height;
		}


		//Update Color Attachment.
		if (m_props.attachment == TextureAttachment::COLOR)
		{
			//Re-Allocate Memory for the Attachment texture.
			VAMP_GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
		}


		//Update Depth Attachment.
		else if (m_props.attachment == TextureAttachment::DEPTH)
		{
			//Re-Allocate Memory for the Attachment texture.
			VAMP_GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
		}


		//Update Depth Attachment.
		else if (m_props.attachment == TextureAttachment::DEPTH_STENCIL)
		{
			//Re-Allocate Memory for the Attachment texture.
			VAMP_GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL));
		}
	}



	const Texture2DProps& OpenGLTexture2D::GetProps() const
	{
		return m_props;
	}

	unsigned int OpenGLTexture2D::GetID() const
	{
		return m_id;
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
		m_props.externalFormat = ConvertFormat(source_format);


		//Bind.
		this->Bind();

		//Data successfully loaded!
		if (data)
		{

			//Upload the data to the GPU.
			VAMP_GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, ConvertFormat(m_props.internalFormat), m_props.width, m_props.height,
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
		VAMP_GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, ConvertFormat(m_props.internalFormat), m_props.width, m_props.height,
			0, ConvertFormat(m_props.externalFormat), GL_UNSIGNED_BYTE, NULL));

		//Unbind.
		this->Unbind();
	}



	unsigned int ConvertFormat(TextureFormat format)
	{
		switch (format)
		{
			case VampEngine::TextureFormat::R		: return GL_R;
			case VampEngine::TextureFormat::RG		: return GL_RG;
			case VampEngine::TextureFormat::RGB		: return GL_RGB;
			case VampEngine::TextureFormat::RGBA	: return GL_RGBA;
			case VampEngine::TextureFormat::RGBA8	: return GL_RGBA8;
			case VampEngine::TextureFormat::DEPTH	: return GL_DEPTH_COMPONENT;

			case VampEngine::TextureFormat::DEPTH_STENCIL		: return GL_DEPTH24_STENCIL8;
		}

		VAMP_ASSERT(0, "Uknown TextureFormat.");
		return 0;
	}




	TextureFormat ConvertFormat(unsigned int gl_format)
	{
		switch (gl_format)
		{
			case GL_R				 : return TextureFormat::R;
			case GL_RG				 : return TextureFormat::RG;
			case GL_RGB				 : return TextureFormat::RGB;
			case GL_RGBA			 : return TextureFormat::RGBA;
			case GL_DEPTH_COMPONENT	 : return TextureFormat::DEPTH;
			case GL_DEPTH24_STENCIL8 : return TextureFormat::DEPTH_STENCIL;
		}

		VAMP_ASSERT(0, "Uknown OpenGL Texture Format.");
		return TextureFormat::NONE;
	}



	unsigned int ConvertWrap(TextureWrap wrap)
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




	TextureWrap ConvertWrap(unsigned int gl_wrap)
	{
		switch (gl_wrap)
		{
			case GL_REPEAT			: return TextureWrap::REPEAT;
			case GL_MIRRORED_REPEAT	: return TextureWrap::MIRROR_REPEAT;
			case GL_CLAMP_TO_EDGE	: return TextureWrap::CLAMP_TO_EDGE;
			case GL_CLAMP_TO_BORDER	: return TextureWrap::CLAMP_TO_BORDER;
		}

		VAMP_ASSERT(0, "Uknown TextureWrap.");
		return TextureWrap::NONE;
	}



	unsigned int ConvertFilter(TextureFilter filter)
	{
		switch (filter)
		{
			case VampEngine::TextureFilter::LINEAR : return GL_LINEAR;
			case VampEngine::TextureFilter::NEAREST: return GL_NEAREST;
		}

		VAMP_ASSERT(0, "Uknown TextureFilter.");
		return 0;
	}




	TextureFilter ConvertFilter(unsigned int gl_filter)
	{
		switch (gl_filter)
		{
			case GL_LINEAR : return TextureFilter::LINEAR;
			case GL_NEAREST: return TextureFilter::NEAREST;
		}

		VAMP_ASSERT(0, "Uknown TextureFilter.");
		return TextureFilter::NONE;
	}




	unsigned int ConvertMipmapFilter(TextureFilter filter)
	{
		switch (filter)
		{
			case VampEngine::TextureFilter::LINEAR	: return GL_LINEAR_MIPMAP_LINEAR;
			case VampEngine::TextureFilter::NEAREST	: return GL_NEAREST_MIPMAP_LINEAR;
		}

		VAMP_ASSERT(0, "Uknown TextureFilter.");
		return 0;
	}



	unsigned int GetFormatCount(TextureFormat format)
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



	unsigned int GetFormatSize(TextureFormat format)
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