#define VAMP_ENTRY_POINT
#include <VampEngine/vampengine.h>

VampApplication *userApplicationEntry()
{   
    VAMP_LOG_FORMAT_TYPE1(VAMP_COLOR_CYAN, "MESSAGE", "SANDBOX", __FILE__, __func__, __LINE__, "%s", "This is a message!");

    VAMP_TRACE("This is a TRACE!");
    VAMP_INFO("This is an INFO!");
    VAMP_WARN("This is a WARNING!");
    VAMP_ERROR("This is an ERROR!");
    VAMP_FATAL("This is FATAL!");

    VAMP_INFO("%s", "This is an INFO using a formatted string!");

    return vampCreateApplication();
}