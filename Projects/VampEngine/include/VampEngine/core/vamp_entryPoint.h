#ifndef VAMP_ENTRY_POINT_H
#define VAMP_ENTRY_POINT_H
#include <VampEngine/core/vamp_application.h>

//For all PC Platforms.
#if VAMP_ALL_PC_PLATFORMS

    #ifdef VAMP_ENTRY_POINT
    int main()
    {
        VampApplication *app = userApplicationEntry();

        app->run(app);

        return vampDestroyApplication(&app);
    }
    #endif

#endif

#endif