#pragma once
#include <string>

namespace VampEngine
{

	enum class TextureFormat
	{
		NONE,
		R, RG, RGB, RGBA, RGBA8
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




	struct Texture2DProps
	{
		std::string		filepath;
		unsigned int	width;
		unsigned int	height;
		unsigned int	samples;
		bool			flipped;
		TextureFormat	internalFormat;
		TextureFormat	externalFormat;
		TextureWrap		wrap;
		TextureFilter	filter;

		Texture2DProps(const std::string& path);
		Texture2DProps(const std::string& path, bool flip);
		Texture2DProps(unsigned int width, unsigned int height);
	};





	class Texture2D
	{
		//Public Static Methods.
		public:

			static Texture2D* CreateTexture2D(const Texture2DProps& props);

		//Public Virtual Methods.
		public:

			//Virtual Destructor.
			virtual ~Texture2D() = default;

			//Bind and Unbind Methods.
			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			//Upload Data Method.
			virtual void UploadData(const void* data, unsigned int size) const = 0;

			//Get Props Method.
			virtual const Texture2DProps& GetProps() const = 0;
	};
}