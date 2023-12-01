#define VAMP_MEMORY_TRACKER_INIT
#include <VampTest/VampTest.h>
#include <debug/MemoryTracker.h>

VampMemoryTracker *VampGlobalGetMemoryTracker()
{
    return VAMP_GLOBAL_MEMORY_TRACKER;
}


void VampRunBeforeAllTests()
{
    VAMP_GLOBAL_MEMORY_TRACKER = VampNewMemoryTracker();
}



void VampRunAfterAllTests()
{
    VampDestroyMemoryTracker(VAMP_GLOBAL_MEMORY_TRACKER);
}

VAMP_DECLARE_TEST(VampList, CreateAndDestroyTest);
VAMP_DECLARE_TEST(VampList, IsEmptyTest);
VAMP_DECLARE_TEST(VampList, AppendDataTest);
VAMP_DECLARE_TEST(VampList, GetAtTest);
VAMP_DECLARE_TEST(VampList, RemoveAtTest);
VAMP_DECLARE_TEST(VampList, RemoveByConditionTest);
VAMP_DECLARE_TEST(VampList, GetByConditionTest);
VAMP_DECLARE_TEST(VampList, DestroyListAndClearUserData);
VAMP_DECLARE_TEST(MemoryTracker, CheckMallocAndFreeBalance);
VAMP_DECLARE_TEST(MemoryTracker, WriteMemoryLeaksToFile);


VAMP_TEST_FRAMEWORK(
    VAMP_REGISTER_TEST(VampList, CreateAndDestroyTest);
    VAMP_REGISTER_TEST(VampList, IsEmptyTest);
    VAMP_REGISTER_TEST(VampList, AppendDataTest);
    VAMP_REGISTER_TEST(VampList, GetAtTest);
    VAMP_REGISTER_TEST(VampList, RemoveAtTest);
    VAMP_REGISTER_TEST(VampList, RemoveByConditionTest);
    VAMP_REGISTER_TEST(VampList, GetByConditionTest);
    VAMP_REGISTER_TEST(VampList, DestroyListAndClearUserData);
    VAMP_REGISTER_TEST(MemoryTracker, CheckMallocAndFreeBalance);
    VAMP_REGISTER_TEST(MemoryTracker, WriteMemoryLeaksToFile);
);