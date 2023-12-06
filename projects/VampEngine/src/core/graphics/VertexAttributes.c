#include <VampPCH.h>
#include "VertexAttributes.h"
#include <debug/MemoryTracker.h>

#ifdef VAMP_LINUX
    #include <platform/opengl/OpenGLVertexAttributes.h>
#endif

#ifdef VAMP_WINDOWS
    #include <platform/opengl/OpenGLVertexAttributes.h>
#endif

VampVertexAttributes *VampCreateVertexAttributes()
{   
    #ifdef VAMP_LINUX
    return VampNewOpenGLVertexAttributes()->__base__;
    #endif


    #ifdef VAMP_WINDOWS
    return VampNewOpenGLVertexAttributes()->__base__;
    #endif
}

void VampDestroyVertexAttributes(VampVertexAttributes *va)
{
    va->__ChildDeconstructor__(va->__child__);
    VAMP_FREE(va);
}

VampVertexAttributes *__VampNewVertexAttributes__()
{
    VampVertexAttributes *VAMP_MALLOC(new_va, sizeof(VampVertexAttributes));

    new_va->Push                    = NULL; //To be ovveridden.
    new_va->Generate                = NULL; //To be ovveridden.
    new_va->__child__               = NULL; //To be ovveridden.
    new_va->__ChildDeconstructor__  = NULL; //To be ovveridden.

    return new_va;
}