#pragma once
#include "Renderer/Texture.h"

namespace VampEngine
{
	class OpenGLTexture2D : public Texture2D
	{
		//Public Methods.
		public:
			OpenGLTexture2D(const Texture2DProps& props);

		//Public Virtual Methods.
		public:

			//Virtual Destructor.
			virtual ~OpenGLTexture2D();

			//Bind and Unbind Methods.
			virtual void Bind() const override;
			virtual void Unbind() const override;

			//Upload Data Method.
			virtual void UploadData(const void* data, unsigned int size) const override;

			//Get Props Method.
			virtual const Texture2DProps& GetProps() const override;


		//Private Methods.
		private:

			void LoadTextureFromFile();
			void CreateEmptyTexture();

			unsigned int ConvertFormat(TextureFormat format) const;
			TextureFormat ConvertFormat(unsigned int gl_format) const;
			unsigned int ConvertWrap(TextureWrap wrap) const;
			unsigned int ConvertFilter(TextureFilter filter) const;
			unsigned int ConvertMipmapFilter(TextureFilter filter) const;
			unsigned int GetFormatCount(TextureFormat format) const;
			unsigned int GetFormatSize(TextureFormat format) const;


		//Private Members.
		private:
			Texture2DProps	m_props;
			unsigned int	m_id;
	};
}