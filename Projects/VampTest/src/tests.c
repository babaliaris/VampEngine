#include <VampTest/vamptest.h>
#include <VampEngine/debug/vamp_assert.h>

VAMPTEST_DECLARE_TEST(memory, vamp_memory_debugger);
VAMPTEST_DECLARE_TEST(memory, vamp_memory_debugger_one_allocation);
VAMPTEST_DECLARE_TEST(memory, vamp_memory_debugger_two_allocations);

int main()
{   
    VAMPTEST_START(vamp_app);

    VAMPTEST_REGISTER(vamp_app, memory, vamp_memory_debugger);
    VAMPTEST_REGISTER(vamp_app, memory, vamp_memory_debugger_one_allocation);
    VAMPTEST_REGISTER(vamp_app, memory, vamp_memory_debugger_two_allocations);

    VAMPTEST_END(vamp_app);

    return 0;
}