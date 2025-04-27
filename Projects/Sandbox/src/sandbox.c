#define VAMP_ENTRY_POINT
#include <VampEngine/vampengine.h>

VampApplication *userApplicationEntry()
{
    vampPrintf("This is the User Entry Point!\n");
    return vampCreateApplication();
}