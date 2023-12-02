#include <VampPCH.h>

#define VAMP_LOGGER_INIT
#define VAMP_MEMORY_TRACKER_INIT

#include <debug/Logger.h>
#include <debug/MemoryTracker.h>
#include "Application.h"
#include <debug/MemoryTracker.h>
#include <data-structures/list.h>
#include <core/Window.h>
#include <core/Layer.h>


VampLogger *GlobalGetEngineLogger()
{
    return GLOBAL_ENGINE_LOGGER;
}


VampLogger *GlobalGetClientLogger()
{
    return GLOBAL_CLIENT_LOGGER;
}


VampMemoryTracker *VampGlobalGetMemoryTracker()
{
    return VAMP_GLOBAL_MEMORY_TRACKER;
}


void VampListLayersDecontructor(void *data)
{
    VampLayer *layer = (VampLayer *)data;

    VampDestroyLayer(layer);
}


void VampApplicationRun(VampApplication *app)
{
    while (app->__window__->__is_running__)
    {
        //Run all the layers.
        for (unsigned int i = 0; i < app->__layers_list->__length__; i++)
        {
            VampLayer *layer = app->__layers_list->GetAt(app->__layers_list, i);
            if (layer->__OnUpdate__) layer->__OnUpdate__(layer);
        }

        //Update the VampWindow.
        app->__window__->Update(app->__window__);
    }
}


void VampApplicationAppendLayer(VampApplication *app, VampLayer *layer)
{
    app->__layers_list->Append(app->__layers_list, layer);
    if (layer->__OnAttach__) layer->__OnAttach__(layer);
}




char LayerRemoveCondition(void *data, void *cond)
{
    return data == cond;
}

VampLayer *VampApplicationRemoveLayer(VampApplication *app, VampLayer *layer)
{
    //Remove the layer from the list.
    VampLayer *removed_layer = app->__layers_list->RemoveByCondition(app->__layers_list, LayerRemoveCondition, layer);

    //Layer removed and OnDetach exists.
    if (removed_layer && layer->__OnDetach__) layer->__OnDetach__(layer);

    return removed_layer;
}




VampApplication *VampNewApplication(UserEntryPoint user, const char *title, int width, int height)
{
    VampApplication *new_app = (VampApplication *)malloc( sizeof(VampApplication) );

    GLOBAL_ENGINE_LOGGER        = VampNewLogger("VampEngine");
    GLOBAL_CLIENT_LOGGER        = VampNewLogger("Client");
    VAMP_GLOBAL_MEMORY_TRACKER  = VampNewMemoryTracker();

    new_app->__user_entry_point__   = user;
    new_app->__window__             = VampCreateWindow(new_app, title, width, height);
    new_app->__layers_list          = VampNewList();

    new_app->__Run__                = VampApplicationRun;
    new_app->AppendLayer            = VampApplicationAppendLayer;
    new_app->RemoveLayer            = VampApplicationRemoveLayer;

    return new_app;

}


void VampDestroyApplication(VampApplication *app)
{
    //Destroy all the layers.
    VampDestroyList(app->__layers_list, VampListLayersDecontructor);

    //Destroy the window.
    VampDestroyWindow(app->__window__);

    //If the memory tracker list is not empty, there are memory leaks.
    #ifdef VAMP_DEBUG
    if (!VAMP_GLOBAL_MEMORY_TRACKER->__list__->IsEmpty(VAMP_GLOBAL_MEMORY_TRACKER->__list__))
    {
        VAMP_WARN("There are memory leaks, check out mem.leaks.txt");
    }
    #endif

    //Destroy the loggers.
    VampDestroyLogger(GLOBAL_ENGINE_LOGGER);
    VampDestroyLogger(GLOBAL_CLIENT_LOGGER);

    //Log any memory leaks to a file and then destroy the tracker.
    VAMP_GLOBAL_MEMORY_TRACKER->WriteMemoryLeaksFile(VAMP_GLOBAL_MEMORY_TRACKER, "mem.leaks.txt");
    VampDestroyMemoryTracker(VAMP_GLOBAL_MEMORY_TRACKER);

    free(app);
}