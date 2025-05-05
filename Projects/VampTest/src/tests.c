#include <VampTest/vamptest.h>
#include <VampEngine/debug/vamp_assert.h>

VAMPTEST_DECLARE_TEST(memory, vamp_memory_debugger);
VAMPTEST_DECLARE_TEST(memory, vamp_memory_debugger_one_allocation);
VAMPTEST_DECLARE_TEST(memory, vamp_memory_debugger_two_allocations);
VAMPTEST_DECLARE_TEST(stack_allocator, creation_and_deletion);
VAMPTEST_DECLARE_TEST(stack_allocator, pushing_and_using_the_data);
VAMPTEST_DECLARE_TEST(stack_allocator, push_various_types);

int main()
{   
    VAMPTEST_START(vamp_app);

    VAMPTEST_REGISTER(vamp_app, memory, vamp_memory_debugger);
    VAMPTEST_REGISTER(vamp_app, memory, vamp_memory_debugger_one_allocation);
    VAMPTEST_REGISTER(vamp_app, memory, vamp_memory_debugger_two_allocations);
    VAMPTEST_REGISTER(vamp_app, stack_allocator, creation_and_deletion);
    VAMPTEST_REGISTER(vamp_app, stack_allocator, pushing_and_using_the_data);
    VAMPTEST_REGISTER(vamp_app, stack_allocator, push_various_types);

    VAMPTEST_END(vamp_app);

    return 0;
}