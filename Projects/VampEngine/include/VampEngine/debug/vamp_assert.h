#ifndef VAMP_ASSERT_H
#define VAMP_ASSERT_H
#include <VampEngine/debug/vamp_logger.h>

#if defined(VAMP_DEBUG)

#define VAMP_ASSERT(cond, fmt, ...)\
    if ( !(cond) )\
    {\
        VAMP_LOG_FORMAT_ASSERT(fmt, ##__VA_ARGS__);\
        vampExit(-1);\
    }


#else
    #define VAMP_ASSERT(cond, fmt, ...)
#endif

#endif