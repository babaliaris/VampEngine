#include <VampPCH.h>
#include "VertexArray.h"
#include <debug/MemoryTracker.h>
#include <core/graphics/VertexBuffer.h>

#ifdef VAMP_LINUX
    #include <platform/opengl/OpenGLVao.h>
#endif


#ifdef VAMP_WINDOWS
    #include <platform/opengl/OpenGLVao.h>
#endif



static void AddVertexBuffer(VampVertexArray *this, VampVertexBuffer *vbo)
{
    this->__buffer__ = vbo;
}





VampVertexArray *VampCreateVertexArray()
{   
    #ifdef VAMP_LINUX
    return VampNewOpenGLVao()->__base__;
    #endif


    #ifdef VAMP_WINDOWS
    return VampNewOpenGLVao()->__base__;
    #endif
}



VampVertexArray *__VampNewVertexArray__()
{
    VampVertexArray *VAMP_MALLOC(new_vao, sizeof(VampVertexArray));

    new_vao->Bind                   = NULL; //To be ovverriden.
    new_vao->Unbind                 = NULL; //To be ovverriden.
    new_vao->__child__              = NULL; //To be ovverriden.
    new_vao->__ChildDeconstructor__ = NULL; //To be ovverriden.

    new_vao->__buffer__             = NULL;
    new_vao->AddVertexBuffer        = AddVertexBuffer;

    return new_vao;
}

void VampDestroyVertexArray(VampVertexArray *vao)
{
    vao->__ChildDeconstructor__(vao->__child__);

    VampDestroyVertexBuffer(vao->__buffer__);
    VAMP_FREE(vao);
}