#include <VampTest/vamptest.h>
#include <VampEngine/core/vamp_memory.h>

VAMPTEST_TEST(pool_allocator, create_delete)
{
    #if VAMP_DEBUG
        vampMemoryDebuggerInit();
    #endif

    VampMemoryPool *pool = vampCreateMemoryPool(VAMP_SIZEOF(float), 4);

    VAMPTEST_ASSERT(pool->m_buffer != NULL);
    VAMPTEST_ASSERT(pool->m_buffer_size == ( VAMP_SIZEOF(float) + VAMP_SIZEOF(__VampMemoryPoolBlock__) ) * 4);
    VAMPTEST_ASSERT(pool->m_lastDirtyBlock == pool->m_buffer);
    VAMPTEST_ASSERT(pool->m_nextFreeBlock == pool->m_buffer);
    VAMPTEST_ASSERT(pool->m_user_block_count == 4);
    VAMPTEST_ASSERT(pool->m_user_block_size == VAMP_SIZEOF(float));
    VAMPTEST_ASSERT(pool->m_blocks_in_used == 0);
    VAMPTEST_ASSERT(pool->m_block_size == VAMP_SIZEOF(float) + VAMP_SIZEOF(__VampMemoryPoolBlock__));
    VAMPTEST_ASSERT(pool->malloc != NULL);
    VAMPTEST_ASSERT(pool->free != NULL);
    VAMPTEST_ASSERT(pool->remainingSize != NULL);
    VAMPTEST_ASSERT(pool->occupiedSize != NULL);

    vampDestroyMemoryPool(&pool);

    VAMPTEST_ASSERT(pool == NULL);
}



VAMPTEST_TEST(pool_allocator, malloc_until_full)
{
    #if VAMP_DEBUG
        vampMemoryDebuggerInit();
    #endif

    VampMemoryPool *pool = vampCreateMemoryPool(VAMP_SIZEOF(float), 4);

    float num1 = 5.5f;
    float *m1 = (float *)pool->malloc(pool, &num1);
    VAMPTEST_ASSERT(m1 != NULL);
    VAMPTEST_ASSERT(*m1 == num1);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 3 * VAMP_SIZEOF(float) );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 1 * VAMP_SIZEOF(float) );

    float num2 = 8.5f;
    float *m2 = (float *)pool->malloc(pool, &num2);
    VAMPTEST_ASSERT(m2 != NULL);
    VAMPTEST_ASSERT(*m2 == num2);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 2 * VAMP_SIZEOF(float) );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 2 * VAMP_SIZEOF(float) );

    float num3 = 3.5f;
    float *m3 = (float *)pool->malloc(pool, &num3);
    VAMPTEST_ASSERT(m3 != NULL);
    VAMPTEST_ASSERT(*m3 == num3);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 1 * VAMP_SIZEOF(float) );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 3 * VAMP_SIZEOF(float) );

    float num4 = 4.5f;
    float *m4 = (float *)pool->malloc(pool, &num4);
    VAMPTEST_ASSERT(m4 != NULL);
    VAMPTEST_ASSERT(*m4 == num4);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 0 );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 4 * VAMP_SIZEOF(float) );

    float num5 = 10.5f;
    float *m5 = (float *)pool->malloc(pool, &num5);
    VAMPTEST_ASSERT(m5 == NULL);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 0 );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 4 * VAMP_SIZEOF(float) );

    vampDestroyMemoryPool(&pool);
    VAMPTEST_ASSERT(pool == NULL);
}


