#include <VampTest/vamptest.h>
#include <VampEngine/debug/vamp_assert.h>

VAMPTEST_DECLARE_TEST(memory, vamp_memory_debugger);
VAMPTEST_DECLARE_TEST(memory, vamp_memory_debugger_one_allocation);
VAMPTEST_DECLARE_TEST(memory, vamp_memory_debugger_two_allocations);
VAMPTEST_DECLARE_TEST(stack_allocator, creation_and_deletion);
VAMPTEST_DECLARE_TEST(stack_allocator, pushing_and_using_the_data);
VAMPTEST_DECLARE_TEST(stack_allocator, push_various_types);
VAMPTEST_DECLARE_TEST(pool_allocator, create_delete);
VAMPTEST_DECLARE_TEST(pool_allocator, malloc_until_full);
VAMPTEST_DECLARE_TEST(pool_allocator, malloc_and_free);
VAMPTEST_DECLARE_TEST(pool_allocator, allocations_are_contiguous);
VAMPTEST_DECLARE_TEST(pool_allocator, reused_after_free);
VAMPTEST_DECLARE_TEST(pool_allocator, destroy_pool_with_active_allocations);
VAMPTEST_DECLARE_TEST(pool_allocator, stress_test_alloc_free);

int main()
{   
    VAMPTEST_START(vamp_app);

    VAMPTEST_REGISTER(vamp_app, memory, vamp_memory_debugger);
    VAMPTEST_REGISTER(vamp_app, memory, vamp_memory_debugger_one_allocation);
    VAMPTEST_REGISTER(vamp_app, memory, vamp_memory_debugger_two_allocations);
    VAMPTEST_REGISTER(vamp_app, stack_allocator, creation_and_deletion);
    VAMPTEST_REGISTER(vamp_app, stack_allocator, pushing_and_using_the_data);
    VAMPTEST_REGISTER(vamp_app, stack_allocator, push_various_types);
    VAMPTEST_REGISTER(vamp_app, pool_allocator, create_delete);
    VAMPTEST_REGISTER(vamp_app, pool_allocator, malloc_until_full);
    VAMPTEST_REGISTER(vamp_app, pool_allocator, malloc_and_free);
    VAMPTEST_REGISTER(vamp_app, pool_allocator, allocations_are_contiguous);
    VAMPTEST_REGISTER(vamp_app, pool_allocator, reused_after_free);
    VAMPTEST_REGISTER(vamp_app, pool_allocator, destroy_pool_with_active_allocations);
    VAMPTEST_REGISTER(vamp_app, pool_allocator, stress_test_alloc_free);

    VAMPTEST_END(vamp_app);

    return 0;
}