#define VAMP_LOGGER_INIT
#include <VampPCH.h>
#include <debug/Logger.h>
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


void VampApplicationRun(VampApplication *app)
{
    while (app->__window__->__is_running__)
    {
        app->__window__->Update(app->__window__);
    }
}


VampMemoryTracker *VampApplicationGetTracker(VampApplication *app)
{
    return app->__memory_tracker__;
}


VampApplication *VampNewApplication(UserEntryPoint user, const char *title, int width, int height)
{
    VampApplication *new_app = (VampApplication *)malloc( sizeof(VampApplication) );

    GLOBAL_ENGINE_LOGGER     = VampNewLogger("VampEngine");
    GLOBAL_CLIENT_LOGGER     = VampNewLogger("Client");

    new_app->__user_entry_point__   = user;
    new_app->__memory_tracker__     = VampNewMemoryTracker();
    new_app->__window__             = VampNewWindow(new_app, title, width, height);

    new_app->Run                    = VampApplicationRun;
    new_app->GetTracker             = VampApplicationGetTracker;

    return new_app;

}


void VampDestroyApplication(VampApplication *app)
{

    VampDestroyWindow(app->__window__);

    //If the memory tracker list is not empty, there are memory leaks.
    #ifdef VAMP_DEBUG
    if (!app->__memory_tracker__->__list__->IsEmpty(app->__memory_tracker__->__list__))
    {
        VAMP_WARN("There are memory leaks, check out mem.leaks.txt");
    }
    #endif

    //Destroy the loggers.
    VampDestroyLogger(GLOBAL_ENGINE_LOGGER);
    VampDestroyLogger(GLOBAL_CLIENT_LOGGER);

    //Log any memory leaks to a file and then destroy the tracker.
    app->__memory_tracker__->WriteMemoryLeaksFile(app->__memory_tracker__, "mem.leaks.txt");
    VampDestroyMemoryTracker(app->__memory_tracker__);

    free(app);
}