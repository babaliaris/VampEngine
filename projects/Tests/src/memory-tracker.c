#include <VampTest/VampTest.h>
#include <VampEngine.h>

VAMP_TEST(MemoryTracker, CreateAndDestroy)
{
    VampMemoryTracker *tracker = VampNewMemoryTracker();

    VampDestroyMemoryTracker(tracker);
}


VAMP_TEST(MemoryTracker, CheckMallocAndFreeBalance)
{
    VampMemoryTracker *tracker = VampNewMemoryTracker();

    char *VAMP_MALLOC(char1, sizeof(char), tracker);
    VAMP_EXPECT(tracker->__list__->GetLength(tracker->__list__) == 1, "The trackers list should have 1 element at this point.");

    char * VAMP_MALLOC(char2, sizeof(char), tracker);
    VAMP_EXPECT(tracker->__list__->GetLength(tracker->__list__) == 2, "The trackers list should have 2 elements at this point.");

    VAMP_FREE(tracker, char2);
    VAMP_EXPECT(tracker->__list__->GetLength(tracker->__list__) == 1, "The trackers list should have 1 element at this point.");

    VAMP_FREE(tracker, char1);
    VAMP_EXPECT( tracker->__list__->IsEmpty(tracker->__list__) , "The trackers list should be empty." );

    VampDestroyMemoryTracker(tracker);
}


VAMP_TEST(MemoryTracker, WriteMemoryLeaksToFile)
{
    VampMemoryTracker *tracker = VampNewMemoryTracker();

    char *VAMP_MALLOC(char1, sizeof(char), tracker);
    char *VAMP_MALLOC(char2, sizeof(char), tracker);

    tracker->WriteMemoryLeaksFile(tracker, "memory.leaks.txt");

    FILE *file = fopen("memory.leaks.txt", "r");

    VAMP_EXPECT(  file != NULL , "The file should exist at this point. \
    (Also make sure that the location from where you are running the tests, have write and read access.)" );

    if (file) fclose(file);

    VampDestroyMemoryTracker(tracker);
}