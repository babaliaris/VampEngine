#include <VampTest/vamptest.h>

VAMPTEST_TEST(math, add)
{
    VAMPTEST_TEST_ASSERT(1 == 0, "MESSAGE");
}


VAMPTEST_TEST(math, subtract)
{
    VAMPTEST_TEST_ASSERT(1 == 1, "MESSAGE");
}

int main()
{
    VAMPTEST_START();

    VAMPTEST_REGISTER_TEST(math, add);
    VAMPTEST_REGISTER_TEST(math, subtract);

    VAMPTEST_END();
    return 0;
}
