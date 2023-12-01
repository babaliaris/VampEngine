#define VAMP_ENGINE_ENTRY_POINT
#include <VampEngine.h>

void Sandbox(VampApplication *app)
{
}

VampApplication *VampCreateUserApplication()
{
    return VampNewApplication(Sandbox, "Sandbox", 800, 600);
}
