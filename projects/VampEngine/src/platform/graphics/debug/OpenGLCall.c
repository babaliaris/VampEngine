#include <VampPCH.h>
#include "OpenGLCall.h"
#include <debug/Logger.h>
#include <glad/glad.h>


static const char *GetErrorMeaning(unsigned int error)
{
    switch (error)
    {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";

        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";

        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";

        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        
        default:
            return "GL_NO_ERROR";
    }
}



void __VampOpenGLCrearAllErrors__()
{
    while (glGetError() != GL_NO_ERROR);
}


void __VampOpenGLRetrieveErrors__()
{
    GLenum error;
    while ( (error = glGetError()) != GL_NO_ERROR)
    {
        VAMP_ERROR("[OpenGL Error: %d] %s", error, GetErrorMeaning(error));
    }
}
