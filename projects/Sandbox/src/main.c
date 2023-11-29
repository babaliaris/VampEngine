#define VAMP_ENGINE_ENTRY_POINT
#include <VampEngine.h>

void Sandbox(VampApplication *app)
{
    VAMP_INFO(app->__client_logger__, "Sandbox Created!")
}

VampApplication *VampCreateUserApplication()
{
    return VampNewApplication(Sandbox);
}
