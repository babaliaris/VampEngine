#ifndef VAMP_ENTRY_POINT_H
#define VAMP_ENTRY_POINT_H
#include <VampEngine/core/vamp_platform.h>
#include <stdio.h>

//For all PC Platforms.
#if VAMP_ALL_PC_PLATFORMS

    #ifdef VAMP_ENTRY_POINT
    int main()
    {
        printf("Hello VampEngine!\n");
        return 0;
    }
    #endif

#endif

#endif