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

void vampPrintfColored(VampPrintColor pColor, const char *pFmt, ...)
{
    const char *ansi = "";

    switch (pColor)
    {
        case VAMP_COLOR_DEFAULT: ansi = "\033[0m";  break;
        case VAMP_COLOR_RED:     ansi = "\033[31m"; break;
        case VAMP_COLOR_GREEN:   ansi = "\033[32m"; break;
        case VAMP_COLOR_YELLOW:  ansi = "\033[33m"; break;
        case VAMP_COLOR_BLUE:    ansi = "\033[34m"; break;
        case VAMP_COLOR_MAGENTA: ansi = "\033[35m"; break;
        case VAMP_COLOR_CYAN:    ansi = "\033[36m"; break;
        case VAMP_COLOR_WHITE:   ansi = "\033[37m"; break;
        default: return;
    }

    #if VAMP_ALL_PC_PLATFORMS
        va_list args;
        va_start(args, pFmt);

        //Set a color, then print the message and final reset the color.
        printf(ansi);
        vprintf(pFmt, args);
        printf("\033[0m");

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
