#define VAMP_MEMORY_TRACKER_INIT
#include <VampTest/VampTest.h>
#include <data-structures/list.h> //TODO Remove that and make a standalone list for the MemoryTracker!
#include <debug/MemoryTracker.h>


VampMemoryTracker *VampGlobalGetMemoryTracker()
{
    return VAMP_GLOBAL_MEMORY_TRACKER;
}



VAMP_TEST(MemoryTracker, CreateAndDestroy)
{
    VampMemoryTracker *tracker = VampNewMemoryTracker();

    VampDestroyMemoryTracker(tracker);
}


VAMP_TEST(MemoryTracker, CheckMallocAndFreeBalance)
{
    VAMP_GLOBAL_MEMORY_TRACKER = VampNewMemoryTracker();

    char *VAMP_MALLOC(char1, sizeof(char));
    VAMP_EXPECT(VAMP_GLOBAL_MEMORY_TRACKER->__list__->GetLength(VAMP_GLOBAL_MEMORY_TRACKER->__list__) == 1, "The trackers list should have 1 element at this point.");

    char * VAMP_MALLOC(char2, sizeof(char));
    VAMP_EXPECT(VAMP_GLOBAL_MEMORY_TRACKER->__list__->GetLength(VAMP_GLOBAL_MEMORY_TRACKER->__list__) == 2, "The trackers list should have 2 elements at this point.");

    VAMP_FREE(char2);
    VAMP_EXPECT(VAMP_GLOBAL_MEMORY_TRACKER->__list__->GetLength(VAMP_GLOBAL_MEMORY_TRACKER->__list__) == 1, "The trackers list should have 1 element at this point.");

    VAMP_FREE(char1);
    VAMP_EXPECT( VAMP_GLOBAL_MEMORY_TRACKER->__list__->IsEmpty(VAMP_GLOBAL_MEMORY_TRACKER->__list__) , "The trackers list should be empty." );

    VampDestroyMemoryTracker(VAMP_GLOBAL_MEMORY_TRACKER);
}


VAMP_TEST(MemoryTracker, WriteMemoryLeaksToFile)
{
    VAMP_GLOBAL_MEMORY_TRACKER = VampNewMemoryTracker();

    char *VAMP_MALLOC(char1, sizeof(char));
    char *VAMP_MALLOC(char2, sizeof(char));

    VAMP_GLOBAL_MEMORY_TRACKER->WriteMemoryLeaksFile(VAMP_GLOBAL_MEMORY_TRACKER, "memory.leaks.txt");

    FILE *file = fopen("memory.leaks.txt", "r");

    VAMP_EXPECT(  file != NULL , "The file should exist at this point. \
    (Also make sure that the location from where you are running the tests, have write and read access.)" );

    if (file) fclose(file);

    VampDestroyMemoryTracker(VAMP_GLOBAL_MEMORY_TRACKER);
}