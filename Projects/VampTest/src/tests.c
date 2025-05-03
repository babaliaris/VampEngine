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
    VAMPTEST_START(vamp_app);

    VAMPTEST_REGISTER(vamp_app, math, add);
    VAMPTEST_REGISTER(vamp_app, math, subtract);
    VAMPTEST_REGISTER(vamp_app, math, mult);

    VAMPTEST_END(vamp_app);

    return 0;
}