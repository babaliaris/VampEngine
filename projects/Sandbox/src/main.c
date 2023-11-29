#define VAMP_ENGINE_ENTRY_POINT
#include <VampEngine.h>

void MyApplication(VampApplication *app)
{
    VAMP_INFO(app->__client_logger__, "MyApplication Created!")
}

VampApplication *VampCreateUserApplication()
{
    return VampNewApplication(MyApplication);
}
