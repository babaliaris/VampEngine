#include <VampEngine/core/vamp_application.h>
#include <VampEngine/core/vamp_std.h>

static void runIMPL(VampApplication *pThis)
{
    VAMP_DISABLE_UNUSED_VARIABLE_WARNING(pThis);

    vampPrintfColored(VAMP_COLOR_CYAN, "%s\n", "Hello VampEngine!");
}


VampApplication *vampCreateApplication()
{
    VampApplication *new_app = (VampApplication *)vampMalloc( VAMP_SIZEOF(VampApplication) );

    //TODO Log a warning or do an assertion here.
    if (!new_app) return NULL;

    new_app->run = runIMPL;

    return new_app;
}



char vampDestroyApplication(VampApplication **pApp)
{
    if ( !pApp || !(*pApp) ) return 0;

    vampFree(*pApp);

    *pApp = NULL; //Set the user variable to NULL, for safety reasons.

    return 1; //Return successfully!
}