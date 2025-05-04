#include <VampTest/vamptest.h>

#define VAMP_MEMORY_DEBUGGER_GLOBAL_INSTANCE
#include <VampEngine/core/vamp_memory.h>

typedef struct ExampleUserStruct
{

    int some_index;
    const char *some_str;
    float some_number;
    char some_flag;

}ExampleUserStruct;



VAMPTEST_TEST(memory, vamp_memory_debugger)
{
    //Initialize the memory debugger.
    #if VAMP_DEBUG
        vampMemoryDebuggerInit();
    #endif

    ExampleUserStruct *new_struct1 = VAMP_MALLOC(VAMP_SIZEOF(ExampleUserStruct));
    ExampleUserStruct *new_struct2 = VAMP_MALLOC(VAMP_SIZEOF(ExampleUserStruct));
    ExampleUserStruct *new_struct3 = VAMP_MALLOC(VAMP_SIZEOF(ExampleUserStruct));

    #if VAMP_DEBUG
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations == 3);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_head != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.malloc != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.free   != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.checkForLeaks != NULL);
    #endif

    new_struct1->some_index     = 0;
    new_struct1->some_number    = 0.0f;
    new_struct1->some_flag      = 0;

    new_struct2->some_index     = 1;
    new_struct2->some_number    = 1.1f;
    new_struct2->some_flag      = 1;

    new_struct3->some_index     = 2;
    new_struct3->some_number    = 2.5f;
    new_struct3->some_flag      = 0;

    VAMPTEST_ASSERT(new_struct1->some_index     == 0);
    VAMPTEST_ASSERT(new_struct1->some_number    == 0.0f);
    VAMPTEST_ASSERT(new_struct1->some_flag      == 0);

    VAMPTEST_ASSERT(new_struct2->some_index     == 1);
    VAMPTEST_ASSERT(new_struct2->some_number    == 1.1f);
    VAMPTEST_ASSERT(new_struct2->some_flag      == 1);

    VAMPTEST_ASSERT(new_struct3->some_index     == 2);
    VAMPTEST_ASSERT(new_struct3->some_number    == 2.5f);
    VAMPTEST_ASSERT(new_struct3->some_flag      == 0);

    VAMP_FREE(new_struct1);
    VAMP_FREE(new_struct2);
    VAMP_FREE(new_struct3);

    #if VAMP_DEBUG
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations == 0);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_head == NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail == NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.malloc != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.free   != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.checkForLeaks != NULL);
    #endif
}



VAMPTEST_TEST(memory, vamp_memory_debugger_one_allocation)
{
    //Initialize the memory debugger.
    #if VAMP_DEBUG
        vampMemoryDebuggerInit();
    #endif

    ExampleUserStruct *new_struct1 = VAMP_MALLOC(VAMP_SIZEOF(ExampleUserStruct));

    #if VAMP_DEBUG
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations == 1);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_head != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.malloc != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.free   != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.checkForLeaks != NULL);
    #endif

    new_struct1->some_index     = 4;
    new_struct1->some_number    = 5.5f;
    new_struct1->some_flag      = 1;

    VAMPTEST_ASSERT(new_struct1->some_index     == 4);
    VAMPTEST_ASSERT(new_struct1->some_number    == 5.5f);
    VAMPTEST_ASSERT(new_struct1->some_flag      == 1);


    VAMP_FREE(new_struct1);

    #if VAMP_DEBUG
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations == 0);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_head == NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail == NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.malloc != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.free   != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.checkForLeaks != NULL);
    #endif
}


VAMPTEST_TEST(memory, vamp_memory_debugger_two_allocations)
{
    //Initialize the memory debugger.
    #if VAMP_DEBUG
        vampMemoryDebuggerInit();
    #endif

    ExampleUserStruct *new_struct1 = VAMP_MALLOC(VAMP_SIZEOF(ExampleUserStruct));
    ExampleUserStruct *new_struct2 = VAMP_MALLOC(VAMP_SIZEOF(ExampleUserStruct));

    #if VAMP_DEBUG
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations == 2);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_head != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.malloc != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.free   != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.checkForLeaks != NULL);
    #endif

    new_struct1->some_index     = 0;
    new_struct1->some_number    = 0.0f;
    new_struct1->some_flag      = 0;

    new_struct2->some_index     = 1;
    new_struct2->some_number    = 1.1f;
    new_struct2->some_flag      = 1;

    VAMPTEST_ASSERT(new_struct1->some_index     == 0);
    VAMPTEST_ASSERT(new_struct1->some_number    == 0.0f);
    VAMPTEST_ASSERT(new_struct1->some_flag      == 0);

    VAMPTEST_ASSERT(new_struct2->some_index     == 1);
    VAMPTEST_ASSERT(new_struct2->some_number    == 1.1f);
    VAMPTEST_ASSERT(new_struct2->some_flag      == 1);

    VAMP_FREE(new_struct1);
    VAMP_FREE(new_struct2);

    #if VAMP_DEBUG
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations == 0);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_head == NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail == NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.malloc != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.free   != NULL);
        VAMPTEST_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.checkForLeaks != NULL);
    #endif
}
