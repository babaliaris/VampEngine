#include <VampPCH.h>
#include "GraphicsContext.h"
#include <core/Application.h>
#include <debug/MemoryTracker.h>

#ifdef VAMP_LINUX
#include <platform/opengl/GraphicsContextGLAD.h>
#endif


#ifdef VAMP_WINDOWS
#include <platform/opengl/GraphicsContextGLAD.h>
#endif


VampGraphicsContext *VampCreateGraphicsContext(VampApplication *app)
{
    #ifdef VAMP_LINUX
    return VampNewGraphicsContextGLAD(app)->__base__;
    #endif

    #ifdef VAMP_WINDOWS
    return VampNewGraphicsContextGLAD(app)->__base__;
    #endif
}


VampGraphicsContext *__VampNewGraphicsContext__(VampApplication *app)
{
    VampGraphicsContext *VAMP_MALLOC( new_ctx, sizeof(VampGraphicsContext) );

    new_ctx->__child__                  = NULL;  //To be overridden.
    new_ctx->__child_deconstructor__    = NULL; //To be overridden.
    new_ctx->__app__                    = app;
    new_ctx->__clear_color_r            = 0;
    new_ctx->__clear_color_g            = 0;
    new_ctx->__clear_color_b            = 0;

    new_ctx->SetClearColor  = NULL; //To be overridden.
    new_ctx->ClearBuffers   = NULL; //To be overridden.

    return new_ctx;
}


void VampDestroyGraphicsContext(VampGraphicsContext *ctx)
{
    ctx->__child_deconstructor__(ctx->__child__);
    VAMP_FREE(ctx);
}