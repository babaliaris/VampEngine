#include <VampPCH.h>
#include "VertexBuffer.h"
#include <debug/MemoryTracker.h>

#ifdef VAMP_LINUX
    #include <platform/graphics/OpenGLVbo.h>
#endif


#ifdef VAMP_WINDOWS
    #include <platform/graphics/OpenGLVbo.h>
#endif





VampVertexBuffer *VampCreateVertexBuffer()
{   
    #ifdef VAMP_LINUX
    return VampNewOpenGLVbo()->__base__;
    #endif


    #ifdef VAMP_WINDOWS
    return VampNewOpenGLVbo()->__base__;
    #endif
}



VampVertexBuffer *__VampNewVertexBuffer__()
{
    VampVertexBuffer *VAMP_MALLOC(new_vbo, sizeof(VampVertexBuffer));

    new_vbo->Bind                   = NULL; //To be ovverriden.
    new_vbo->Unbind                 = NULL; //To be ovverriden.
    new_vbo->__child__              = NULL; //To be ovverriden.
    new_vbo->__ChildDeconstructor__ = NULL; //To be ovverriden.

    return new_vbo;
}

void VampDestroyVertexBuffer(VampVertexBuffer *vbo)
{
    vbo->__ChildDeconstructor__(vbo->__child__);
    VAMP_FREE(vbo);
}