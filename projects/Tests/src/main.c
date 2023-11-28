#include <VampTest/VampTest.h>

VAMP_TEST(TestingSuite, TestingTest)
{
    VAMP_EXPECT(1==1, "1 should be equal to 1");
}


VAMP_TEST_FRAMEWORK(
    VAMP_REGISTER_TEST(TestingSuite, TestingTest);
);