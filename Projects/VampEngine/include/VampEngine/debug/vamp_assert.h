#ifndef VAMP_ASSERT_H
#define VAMP_ASSERT_H
#include <VampEngine/debug/vamp_logger.h>

#if VAMP_DEBUG

    #define VAMP_ASSERT(cond)\
        if ( !(cond) )\
        {\
            VAMP_LOG_FORMAT_ASSERTION_TYPE(#cond);\
            vampExit(-1);\
        }

#else
    #define VAMP_ASSERT(cond)

#endif

#endif