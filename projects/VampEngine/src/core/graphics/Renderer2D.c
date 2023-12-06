#include <VampPCH.h>
#include "Renderer2D.h"
#include <debug/MemoryTracker.h>
#include <core/graphics/VertexArray.h>
#include <core/graphics/VertexBuffer.h>
#include <core/graphics/VertexAttributes.h>
#include <core/graphics/Shader.h>
#include <data-structures/list.h>

#ifdef VAMP_LINUX
    #include <platform/opengl/OpenGLRenderer2D.h>
#endif

#ifdef VAMP_WINDOWS
    #include <platform/opengl/OpenGLRenderer2D.h>
#endif


static void PushDrawData(VampRenderer2D *this, VampVertexArray *vao, VampShader *shader)
{
    this->__list__->Append(this->__list__, VampNewRendererData2D(vao, shader));
}


static void DrawAllArrays(VampRenderer2D *this)
{
    for (unsigned int i = 0; i < this->__list__->__length__; i++)
    {
        VampRendererData2D *data2D = (VampRendererData2D *)this->__list__->GetAt(this->__list__, i);

        this->DrawArrays(this, data2D);
    }
}


static void Data2DListDeconstructor(void *data)
{
    VampRendererData2D *d = (VampRendererData2D *)data;
    VampDestroyRendererData2D(d);
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

    VampDestroyList(renderer2D->__list__, Data2DListDeconstructor);

    VAMP_FREE(renderer2D);
}


VampRendererData2D *VampNewRendererData2D(VampVertexArray *vao, VampShader *shader)
{
    VampRendererData2D *VAMP_MALLOC(new_data, sizeof(VampRendererData2D));

    new_data->__vao__       = vao;
    new_data->__shader__    = shader;

    return new_data;
}

void VampDestroyRendererData2D(VampRendererData2D *data2D)
{
    VampDestroyVertexArray(data2D->__vao__);
    VampDestroyShader(data2D->__shader__);
    VAMP_FREE(data2D);
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