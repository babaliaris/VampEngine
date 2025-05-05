#ifndef VAMP_ENTRY_POINT_H
#define VAMP_ENTRY_POINT_H
#include <VampEngine/core/vamp_application.h>

/**
 * @file
 * @brief The entry point of the `VampApplication`
 * 
 * Define VAMP_ENTRY_POINT in only ONE .c or .cpp 
 * file before including this header file, in order
 * to enable the entry point of the Engine.
 * 
 * @author Babaliaris Nikolaos
 * @date 05 May 2025
 */

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