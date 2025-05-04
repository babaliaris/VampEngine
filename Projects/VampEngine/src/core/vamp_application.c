#include <VampEngine/core/vamp_application.h>
#include <VampEngine/core/vamp_std.h>

#define VAMP_MEMORY_DEBUGGER_GLOBAL_INSTANCE
#include <VampEngine/core/vamp_memory.h>

static void runIMPL(VampApplication *pThis)
{
    VAMP_DISABLE_UNUSED_VARIABLE_WARNING(pThis);

    vampPrintf("%s%s%s\n", VAMP_COLOR_GREEN, "Hello VampEngine!", VAMP_COLOR_DEFAULT);
}


VampApplication *vampCreateApplication()
{
    //Initialize the memory debugger.
    #if VAMP_DEBUG
        vampMemoryDebuggerInit();
    #endif

    VampApplication *new_app = (VampApplication *)VAMP_MALLOC( VAMP_SIZEOF(VampApplication) );

    //TODO Log a warning or do an assertion here.
    if (!new_app) return NULL;

    new_app->run = runIMPL;

    return new_app;
}



char vampDestroyApplication(VampApplication **pApp)
{
    if ( !pApp || !(*pApp) ) return 0;

    VAMP_FREE(*pApp);

    *pApp = NULL; //Set the user variable to NULL, for safety reasons.

    return 1; //Return successfully!
}