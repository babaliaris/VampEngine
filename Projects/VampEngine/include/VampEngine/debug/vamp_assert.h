#ifndef VAMP_ASSERT_H
#define VAMP_ASSERT_H
#include <VampEngine/debug/vamp_logger.h>

#if VAMP_DEBUG

    #define VAMP_ASSERT(cond, fmt, ...)\
        if ( !(cond) )\
        {\
            VAMP_LOG_FORMAT_TYPE1(VAMP_COLOR_RED, "ASSERTION", "VampEngine", __FILE__, __LINE__, fmt, ##__VA_ARGS__);\
            vampExit(-1);\
        }

#else
    #define VAMP_ASSERT(cond, fmt, ...)

#endif

#endif