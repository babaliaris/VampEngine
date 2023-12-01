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

#ifdef VAMP_LOGGER_INIT
VampLogger *GLOBAL_ENGINE_LOGGER;
VampLogger *GLOBAL_CLIENT_LOGGER;
#endif

VampLogger *GlobalGetEngineLogger();
VampLogger *GlobalGetClientLogger();


#define VAMP_PRINTF_COLORED(color, ...)\
    printf(color);printf(__VA_ARGS__);printf(VAMP_CLI_COLOR_RESET);


#ifdef VAMP_DEBUG
    #define __VAMP_LOG__(logger, level_name, debug_color, message_color, ...)\
        VAMP_PRINTF_COLORED(debug_color, \
            "[%s : %s]\n\t[%s : %d]\n\t[Message]: ", logger->__name__->GetCStr(logger->__name__), level_name, __FILE__, __LINE__)\
            \
        VAMP_PRINTF_COLORED(message_color, __VA_ARGS__)\
        printf("\n\n");


    #define __VAMP_LOGGER_CHECK__(logger, LEVEL, name, log_color, msg_color, ...)\
        if (GlobalGetEngineLogger()->__level__ >= LEVEL)\
        {\
            __VAMP_LOG__(logger, name, log_color, msg_color, __VA_ARGS__)\
        }


    #define VAMP_INFO(...)\
        __VAMP_LOGGER_CHECK__(GlobalGetEngineLogger(), VAMP_LOGGER_LEVEL_INFO, "INFO", VAMP_CLI_COLOR_GREEN, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_WARN(...)\
        __VAMP_LOGGER_CHECK__(GlobalGetEngineLogger(), VAMP_LOGGER_LEVEL_WARN, "WARNING", VAMP_CLI_COLOR_YELLOW, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_ERROR(...)\
        __VAMP_LOGGER_CHECK__(GlobalGetEngineLogger(), VAMP_LOGGER_LEVEL_ERROR, "ERROR", VAMP_CLI_COLOR_RED, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_FATAL(...)\
        __VAMP_LOGGER_CHECK__(GlobalGetEngineLogger(), VAMP_LOGGER_LEVEL_FATAL, "FATAL", VAMP_CLI_COLOR_RED, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)


    #define VAMP_CLIENT_INFO(...)\
        __VAMP_LOGGER_CHECK__(GlobalGetClientLogger(), VAMP_LOGGER_LEVEL_INFO, "INFO", VAMP_CLI_COLOR_GREEN, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_CLIENT_WARN(...)\
        __VAMP_LOGGER_CHECK__(GlobalGetClientLogger(), VAMP_LOGGER_LEVEL_WARN, "WARNING", VAMP_CLI_COLOR_YELLOW, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_CLIENT_ERROR(...)\
        __VAMP_LOGGER_CHECK__(GlobalGetClientLogger(), VAMP_LOGGER_LEVEL_ERROR, "ERROR", VAMP_CLI_COLOR_RED, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_CLIENT_FATAL(...)\
        __VAMP_LOGGER_CHECK__(GlobalGetClientLogger(), VAMP_LOGGER_LEVEL_FATAL, "FATAL", VAMP_CLI_COLOR_RED, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

#else
    #define __VAMP_LOG__(logger, level_name, debug_color, message_color, ...)
    #define __VAMP_LOGGER_CHECK__(logger, LEVEL, name, log_color, msg_color, ...)

    #define VAMP_INFO(...)
    #define VAMP_WARN(...)
    #define VAMP_ERROR(...)
    #define VAMP_FATAL(...)
    
    #define VAMP_CLIENT_INFO(...)
    #define VAMP_CLIENT_WARN(...)
    #define VAMP_CLIENT_ERROR(...)
    #define VAMP_CLIENT_FATAL(...)
    

#endif

#endif