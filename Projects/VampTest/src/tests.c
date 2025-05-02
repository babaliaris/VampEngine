#include <VampTest/vamptest.h>
#include <VampEngine/debug/vamp_assert.h>

VAMPTEST_TEST(math, add)
{
    VAMPTEST_ASSERT(1+1 == 0);
}

VAMPTEST_TEST(math, subtract)
{
    VAMPTEST_ASSERT(1-1 == 10);
}

VAMPTEST_TEST(math, mult)
{
    VAMPTEST_ASSERT(2*2 == 4);
}

int main()
{   
    VAMPTEST_START();

    VAMPTEST_REGISTER(math, add);
    VAMPTEST_REGISTER(math, subtract);
    VAMPTEST_REGISTER(math, mult);

    VAMPTEST_END();

    return 0;
}