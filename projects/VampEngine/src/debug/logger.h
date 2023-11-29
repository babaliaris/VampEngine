#ifndef VAMP_ENGINE_LOGGER_H
#define VAMP_ENGINE_LOGGER_H
#include <VampString.h>

#define VAMP_LOGGER_LEVEL_INFO  0
#define VAMP_LOGGER_LEVEL_WARN  1
#define VAMP_LOGGER_LEVEL_ERROR 2
#define VAMP_LOGGER_LEVEL_FATAL 3

#define VAMP_CLI_COLOR_RESET    "\033[0;0m"
#define VAMP_CLI_COLOR_RED      "\033[0;31m"
#define VAMP_CLI_COLOR_GREEN    "\033[0;32m"
#define VAMP_CLI_COLOR_YELLOW   "\033[0;33m"
#define VAMP_CLI_COLOR_BLUE     "\033[0;34m"
#define VAMP_CLI_COLOR_PINK     "\033[0;35m"
#define VAMP_CLI_COLOR_CYAN     "\033[0;36m"
#define VAMP_CLI_COLOR_WHITE    "\033[0;37m"

typedef struct VampLogger
{
    unsigned int __level__;
    VampString *__name__;

    void (*SetLevel)(struct VampLogger *logger, unsigned int level);
}
VampLogger;


VampLogger *VampNewLogger(const char *name);

void VampDestroyLogger(VampLogger *logger);


#define VAMP_PRINTF_COLORED(color, ...)\
    printf(color);printf(__VA_ARGS__);printf(VAMP_CLI_COLOR_RESET);


#ifdef VAMP_DEBUG
    #define __VAMP_LOG__(logger, level_name, debug_color, message_color, ...)\
        VAMP_PRINTF_COLORED(debug_color, \
            "[%s : %s]\n\t[%s : %d]\n\t[Message]: ", logger->__name__->GetCStr(logger->__name__), level_name, __FILE__, __LINE__)\
            \
        VAMP_PRINTF_COLORED(message_color, __VA_ARGS__)\
        printf("\n\n");


    #define VAMP_INFO(logger, ...)\
        if (logger->__level__ >= VAMP_LOGGER_LEVEL_INFO)\
        {\
            __VAMP_LOG__(logger, "INFO", VAMP_CLI_COLOR_GREEN, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)\
        }

    #define VAMP_WARN(logger, ...)\
        if (logger->__level__ >= VAMP_LOGGER_LEVEL_WARN)\
        {\
            __VAMP_LOG__(logger, "WARNING", VAMP_CLI_COLOR_YELLOW, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)\
        }

    #define VAMP_ERROR(logger, ...)\
        if (logger->__level__ >= VAMP_LOGGER_LEVEL_ERROR)\
        {\
            __VAMP_LOG__(logger, "ERROR", VAMP_CLI_COLOR_RED, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)\
        }

    #define VAMP_FATAL(logger, ...)\
        if (logger->__level__ >= VAMP_LOGGER_LEVEL_FATAL)\
        {\
            __VAMP_LOG__(logger, "FATAL", VAMP_CLI_COLOR_RED, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)\
        }

#else
    #define __VAMP_LOG__(level_name, debug_color, message_color, ...)
    #define VAMP_INFO(logger, ...)
    #define VAMP_WARN(logger, ...)
    #define VAMP_ERROR(logger, ...)
    #define VAMP_FATAL(logger, ...)

#endif

#endif