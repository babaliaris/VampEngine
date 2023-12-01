#include <VampTest/VampTest.h>
#include <debug/MemoryTracker.h>


VAMP_TEST(MemoryTracker, CheckMallocAndFreeBalance)
{
    char *VAMP_MALLOC(char1, sizeof(char));
    VAMP_EXPECT(VampGlobalGetMemoryTracker()->__list__->GetLength(VampGlobalGetMemoryTracker()->__list__) == 1, "The trackers list should have 1 element at this point.");

    char * VAMP_MALLOC(char2, sizeof(char));
    VAMP_EXPECT(VampGlobalGetMemoryTracker()->__list__->GetLength(VampGlobalGetMemoryTracker()->__list__) == 2, "The trackers list should have 2 elements at this point.");

    VAMP_FREE(char2);
    VAMP_EXPECT(VampGlobalGetMemoryTracker()->__list__->GetLength(VampGlobalGetMemoryTracker()->__list__) == 1, "The trackers list should have 1 element at this point.");

    VAMP_FREE(char1);
    VAMP_EXPECT( VampGlobalGetMemoryTracker()->__list__->IsEmpty(VampGlobalGetMemoryTracker()->__list__) , "The trackers list should be empty." );
}


VAMP_TEST(MemoryTracker, WriteMemoryLeaksToFile)
{

    char *VAMP_MALLOC(char1, sizeof(char));
    char *VAMP_MALLOC(char2, sizeof(char));

    //Since char1 and char2 have not been freed, the call to WriteMemoryLeaksFile() should write something.
    VampGlobalGetMemoryTracker()->WriteMemoryLeaksFile(VampGlobalGetMemoryTracker(), "testing.leaks.txt");

    FILE *file = fopen("testing.leaks.txt", "r");

    VAMP_EXPECT(  file != NULL , "The file should exist at this point. \
    (Also make sure that the location from where you are running the tests, have write and read access.)" );

    if (file) fclose(file);

    VAMP_FREE(char1);
    VAMP_FREE(char2);
}