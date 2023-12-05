#include <VampPCH.h>
#include "OpenGLVbo.h"
#include <core/graphics/VertexBuffer.h>
#include <debug/MemoryTracker.h>
#include <glad/glad.h>
#include "debug/OpenGLCall.h"


static void Bind(VampVertexBuffer *base)
{
    VampOpenGLVbo *this = (VampOpenGLVbo *)base->__child__;
    VAMP_GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->__id__));
}


static void Unbind(VampVertexBuffer *base)
{
    VAMP_GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


static void Deconstructor(void *this)
{
    VampOpenGLVbo *t = (VampOpenGLVbo *)this;
    VampDestroyOpenGLVbo(t);
}


VampOpenGLVbo *VampNewOpenGLVbo()
{
    VampVertexBuffer *new_vbo = __VampNewVertexBuffer__();

    VampOpenGLVbo *VAMP_MALLOC(new_OpenGLVbo, sizeof(VampOpenGLVbo));

    new_vbo->__child__              = new_OpenGLVbo;
    new_vbo->__ChildDeconstructor__ = Deconstructor;
    new_vbo->Bind                   = Bind;
    new_vbo->Unbind                 = Unbind;

    new_OpenGLVbo->__base__ = new_vbo;
    new_OpenGLVbo->__id__   = 0;

    VAMP_GLCALL(glGenBuffers(1, &new_OpenGLVbo->__id__));

    return new_OpenGLVbo;
}

void VampDestroyOpenGLVbo(VampOpenGLVbo *glVbo)
{
    VAMP_GLCALL(glDeleteBuffers(1, &glVbo->__id__));
    VAMP_FREE(glVbo);
}