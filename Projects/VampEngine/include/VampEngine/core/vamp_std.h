#ifndef VAMP_STD_H
#define VAMP_STD_H
#include <VampEngine/core/vamp_platform.h>

#if VAMP_ALL_PC_PLATFORMS
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <stdint.h>
#endif


#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ( (void *)0 )
    #endif
#endif

#if VAMP_ALL_PC_PLATFORMS

    #define VAMP_INT8 int8_t
    #define VAMP_INT16 int16_t
    #define VAMP_INT32 int32_t
    #define VAMP_INT64 int64_t

    #define VAMP_UINT8 u_int8_t
    #define VAMP_UINT16 u_int16_t
    #define VAMP_UINT32 u_int32_t
    #define VAMP_UINT64 u_int64_t

    #define VAMP_SIZE_T size_t

    #define VAMP_SIZEOF(type) sizeof(type)

#endif


typedef enum VampPrintColor
{
    VAMP_COLOR_DEFAULT = 0,
    VAMP_COLOR_RED,
    VAMP_COLOR_GREEN,
    VAMP_COLOR_YELLOW,
    VAMP_COLOR_BLUE,
    VAMP_COLOR_MAGENTA,
    VAMP_COLOR_CYAN,
    VAMP_COLOR_WHITE
} VampPrintColor;


void vampPrintf(const char *pFmt, ...);

void vampPrintfColored(VampPrintColor pColor, const char *pFmt, ...);

void *vampMalloc(VAMP_SIZE_T pSize);

void vampFree(void *pPtr);


#define VAMP_DISABLE_UNUSED_VARIABLE_WARNING(variable) (void)variable

#endif
