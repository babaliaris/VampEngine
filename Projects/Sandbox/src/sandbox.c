#define VAMP_ENTRY_POINT
#include <VampEngine/vampengine.h>

VampApplication *userApplicationEntry()
{
    VampApplication *app = vampCreateApplication();

    return app;
}