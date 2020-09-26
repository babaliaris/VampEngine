#include "pch.h"
#include "Texture.h"

//Include OpenGL.
#ifdef VAMP_OPENGL
	#include "Platform/OpenGL/OpenGLTexture.h"
#endif


namespace VampEngine
{
	Texture2D* VampEngine::Texture2D::CreateTexture2D(const Texture2DProps& props)
	{
		//Include OpenGL.
		#ifdef VAMP_OPENGL
			return new OpenGLTexture2D(props);
		#endif
	}



	Texture2DProps::Texture2DProps(const std::string& path)
		: filepath(path), width(0), height(0), samples(0), flipped(true), internalFormat(TextureFormat::RGBA8),
		externalFormat(TextureFormat::NONE), wrap(TextureWrap::REPEAT), filter(TextureFilter::LINEAR)
	{
	}



	Texture2DProps::Texture2DProps(const std::string& path, bool flip)
		: filepath(path), width(0), height(0), samples(0), flipped(flip), internalFormat(TextureFormat::RGBA8),
		externalFormat(TextureFormat::NONE), wrap(TextureWrap::REPEAT), filter(TextureFilter::LINEAR)
	{
	}



	Texture2DProps::Texture2DProps(unsigned int width, unsigned int height)
		: width(width), height(height), samples(0), flipped(true), internalFormat(TextureFormat::RGBA8),
		externalFormat(TextureFormat::NONE), wrap(TextureWrap::REPEAT), filter(TextureFilter::LINEAR)
	{
	}
}