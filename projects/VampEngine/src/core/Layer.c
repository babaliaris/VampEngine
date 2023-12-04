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


VampLayer *VampNewLayer(const char *debug_name,
                        VampApplication *app,
                        VampLayerOnAttachFunc onAttach,
                        VampLayerOnDetachFunc onDetach,
                        VampLayerOnUpdateFunc onUpdate,
                        VampLayerOnEventFunc onEvent
                        )
{
    VampLayer *VAMP_MALLOC( new_layer, sizeof(VampLayer) );

    new_layer->__debug_name__   = VampNewString(debug_name);
    new_layer->__app__          = app;
    new_layer->__OnAttach__     = onAttach;
    new_layer->__OnDetach__     = onDetach;
    new_layer->__OnUpdate__     = onUpdate;
    new_layer->__OnEvent__      = onEvent;

    new_layer->GetApp           = GetApp;
    new_layer->GetDebugName     = GetDebugName;
}


void VampDestroyLayer(VampLayer *layer)
{
    VampDestroyString(layer->__debug_name__);
    VAMP_FREE(layer);
}