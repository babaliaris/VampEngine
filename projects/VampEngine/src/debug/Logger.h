#ifndef VAMP_ENGINE_LOGGER_H
#define VAMP_ENGINE_LOGGER_H


/**
 * @file
*/

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



typedef char * sds;


/**
 * The structure that describes a logger object.
*/
typedef struct VampLogger
{
    /**
     * Set the level of the logger.
     * 
     * @param[in] this The logger object.
     * @param[in] level The level (Macro defined enum, starts with VAMP_LOGGER_LEVEL).
    */
    void (*SetLevel)(struct VampLogger *this, unsigned int level);


    unsigned int __level__; /**< @private*/
    sds __name__; /**< @private*/
}
VampLogger;


/**
 * Creates a new logger object.
 * 
 * @param[in] name The name of the logger.
 * 
 * @returns The newly created logger object.
*/
VampLogger *VampNewLogger(const char *name);


/**
 * Destroys the Logger.
 * 
 * @param[in] logger The logger object to be destroyed.
*/
void VampDestroyLogger(VampLogger *logger);



/**
 * Define VAMP_LOGGER_INIT in only ONE .c file. Then
 * create two loggers using VampNewLogger() and assign
 * their value to the following global pointers:
 * GLOBAL_ENGINE_LOGGER and GLOBAL_CLIENT_LOGGER.
*/
#ifdef VAMP_LOGGER_INIT
VampLogger *VAMP_GLOBAL_ENGINE_LOGGER;
VampLogger *VAMP_GLOBAL_CLIENT_LOGGER;
#endif


/**
 * User defined function.
 * MUST be implemented in the same .c file where #define VAMP_LOGGER_INIT
 * took place.
 * 
 * @returns MUST return then GLOBAL_ENGINE_LOGGER pointer.
*/
VampLogger *VampGlobalGetEngineLogger();


/**
 * User defined function.
 * MUST be implemented in the same .c file where #define VAMP_LOGGER_INIT
 * took place.
 * 
 * @returns MUST return the GLOBAL_CLIENT_LOGGER pointer.
*/
VampLogger *VampGlobalGetClientLogger();






#define VAMP_PRINTF_COLORED(color, ...)\
    printf(color);printf(__VA_ARGS__);printf(VAMP_CLI_COLOR_RESET);


#ifdef VAMP_DEBUG
    #define __VAMP_LOG__(logger, level_name, debug_color, message_color, ...)\
        VAMP_PRINTF_COLORED(debug_color, \
            "[%s : %s]\n\t[%s : %d]\n\t[Message]: ", logger->__name__, level_name, __FILE__, __LINE__)\
            \
        VAMP_PRINTF_COLORED(message_color, __VA_ARGS__)\
        printf("\n\n");


    #define __VAMP_LOGGER_CHECK__(logger, LEVEL, name, log_color, msg_color, ...)\
        if (logger->__level__ >= LEVEL)\
        {\
            __VAMP_LOG__(logger, name, log_color, msg_color, __VA_ARGS__)\
        }


    #define VAMP_INFO(...)\
        __VAMP_LOGGER_CHECK__(VampGlobalGetEngineLogger(), VAMP_LOGGER_LEVEL_INFO, "INFO", VAMP_CLI_COLOR_GREEN, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_WARN(...)\
        __VAMP_LOGGER_CHECK__(VampGlobalGetEngineLogger(), VAMP_LOGGER_LEVEL_WARN, "WARNING", VAMP_CLI_COLOR_YELLOW, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_ERROR(...)\
        __VAMP_LOGGER_CHECK__(VampGlobalGetEngineLogger(), VAMP_LOGGER_LEVEL_ERROR, "ERROR", VAMP_CLI_COLOR_RED, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_FATAL(...)\
        __VAMP_LOGGER_CHECK__(VampGlobalGetEngineLogger(), VAMP_LOGGER_LEVEL_FATAL, "FATAL", VAMP_CLI_COLOR_RED, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)


    #define VAMP_CLIENT_INFO(...)\
        __VAMP_LOGGER_CHECK__(VampGlobalGetClientLogger(), VAMP_LOGGER_LEVEL_INFO, "INFO", VAMP_CLI_COLOR_GREEN, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_CLIENT_WARN(...)\
        __VAMP_LOGGER_CHECK__(VampGlobalGetClientLogger(), VAMP_LOGGER_LEVEL_WARN, "WARNING", VAMP_CLI_COLOR_YELLOW, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_CLIENT_ERROR(...)\
        __VAMP_LOGGER_CHECK__(VampGlobalGetClientLogger(), VAMP_LOGGER_LEVEL_ERROR, "ERROR", VAMP_CLI_COLOR_RED, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

    #define VAMP_CLIENT_FATAL(...)\
        __VAMP_LOGGER_CHECK__(VampGlobalGetClientLogger(), VAMP_LOGGER_LEVEL_FATAL, "FATAL", VAMP_CLI_COLOR_RED, VAMP_CLI_COLOR_CYAN, __VA_ARGS__)

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