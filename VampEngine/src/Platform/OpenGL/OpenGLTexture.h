#pragma once
#include "Renderer/Texture.h"

namespace VampEngine
{

	unsigned int ConvertFormat(TextureFormat format);
	TextureFormat ConvertFormat(unsigned int gl_format);

	unsigned int ConvertWrap(TextureWrap wrap);
	TextureWrap ConvertWrap(unsigned int gl_wrap);

	unsigned int ConvertFilter(TextureFilter filter);
	TextureFilter ConvertFilter(unsigned int gl_filter);

	unsigned int ConvertMipmapFilter(TextureFilter filter);
	unsigned int GetFormatCount(TextureFormat format);
	unsigned int GetFormatSize(TextureFormat format);


	class OpenGLTexture2D : public Texture2D
	{
		//Public Methods.
		public:
			OpenGLTexture2D(const Texture2DProps& props);
			OpenGLTexture2D(unsigned width, unsigned int height, TextureAttachment attachment);

		//Public Virtual Methods.
		public:

			//Virtual Destructor.
			virtual ~OpenGLTexture2D();

			//Bind and Unbind Methods.
			virtual void Bind() const override;
			virtual void Unbind() const override;

			//Upload Data Method.
			virtual void UploadData(const void* data, unsigned int size) const override;

			//Update Attachment Method.
			virtual void UpdateAttachment(unsigned int width, unsigned int height) override;

			//Get Props Method.
			virtual const Texture2DProps& GetProps() const override;

			//Get ID Method.
			virtual unsigned int GetID() const override;


		//Private Methods.
		private:

			void LoadTextureFromFile();
			void CreateEmptyTexture();


		//Private Members.
		private:
			Texture2DProps	m_props;
			unsigned int	m_id;
	};
}