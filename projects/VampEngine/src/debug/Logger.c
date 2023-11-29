#include <VampPCH.h>
#include "Logger.h"


void VampLoggerSetLevel(VampLogger *logger, unsigned int level)
{
    logger->__level__ = level;
}


VampLogger *VampNewLogger(const char *name)
{
    VampLogger *new_logger = (VampLogger *)malloc( sizeof(VampLogger) );

    new_logger->__level__   = VAMP_LOGGER_LEVEL_ERROR;
    new_logger->__name__    = VampNewString(name);
    new_logger->SetLevel    = VampLoggerSetLevel;

    return new_logger;
}

void VampDestroyLogger(VampLogger *logger)
{
    VampDestroyString(logger->__name__);
    free(logger);
}