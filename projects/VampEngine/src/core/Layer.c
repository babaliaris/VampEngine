#include <VampPCH.h>
#include "Layer.h"
#include <core/Application.h>
#include <VampString.h>
#include <debug/MemoryTracker.h>


static VampApplication *GetApp(VampLayer *layer)
{
    return layer->__app__;
}


static const char *GetDebugName(VampLayer *layer)
{
    return layer->__debug_name__->__str__;
}


VampLayer *__VampNewLayer__(const char *debug_name, VampApplication *app)
{
    VampLayer *VAMP_MALLOC( new_layer, sizeof(VampLayer) );

    new_layer->__debug_name__           = VampNewString(debug_name);
    new_layer->__app__                  = app;
    new_layer->__child__                = NULL;
    new_layer->__ChildDeconstructor__   = NULL;
    new_layer->__OnAttach__             = NULL;
    new_layer->__OnDetach__             = NULL;
    new_layer->__OnUpdate__             = NULL;
    new_layer->__OnEvent__              = NULL;

    new_layer->GetApp           = GetApp;
    new_layer->GetDebugName     = GetDebugName;
}


void VampDestroyLayer(VampLayer *layer)
{
    layer->__ChildDeconstructor__(layer->__child__);
    VampDestroyString(layer->__debug_name__);
    VAMP_FREE(layer);
}