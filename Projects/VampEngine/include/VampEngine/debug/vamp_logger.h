#ifndef VAMP_LOGGER_H
#define VAMP_LOGGER_H
#include <VampEngine/core/vamp_std.h>

#ifdef VAMP_DEBUG

    #define VAMP_LOG_FORMAT_TYPE1(COLOR, LOG_TYPE, CALLER, FILE, FUNC, LINE, FMT, ...)\
        vampPrintf("[%s%s%s]\t{%s%s%s} %s:%ld:(%s%s%s) %s" FMT "%s\n", \
            COLOR, LOG_TYPE, VAMP_COLOR_DEFAULT, \
            VAMP_COLOR_GREEN, CALLER, VAMP_COLOR_DEFAULT, \
            FILE, LINE, VAMP_COLOR_MAGENTA, FUNC, VAMP_COLOR_DEFAULT, \
            COLOR, ##__VA_ARGS__, VAMP_COLOR_DEFAULT)

    #define VAMP_LOG_FORMAT_ASSERT(reason)\
            vampPrintf("[%sASSERTION%s] {%sVampEngine%s} %s:%ld:%s%s%s() %sREASON%s: %s%s%s\n",\
                        VAMP_COLOR_RED, VAMP_COLOR_DEFAULT, VAMP_COLOR_GREEN, VAMP_COLOR_DEFAULT,\
                        __FILE__, __LINE__, VAMP_COLOR_MAGENTA, __func__, VAMP_COLOR_DEFAULT,\
                        VAMP_COLOR_GREEN, VAMP_COLOR_DEFAULT, VAMP_COLOR_CYAN, reason, VAMP_COLOR_DEFAULT\
            )

    #define VAMP_TRACE(fmt, ...)\
        VAMP_LOG_FORMAT_TYPE1(VAMP_COLOR_WHITE, "TRACE", "VampEngine", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

    #define VAMP_INFO(fmt, ...)\
        VAMP_LOG_FORMAT_TYPE1(VAMP_COLOR_CYAN, "INFO", "VampEngine", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

    #define VAMP_WARN(fmt, ...)\
        VAMP_LOG_FORMAT_TYPE1(VAMP_COLOR_YELLOW, "WARN", "VampEngine", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

    #define VAMP_ERROR(fmt, ...)\
        VAMP_LOG_FORMAT_TYPE1(VAMP_COLOR_RED, "ERROR", "VampEngine", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

    #define VAMP_FATAL(fmt, ...)\
        VAMP_LOG_FORMAT_TYPE1(VAMP_COLOR_MAGENTA, "FATAL", "VampEngine", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

    #define VAMP_LOG_COND(cond, LOGGER)\
        if ( (cond) )\
        {\
            LOGGER;\
        }


//Else define all the macros as nothing, to strip all the debug code from release and distribution versions!!!
#else
    #define VAMP_LOG_FORMAT_TYPE1(COLOR, LOG_TYPE, CALLER, FILE, LINE, FMT, ...)
    #define VAMP_TRACE(fmt, ...)
    #define VAMP_INFO(fmt, ...)
    #define VAMP_WARN(fmt, ...)
    #define VAMP_ERROR(fmt, ...)
    #define VAMP_FATAL(fmt, ...)
    #define VAMP_LOG_COND(cond, LOGGER)


#endif

#endif
