#define VAMP_LOGGER_INIT
#define VAMP_MEMORY_TRACKER_INIT
#include <VampPCH.h>
#include <debug/Logger.h>
#include <debug/MemoryTracker.h>
#include "Application.h"
#include <debug/MemoryTracker.h>
#include <data-structures/list.h>
#include <core/Window.h>


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


void VampApplicationRun(VampApplication *app)
{
    while (app->__window__->__is_running__)
    {
        app->__window__->Update(app->__window__);
    }
}


VampApplication *VampNewApplication(UserEntryPoint user, const char *title, int width, int height)
{
    VampApplication *new_app = (VampApplication *)malloc( sizeof(VampApplication) );

    GLOBAL_ENGINE_LOGGER        = VampNewLogger("VampEngine");
    GLOBAL_CLIENT_LOGGER        = VampNewLogger("Client");
    VAMP_GLOBAL_MEMORY_TRACKER  = VampNewMemoryTracker();

    new_app->__user_entry_point__   = user;
    new_app->__window__             = VampNewWindow(new_app, title, width, height);

    new_app->Run                    = VampApplicationRun;

    return new_app;

}


void VampDestroyApplication(VampApplication *app)
{

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