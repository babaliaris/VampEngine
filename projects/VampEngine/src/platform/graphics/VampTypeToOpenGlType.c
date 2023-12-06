#include <VampPCH.h>
#include "VampTypeToOpenGlType.h"
#include <debug/Logger.h>
#include <core/Types.h>
#include <glad/glad.h>


unsigned int VampTypeToOpenGLType(unsigned int type)
{
    switch (type)
    {
        case VAMP_TYPES_INT32:
            return GL_INT;

        case VAMP_TYPES_INT64:
            return GL_INT;

        case VAMP_TYPES_FLOAT32:
            return GL_FLOAT;

        case VAMP_TYPES_FLOAT64:
            return GL_FLOAT;

        case VAMP_TYPES_UNSIGNED_INT:
            return GL_UNSIGNED_INT;
        
        default:
        {
            VAMP_WARN("Uknown VAMP_TYPE: %d", type);
            return 0;
        }
    }
}


unsigned int VampGetOpenGLTypeSize(unsigned int type)
{
    switch (type)
    {
        case GL_INT:
            return sizeof(int);

        case GL_FLOAT:
            return sizeof(float);

        case GL_UNSIGNED_INT:
            return sizeof(unsigned int);

        default:
        {
            VAMP_WARN("Uknown OpenGL Type: %d", type);
            return 0;
        }
    }
}