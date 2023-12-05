#include <VampPCH.h>
#include "Logger.h"
#include "sds.h"


static void SetLevel(VampLogger *this, unsigned int level)
{
    this->__level__ = level;
}


VampLogger *VampNewLogger(const char *name)
{
    VampLogger *new_logger = (VampLogger *)malloc( sizeof(VampLogger) );

    new_logger->__level__   = VAMP_LOGGER_LEVEL_ERROR;
    new_logger->__name__    = sdsnew(name);
    new_logger->SetLevel    = SetLevel;

    return new_logger;
}

void VampDestroyLogger(VampLogger *logger)
{
    sdsfree(logger->__name__);
    free(logger);
}