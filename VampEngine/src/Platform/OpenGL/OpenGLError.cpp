#include "pch.h"
#include "OpenGLError.h"
#include "glad/glad.h"

namespace VampEngine
{
	std::string GetOpenGLStringError(GLenum error)
	{

		switch (error)
		{
			case GL_INVALID_ENUM					: return "GL_INVALID_ENUM";
			case GL_INVALID_VALUE					: return "GL_INVALID_VALUE";
			case GL_INVALID_OPERATION				: return "GL_INVALID_OPERATION";
			case GL_STACK_OVERFLOW					: return "GL_STACK_OVERFLOW";
			case GL_STACK_UNDERFLOW					: return "GL_STACK_UNDERFLOW";
			case GL_OUT_OF_MEMORY					: return "GL_OUT_OF_MEMORY";
			case GL_INVALID_FRAMEBUFFER_OPERATION	: return "GL_INVALID_FRAMEBUFFER_OPERATION";
			default									: return "Uknown Error";
		}
	}
}





void VampEngine::OpenGLClearErrors()
{
	while (glGetError());
}




void VampEngine::OpenGLLogErrors(const std::string& file, unsigned int line)
{
	GLenum error;
	bool first = true;

	//Print All the errors.
	while (error = glGetError())
	{

		//Print the following only once!!!
		if (first)
		{
			VAMP_PRINT_RED("[OpenGL Error]\n");
			VAMP_PRINT_PINK("At File: %s\n", file.c_str());
			VAMP_PRINT_PINK("At Line: %d\n", line);
			VAMP_PRINT_PINK("Errors :\n");
			first = false;
		}

		VAMP_PRINT_CYAN("\tErrno  : %d\n", error);
		VAMP_PRINT_CYAN("\tMessage: %s\n\n", GetOpenGLStringError(error).c_str());
	}

	//Leave some lines at the end.
	printf("\n\n");
}
