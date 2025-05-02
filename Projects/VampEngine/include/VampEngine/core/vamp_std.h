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

    #define VAMP_COLOR_DEFAULT  "\033[0m"
    #define VAMP_COLOR_RED      "\033[31m"
    #define VAMP_COLOR_GREEN    "\033[32m"
    #define VAMP_COLOR_YELLOW   "\033[33m"
    #define VAMP_COLOR_BLUE     "\033[34m"
    #define VAMP_COLOR_MAGENTA  "\033[35m"
    #define VAMP_COLOR_CYAN     "\033[36m"
    #define VAMP_COLOR_WHITE    "\033[37m"

#endif


VAMP_API void vampPrintf(const char *pFmt, ...);

VAMP_API void *vampMalloc(VAMP_SIZE_T pSize);

VAMP_API void vampFree(void *pPtr);

VAMP_API void vampExit(int status);


#define VAMP_DISABLE_UNUSED_VARIABLE_WARNING(variable) (void)variable

#endif
