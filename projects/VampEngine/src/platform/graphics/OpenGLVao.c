#include <VampPCH.h>
#include "OpenGLVao.h"
#include <core/graphics/VertexArray.h>
#include <debug/MemoryTracker.h>
#include <glad/glad.h>
#include "debug/OpenGLCall.h"


static void Bind(VampVertexArray *base)
{
    VampOpenGLVao *this = (VampOpenGLVao *)base->__child__;
    VAMP_GLCALL(glBindVertexArray(this->__id__));
}


static void Unbind(VampVertexArray *base)
{
    VAMP_GLCALL(glBindVertexArray(0));
}


static void Deconstructor(void *this)
{
    VampOpenGLVao *t = (VampOpenGLVao *)this;
    VampDestroyOpenGLVao(t);
}


VampOpenGLVao *VampNewOpenGLVao()
{
    VampVertexArray *new_vao = __VampNewVertexArray__();

    VampOpenGLVao *VAMP_MALLOC(new_OpenGLVao, sizeof(VampOpenGLVao));

    new_vao->__child__              = new_OpenGLVao;
    new_vao->__ChildDeconstructor__ = Deconstructor;
    new_vao->Bind                   = Bind;
    new_vao->Unbind                 = Unbind;

    new_OpenGLVao->__base__ = new_vao;
    new_OpenGLVao->__id__   = 0;

    VAMP_GLCALL(glGenVertexArrays(1, &new_OpenGLVao->__id__));

    return new_OpenGLVao;
}

void VampDestroyOpenGLVao(VampOpenGLVao *glVao)
{
    VAMP_GLCALL(glDeleteVertexArrays(1, &glVao->__id__));
    VAMP_FREE(glVao);
}