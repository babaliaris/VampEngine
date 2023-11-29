#include <VampPCH.h>
#include "Application.h"
#include <debug/MemoryTracker.h>
#include <data-structures/list.h>


void VampApplicationRun(VampApplication *app)
{
    VAMP_INFO(app->__engine_logger__, "VampApplicationRun");
}


VampMemoryTracker *VampApplicationGetTracker(VampApplication *app)
{
    return app->__memory_tracker__;
}


VampApplication *VampNewApplication(UserEntryPoint user)
{
    VampApplication *new_app = (VampApplication *)malloc( sizeof(VampApplication) );

    new_app->__engine_logger__      = VampNewLogger("VampEngine");
    new_app->__client_logger__      = VampNewLogger("Client");
    new_app->__user_entry_point__   = user;
    new_app->__memory_tracker__     = VampNewMemoryTracker();

    new_app->Run                    = VampApplicationRun;
    new_app->GetTracker             = VampApplicationGetTracker;

    return new_app;

}


void VampDestroyApplication(VampApplication *app)
{

    //If the memory tracker list is not empty, there are memory leaks.
    #ifdef VAMP_DEBUG
    if (!app->__memory_tracker__->__list__->IsEmpty(app->__memory_tracker__->__list__))
    {
        VAMP_WARN(app->__engine_logger__, "There are memory leaks, check out mem.leaks.txt");
    }
    #endif

    //Destroy the loggers.
    VampDestroyLogger(app->__engine_logger__);
    VampDestroyLogger(app->__client_logger__);

    //Log any memory leaks to a file and then destroy the tracker.
    app->__memory_tracker__->WriteMemoryLeaksFile(app->__memory_tracker__, "mem.leaks.txt");
    VampDestroyMemoryTracker(app->__memory_tracker__);

    free(app);
}