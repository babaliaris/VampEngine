#include <VampEngine/core/vamp_std.h>

void vampPrintf(const char *pFmt, ...)
{
    #if VAMP_ALL_PC_PLATFORMS
        va_list args;
        va_start(args, pFmt);
        vprintf(pFmt, args);
        va_end(args);
    #else
        #error Platform not supported!
    #endif
}

void *vampMalloc(VAMP_SIZE_T pSize)
{
    #if VAMP_ALL_PC_PLATFORMS
        return malloc(pSize);
    #else
        #error Platform not supported!
    #endif
}

void vampFree(void *pPtr)
{
    #if VAMP_ALL_PC_PLATFORMS
        free(pPtr);
    #else
        #error Platform not supported!
    #endif
}



void vampExit(int status)
{
    #if VAMP_ALL_PC_PLATFORMS
        exit(status);
    #else
        #error Platform not supported!
    #endif
}
