#include <VampPCH.h>
#include "Application.h"


void VampApplicationRun(VampApplication *app)
{
    while(1)
    {
    }
}


VampApplication *VampNewApplication(UserEntryPoint user)
{
    VampApplication *new_app = (VampApplication *)malloc( sizeof(VampApplication) );

    new_app->__engine_logger__      = VampNewLogger("VampEngine");
    new_app->__client_logger__      = VampNewLogger("Client");
    new_app->__user_entry_point__   = user;
    new_app->Run                    = VampApplicationRun;

    return new_app;

}


void VampDestroyApplication(VampApplication *app)
{
    VampDestroyLogger(app->__engine_logger__);
    VampDestroyLogger(app->__client_logger__);
    free(app);
}