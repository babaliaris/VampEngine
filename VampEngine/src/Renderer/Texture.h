#pragma once
#include <string>

namespace VampEngine
{

	enum class TextureFormat
	{
		NONE,
		R, RG, RGB, RGBA, RGBA8,
		DEPTH, DEPTH_STENCIL
	};


	enum class TextureWrap
	{
		NONE,
		REPEAT, MIRROR_REPEAT, CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
	};


	enum class TextureFilter
	{
		NONE,
		LINEAR, NEAREST
	};


	enum class TextureAttachment
	{
		NONE,
		COLOR, DEPTH, DEPTH_STENCIL
	};




	struct Texture2DProps
	{
		std::string		filepath;
		unsigned int	width;
		unsigned int	height;
		bool			flipped;
		TextureFormat	internalFormat;
		TextureFormat	externalFormat;
		TextureWrap		wrap;
		TextureFilter	filter;
		TextureAttachment attachment;

		Texture2DProps(const std::string& path);
		Texture2DProps(const std::string& path, bool flip);
		Texture2DProps(unsigned int width, unsigned int height);
		Texture2DProps(unsigned int width, unsigned int height, TextureAttachment attachment);
	};





	class Texture2D
	{
		//Public Static Methods.
		public:

			static Texture2D* Create(const Texture2DProps& props);
			static Texture2D* CreateAttachment(unsigned width, unsigned int height, TextureAttachment attachment);

		//Public Virtual Methods.
		public:

			//Virtual Destructor.
			virtual ~Texture2D() = default;

			//Bind and Unbind Methods.
			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			//Upload Data Method.
			virtual void UploadData(const void* data, unsigned int size) const = 0;

			//Update Attachment Method.
			virtual void UpdateAttachment(unsigned int width, unsigned int height) = 0;

			//Get Props Method.
			virtual const Texture2DProps& GetProps() const = 0;

			//Get ID Method.
			virtual unsigned int GetID() const = 0;
	};
}