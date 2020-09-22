#include "pch.h"
#include "RendererCommand.h"

#ifdef VAMP_OPENGL
	#include "Platform/OpenGL/OpenGLRendererCommand.h"
#endif

namespace VampEngine
{
	RendererCommand* RendererCommand::s_Instance = nullptr;

	void RendererCommand::Create()
	{
		#ifdef VAMP_OPENGL
			s_Instance =  new OpenGLRendererCommand();
		#endif
	}
}