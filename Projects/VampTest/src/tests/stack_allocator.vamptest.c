#include <VampTest/vamptest.h>
#include <VampEngine/core/vamp_memory.h>

#define VAMPTEST_PUSH_TYPE_AND_CHECK(TYPE, FUNC_SUFFIX, VALUE)                     \
    do {                                                                           \
        VAMP_SIZE_T size = VAMP_SIZEOF(TYPE);                                      \
        VampMemoryStack *stack = vampCreateMemoryStack(size);                      \
                                                                                   \
        TYPE *ptr = stack->push##FUNC_SUFFIX(stack, (TYPE)(VALUE));                \
        VAMPTEST_ASSERT(ptr != NULL);                                              \
        VAMPTEST_ASSERT(*ptr == (TYPE)(VALUE));                                    \
                                                                                   \
        VAMPTEST_ASSERT(stack->occupiedSize(stack) == size);                       \
        VAMPTEST_ASSERT(stack->remainingSize(stack) == 0);                         \
        VAMPTEST_ASSERT(stack->m_pointer == size);                                 \
                                                                                   \
        TYPE *fail = stack->push##FUNC_SUFFIX(stack, (TYPE)(VALUE));               \
        VAMPTEST_ASSERT(fail == NULL);                                             \
                                                                                   \
        vampDestroyMemoryStack(&stack);                                            \
        VAMPTEST_ASSERT(stack == NULL);                                            \
    } while (0)



VAMPTEST_TEST(stack_allocator, creation_and_deletion)
{
    VampMemoryStack *stack = vampCreateMemoryStack(100);

    VAMPTEST_ASSERT(stack->push != NULL);
    VAMPTEST_ASSERT(stack->reset != NULL);
    VAMPTEST_ASSERT(stack->remainingSize != NULL);
    VAMPTEST_ASSERT(stack->occupiedSize != NULL);
    VAMPTEST_ASSERT(stack->pushChar != NULL);
    VAMPTEST_ASSERT(stack->pushFloat != NULL);
    VAMPTEST_ASSERT(stack->pushDouble != NULL);
    VAMPTEST_ASSERT(stack->pushSizet != NULL);
    VAMPTEST_ASSERT(stack->pushInt8 != NULL);
    VAMPTEST_ASSERT(stack->pushInt16 != NULL);
    VAMPTEST_ASSERT(stack->pushInt32 != NULL);
    VAMPTEST_ASSERT(stack->pushInt64 != NULL);
    VAMPTEST_ASSERT(stack->pushUint8 != NULL);
    VAMPTEST_ASSERT(stack->pushUint16 != NULL);
    VAMPTEST_ASSERT(stack->pushUint32 != NULL);
    VAMPTEST_ASSERT(stack->pushUint64 != NULL);

    VAMPTEST_ASSERT(stack != NULL);
    VAMPTEST_ASSERT(stack->remainingSize(stack) == 100);
    VAMPTEST_ASSERT(stack->occupiedSize(stack) == 0);
    VAMPTEST_ASSERT(stack->m_size == 100);
    VAMPTEST_ASSERT(stack->m_pointer == 0);

    vampDestroyMemoryStack(&stack);

    VAMPTEST_ASSERT(stack == NULL);
}




VAMPTEST_TEST(stack_allocator, pushing_and_using_the_data)
{
    VAMP_SIZE_T buffer_size = VAMP_SIZEOF(float) * 2;

    VampMemoryStack *stack = vampCreateMemoryStack(buffer_size);

    float *num1 = stack->pushFloat(stack, 2.50f);
    float *num2 = stack->pushFloat(stack, 3.50f);

    VAMPTEST_ASSERT(*num1 == 2.50f);
    VAMPTEST_ASSERT(*num2 == 3.50f);
    VAMPTEST_ASSERT(stack->remainingSize(stack) == 0);
    VAMPTEST_ASSERT(stack->occupiedSize(stack) == buffer_size);
    VAMPTEST_ASSERT(stack->m_size == buffer_size);
    VAMPTEST_ASSERT(stack->m_pointer == buffer_size);
    VAMPTEST_ASSERT( (char *)num2 - (char *)num1 == VAMP_SIZEOF(float) );

    float *num3 = stack->pushFloat(stack, 6.50f);
    VAMPTEST_ASSERT(num3 == NULL);

    stack->reset(stack);
    VAMPTEST_ASSERT(stack->m_pointer == 0);
    VAMPTEST_ASSERT(stack->remainingSize(stack) == buffer_size);
    VAMPTEST_ASSERT(stack->occupiedSize(stack) == 0);

    vampDestroyMemoryStack(&stack);

    VAMPTEST_ASSERT(stack == NULL);
}


VAMPTEST_TEST(stack_allocator, push_various_types)
{
    VAMPTEST_PUSH_TYPE_AND_CHECK(char, Char, 'A');
    VAMPTEST_PUSH_TYPE_AND_CHECK(float, Float, 3.14f);
    VAMPTEST_PUSH_TYPE_AND_CHECK(double, Double, 6.28);
    VAMPTEST_PUSH_TYPE_AND_CHECK(VAMP_INT8, Int8, -8);
    VAMPTEST_PUSH_TYPE_AND_CHECK(VAMP_INT16, Int16, -16);
    VAMPTEST_PUSH_TYPE_AND_CHECK(VAMP_INT32, Int32, -32);
    VAMPTEST_PUSH_TYPE_AND_CHECK(VAMP_INT64, Int64, -64);
    VAMPTEST_PUSH_TYPE_AND_CHECK(VAMP_UINT8, Uint8, 8);
    VAMPTEST_PUSH_TYPE_AND_CHECK(VAMP_UINT16, Uint16, 16);
    VAMPTEST_PUSH_TYPE_AND_CHECK(VAMP_UINT32, Uint32, 32);
    VAMPTEST_PUSH_TYPE_AND_CHECK(VAMP_UINT64, Uint64, 64);
    VAMPTEST_PUSH_TYPE_AND_CHECK(VAMP_SIZE_T, Sizet, 12345);
}
