#include <VampPCH.h>
#include "Renderer2D.h"
#include <debug/MemoryTracker.h>
#include <data-structures/list.h>
#include <core/graphics/Mesh.h>

#ifdef VAMP_LINUX
    #include <platform/opengl/OpenGLRenderer2D.h>
#endif

#ifdef VAMP_WINDOWS
    #include <platform/opengl/OpenGLRenderer2D.h>
#endif


static void PushDrawData(VampRenderer2D *this, VampMesh *mesh)
{
    this->__list__->Append(this->__list__, mesh);
}


static void DrawAllArrays(VampRenderer2D *this)
{
    for (unsigned int i = 0; i < this->__list__->__length__; i++)
    {
        VampMesh *mesh = (VampMesh *)this->__list__->GetAt(this->__list__, i);

        this->DrawArrays(this, mesh);
    }
}


static void MeshDeconstructor(void *data)
{
    VampMesh *mesh = (VampMesh *)data;
    VampDestroyMesh(mesh);
}



VampRenderer2D *VampCreateRenderer2D()
{   
    #ifdef VAMP_LINUX
    return VampNewOpenGLRenderer2D()->__base__;
    #endif

    #ifdef VAMP_WINDOWS
    return VampNewOpenGLRenderer2D()->__base__;
    #endif
}


void VampDestroyRenderer2D(VampRenderer2D *renderer2D)
{
    renderer2D->__ChildDeconstructor__(renderer2D->__child__);

    VampDestroyList(renderer2D->__list__, MeshDeconstructor);

    VAMP_FREE(renderer2D);
}




VampRenderer2D *__VampNewRenderer2D__()
{
    VampRenderer2D *VAMP_MALLOC(new_renderer2d, sizeof(VampRenderer2D));

    new_renderer2d->PushDrawData    = PushDrawData;
    new_renderer2d->__list__        = VampNewList();
    new_renderer2d->DrawAllArrays   = DrawAllArrays;

    new_renderer2d->__child__               = NULL; //To be ovverriden.
    new_renderer2d->__ChildDeconstructor__  = NULL; //To be ovverriden.
    new_renderer2d->DrawArrays              = NULL; //To be ovverriden.

    return new_renderer2d;
}