VAMPTEST_TEST(pool_allocator, malloc_and_free)
{
    #if VAMP_DEBUG
        vampMemoryDebuggerInit();
    #endif

    VampMemoryPool *pool = vampCreateMemoryPool(VAMP_SIZEOF(float), 4);

    //Add a number.
    float num1 = 5.5f;
    float *m1 = (float *)pool->malloc(pool, &num1);
    VAMPTEST_ASSERT(m1 != NULL);
    VAMPTEST_ASSERT(*m1 == num1);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 3 * VAMP_SIZEOF(float) );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 1 * VAMP_SIZEOF(float) );

    //Add yet another one.
    float num2 = 8.5f;
    float *m2 = (float *)pool->malloc(pool, &num2);
    VAMPTEST_ASSERT(m2 != NULL);
    VAMPTEST_ASSERT(*m2 == num2);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 2 * VAMP_SIZEOF(float) );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 2 * VAMP_SIZEOF(float) );

    //Free m1
    pool->free(pool, (void *)m1);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 3 * VAMP_SIZEOF(float) );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 1 * VAMP_SIZEOF(float) );

    //Add num2 again.
    m2 = (float *)pool->malloc(pool, &num2);
    VAMPTEST_ASSERT(m2 != NULL);
    VAMPTEST_ASSERT(*m2 == num2);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 2 * VAMP_SIZEOF(float) );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 2 * VAMP_SIZEOF(float) );

    //Add a third number
    float num3 = 3.5f;
    float *m3 = (float *)pool->malloc(pool, &num3);
    VAMPTEST_ASSERT(m3 != NULL);
    VAMPTEST_ASSERT(*m3 == num3);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 1 * VAMP_SIZEOF(float) );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 3 * VAMP_SIZEOF(float) );

    //Remove num3
    pool->free(pool, (void *)m3);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 2 * VAMP_SIZEOF(float) );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 2 * VAMP_SIZEOF(float) );

    //Readd it.
    m3 = (float *)pool->malloc(pool, &num3);
    VAMPTEST_ASSERT(m3 != NULL);
    VAMPTEST_ASSERT(*m3 == num3);
    VAMPTEST_ASSERT( pool->remainingSize(pool) == 1 * VAMP_SIZEOF(float) );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 3 * VAMP_SIZEOF(float) );

    pool->free(pool, (void *)m1);
    pool->free(pool, (void *)m2);
    pool->free(pool, (void *)m3);

    VAMPTEST_ASSERT( pool->remainingSize(pool) == 4 * VAMP_SIZEOF(float) );
    VAMPTEST_ASSERT( pool->occupiedSize(pool) == 0 );

    vampDestroyMemoryPool(&pool);
    VAMPTEST_ASSERT(pool == NULL);
}

VAMPTEST_TEST(pool_allocator, allocations_are_contiguous)
{
    VampMemoryPool *pool = vampCreateMemoryPool(VAMP_SIZEOF(int), 3);

    int num = 5;

    int *a = (int *)pool->malloc(pool, &num);
    int *b = (int *)pool->malloc(pool, &num);
    int *c = (int *)pool->malloc(pool, &num);

    VAMPTEST_ASSERT(a != NULL);
    VAMPTEST_ASSERT(b != NULL);
    VAMPTEST_ASSERT(c != NULL);

    VAMP_SIZE_T stride = VAMP_SIZEOF(int) + VAMP_SIZEOF(__VampMemoryPoolBlock__);
    VAMPTEST_ASSERT((VAMP_SIZE_T)b - (VAMP_SIZE_T)a == stride);
    VAMPTEST_ASSERT((VAMP_SIZE_T)c - (VAMP_SIZE_T)b == stride);

    vampDestroyMemoryPool(&pool);
}


VAMPTEST_TEST(pool_allocator, reused_after_free)
{
    VampMemoryPool *pool = vampCreateMemoryPool(VAMP_SIZEOF(int), 2);

    int val1 = 42, val2 = 88;
    int *a = (int *)pool->malloc(pool, &val1);
    int *b = (int *)pool->malloc(pool, &val2);

    VAMP_DISABLE_UNUSED_VARIABLE_WARNING(a);

    pool->free(pool, b); // Free second block

    int val3 = 77;
    int *c = (int *)pool->malloc(pool, &val3);

    // Confirm it's reusing the same address
    VAMPTEST_ASSERT(c == b);
    VAMPTEST_ASSERT(*c == 77);

    vampDestroyMemoryPool(&pool);
}


VAMPTEST_TEST(pool_allocator, destroy_pool_with_active_allocations)
{
    VampMemoryPool *pool = vampCreateMemoryPool(VAMP_SIZEOF(int), 3);

    int num = 5;

    int *a = (int *)pool->malloc(pool, &num);
    int *b = (int *)pool->malloc(pool, &num);
    VAMPTEST_ASSERT(a != NULL && b != NULL);

    // Don't free 'a' or 'b'
    vampDestroyMemoryPool(&pool);

    VAMPTEST_ASSERT(pool == NULL);
}


VAMPTEST_TEST(pool_allocator, stress_test_alloc_free)
{
    VampMemoryPool *pool = vampCreateMemoryPool(VAMP_SIZEOF(int), 10);

    for (int i = 0; i < 100; ++i)
    {
        int value = i;
        int *ptr = (int *)pool->malloc(pool, &value);
        VAMPTEST_ASSERT(ptr != NULL);
        VAMPTEST_ASSERT(*ptr == value);

        pool->free(pool, ptr);
        VAMPTEST_ASSERT(pool->remainingSize(pool) == 10 * VAMP_SIZEOF(int));
    }

    VAMPTEST_ASSERT(pool->occupiedSize(pool) == 0);

    vampDestroyMemoryPool(&pool);
}


