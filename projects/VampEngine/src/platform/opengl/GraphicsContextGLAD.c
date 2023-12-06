#include <VampPCH.h>
#include "GraphicsContextGLAD.h"
#include <core/Application.h>
#include <core/graphics/GraphicsContext.h>
#include <debug/MemoryTracker.h>
#include <debug/Logger.h>
#include <glad/glad.h>

static void ClearBuffers(VampGraphicsContext *base)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

static void SetClearColor(VampGraphicsContext *base, float r, float g, float b)
{
    base->__clear_color_r = r;
    base->__clear_color_g = g;
    base->__clear_color_b = b;

    glClearColor(r, g, b, 1.0f);
}

static void Deconstructor(void *this)
{
    VampDestroyGraphicsContextGLAD( (VampGraphicsContextGLAD *)this );
}


void VampInitGraphicsContext(void *data)
{
    if ( !gladLoadGLLoader((GLADloadproc)data) )
    {
        VAMP_ERROR("GLAD failed to be initialized. Please make sure you have the latest GPU drivers installed.");
        
        #ifndef VAMP_DEBUG
        printf("[ERROR]: GLAD failed to be initialized. Please make sure you have the latest GPU drivers installed.\n");
        #endif
    }
}

VampGraphicsContextGLAD *VampNewGraphicsContextGLAD(VampApplication *app)
{
    VampGraphicsContext *new_graphics_context = __VampNewGraphicsContext__(app);

    VampGraphicsContextGLAD *VAMP_MALLOC( new_ctxGLAD, sizeof(VampGraphicsContextGLAD) );

    new_graphics_context->ClearBuffers              = ClearBuffers;
    new_graphics_context->SetClearColor             = SetClearColor;
    new_graphics_context->__child__                 = new_ctxGLAD;
    new_graphics_context->__child_deconstructor__   = Deconstructor;

    new_ctxGLAD->__base__ = new_graphics_context;

    return new_ctxGLAD;

}

void VampDestroyGraphicsContextGLAD(VampGraphicsContextGLAD *ctxGLAD)
{
    VAMP_FREE(ctxGLAD);
}