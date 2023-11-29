#include <VampTest/VampTest.h>

VAMP_DECLARE_TEST(VampList, CreateAndDestroyTest);
VAMP_DECLARE_TEST(VampList, IsEmptyTest);
VAMP_DECLARE_TEST(VampList, AppendDataTest);
VAMP_DECLARE_TEST(VampList, GetAtTest);
VAMP_DECLARE_TEST(VampList, RemoveAtTest);
VAMP_DECLARE_TEST(VampList, RemoveByConditionTest);
VAMP_DECLARE_TEST(VampList, GetByConditionTest);


VAMP_TEST_FRAMEWORK(
    VAMP_REGISTER_TEST(VampList, CreateAndDestroyTest);
    VAMP_REGISTER_TEST(VampList, IsEmptyTest);
    VAMP_REGISTER_TEST(VampList, AppendDataTest);
    VAMP_REGISTER_TEST(VampList, GetAtTest);
    VAMP_REGISTER_TEST(VampList, RemoveAtTest);
    VAMP_REGISTER_TEST(VampList, RemoveByConditionTest);
    VAMP_REGISTER_TEST(VampList, GetByConditionTest);
);