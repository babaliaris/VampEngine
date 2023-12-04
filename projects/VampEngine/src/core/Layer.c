#include <VampPCH.h>
#include "Layer.h"
#include <core/Application.h>
#include <debug/MemoryTracker.h>


static VampApplication *GetApp(VampLayer *layer)
{
    return layer->__app__;
}


VampLayer *__VampNewLayer__(VampApplication *app)
{
    VampLayer *VAMP_MALLOC( new_layer, sizeof(VampLayer) );

    new_layer->__app__                  = app;
    new_layer->__child__                = NULL;
    new_layer->__ChildDeconstructor__   = NULL;
    new_layer->__OnAttach__             = NULL;
    new_layer->__OnDetach__             = NULL;
    new_layer->__OnUpdate__             = NULL;
    new_layer->__OnEvent__              = NULL;

    new_layer->GetApp           = GetApp;
}


void VampDestroyLayer(VampLayer *layer)
{
    layer->__ChildDeconstructor__(layer->__child__);
    VAMP_FREE(layer);
}