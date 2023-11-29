#include <VampPCH.h>
#include "Application.h"
#include <debug/MemoryTracker.h>


void VampApplicationRun(VampApplication *app)
{
    VAMP_INFO(app->__engine_logger__, "VampApplicationRun");
}


VampApplication *VampNewApplication(UserEntryPoint user)
{
    VampApplication *new_app = (VampApplication *)malloc( sizeof(VampApplication) );

    new_app->__engine_logger__      = VampNewLogger("VampEngine");
    new_app->__client_logger__      = VampNewLogger("Client");
    new_app->__user_entry_point__   = user;
    new_app->Run                    = VampApplicationRun;
    new_app->__memory_tracker__     = VampNewMemoryTracker();

    return new_app;

}


void VampDestroyApplication(VampApplication *app)
{
    VampDestroyLogger(app->__engine_logger__);
    VampDestroyLogger(app->__client_logger__);
    VampDestroyMemoryTracker(app->__memory_tracker__);
    free(app);
}