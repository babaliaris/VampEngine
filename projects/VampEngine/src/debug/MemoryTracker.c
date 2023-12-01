#include <VampPCH.h>
#include <VampString.h>
#include "MemoryTracker.h"
#include <data-structures/list.h>


char RemoveTrackerDataConditionCallback(void *trackerData, void *pointer)
{
    VampMemoryTrackerData *d = (VampMemoryTrackerData *)trackerData;

    return (d->__point_in_memory__ == pointer);
}


void VampMemoryTrackerPush(VampMemoryTracker *tracker, void * pointer, const char *filepath, unsigned int line)
{
    VampMemoryTrackerData *data = VampNewMemoryTrackerData(pointer, filepath, line);

    tracker->__list__->Append(tracker->__list__, data);
}

void VampMemoryTrackerRemove(VampMemoryTracker *tracker, void *pointer)
{
    tracker->__list__->RemoveByCondition(tracker->__list__, RemoveTrackerDataConditionCallback, pointer);
}


void VampMemoryTrackerWriteFile(VampMemoryTracker *tracker, const char *filename)
{
    if (!tracker) return;

    FILE *file = fopen(filename, "w");

    if (!file)
    {
        printf("Failed to open the memory tracker file.\n\n");
        return;
    }

    //Write the file only if the list is not empty.
    if ( !tracker->__list__->IsEmpty(tracker->__list__) )
    {
        //Loop through the list.
        for (unsigned int i = 0; i < tracker->__list__->__length__; i++)
        {
            VampMemoryTrackerData *data = (VampMemoryTrackerData *)tracker->__list__->GetAt(tracker->__list__, i);

            fprintf(file, "%s:%d\n", data->__filepath__->__str__, data->__line_number__);
        }
    }

    if ( file && fclose(file) != 0 ) printf("Failed to close the memory tracker file.\n\n");
}









VampMemoryTracker *VampNewMemoryTracker()
{
    VampMemoryTracker *new_tracker = (VampMemoryTracker *)malloc(sizeof(VampMemoryTracker));

    new_tracker->__list__               = VampNewList();
    new_tracker->Push                   = VampMemoryTrackerPush;
    new_tracker->Remove                 = VampMemoryTrackerRemove;
    new_tracker->WriteMemoryLeaksFile   = VampMemoryTrackerWriteFile;

    return new_tracker;
}



void VampListDeconstructor(void *data)
{
    VampMemoryTrackerData *d = (VampMemoryTrackerData *)data;

    VampDestroyMemoryTrackerData(d);
}


void VampDestroyMemoryTracker(VampMemoryTracker *tracker)
{
    if (!tracker) return;

    VampDestroyList(tracker->__list__, VampListDeconstructor);

    free(tracker);
}

VampMemoryTrackerData *VampNewMemoryTrackerData(void *pointer, const char *filepath, unsigned int line)
{
    VampMemoryTrackerData *new_data = (VampMemoryTrackerData *)malloc(sizeof(VampMemoryTrackerData));

    new_data->__filepath__          = VampNewString(filepath);
    new_data->__line_number__       = line;
    new_data->__point_in_memory__   = pointer;

    return new_data;
}

void VampDestroyMemoryTrackerData(VampMemoryTrackerData *data)
{
    if (!data) return;

    VampDestroyString(data->__filepath__);
    free(data);
}