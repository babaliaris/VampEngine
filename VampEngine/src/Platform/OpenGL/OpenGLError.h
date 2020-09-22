#pragma once
#include <VampLogger.h>

namespace VampEngine
{
	void OpenGLClearErrors();
	void OpenGLLogErrors(const std::string& file, unsigned int line);
}

#ifdef VAMP_DEBUG
	#define VAMP_GLCALL(code) VampEngine::OpenGLClearErrors(); code; VampEngine::OpenGLLogErrors(__FILE__, __LINE__)

#else 
	#define VAMP_GLCALL(code) code

#endif