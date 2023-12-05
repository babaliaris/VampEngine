#include <VampPCH.h>
#include "VertexArray.h"
#include <debug/MemoryTracker.h>

#ifdef VAMP_LINUX
    #include <platform/graphics/OpenGLVao.h>
#endif


#ifdef VAMP_WINDOWS
    #include <platform/graphics/OpenGLVao.h>
#endif





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

    return new_vao;
}

void VampDestroyVertexArray(VampVertexArray *this)
{
    this->__ChildDeconstructor__(this->__child__);
    VAMP_FREE(this);
}