#include <VampPCH.h>
#include "MemoryTracker.h"
#include <sds.h>



//List
/*=======================Its Important that MemoryTracker will have it's OWN List Implementation.=======================*/
__VampMemoryTrackerListNode__ *VampNewMemoryTrackerListNode(void *data)
{
    __VampMemoryTrackerListNode__ *new_node = malloc( sizeof(__VampMemoryTrackerListNode__) );

    new_node->__next__ = NULL;
    new_node->__prev__ = NULL;
    new_node->__data__ = data;

    return new_node;
}


void VampDestroyMemoryTrackerListNode(__VampMemoryTrackerListNode__ *listNode)
{
    if (!listNode) return;
    free(listNode);
}


static void ListAppend(VampMemoryTrackerList *vampList, void *data)
{
    if (!vampList || !data) return;

    __VampMemoryTrackerListNode__ *new_node = VampNewMemoryTrackerListNode(data);

    if ( vampList->IsEmpty(vampList) )
    {
        vampList->__head__->__next__ = new_node;
        vampList->__tail__->__prev__ = new_node;

        new_node->__next__ = vampList->__tail__;
        new_node->__prev__ = vampList->__head__;
    }

    else
    {
        new_node->__next__ = vampList->__tail__;
        new_node->__prev__ = vampList->__tail__->__prev__;

        vampList->__tail__->__prev__->__next__  = new_node;
        vampList->__tail__->__prev__            = new_node;
    }

    vampList->__length__++;
}


static void *ListGetAt(VampMemoryTrackerList *vampList, unsigned int position)
{
    if (!vampList) return NULL;

    unsigned int i = 0;
    __VampMemoryTrackerListNode__ *current = vampList->__head__->__next__;

    while(current && current->__next__)
    {
        if (i == position) return current->__data__;

        current = current->__next__;
        i++;
    }

    return NULL;
}


static void *ListRemoveAt(VampMemoryTrackerList *vampList, unsigned int position)
{
    if (!vampList) return NULL;

    unsigned int i = 0;
    __VampMemoryTrackerListNode__ *current = vampList->__head__->__next__;

    //Loop through the list.
    while(current && current->__next__)
    {
        if (i == position)
        {
            //The list has one element.
            if (vampList->__length__ == 1)
            {
                current->__next__ = NULL;
                current->__prev__ = NULL;

                vampList->__head__->__next__ = NULL;
                vampList->__tail__->__prev__ = NULL;
            }


            //The list has more than 1 elements.
            else
            {
                current->__next__->__prev__ = current->__prev__;
                current->__prev__->__next__ = current->__next__;
            }

            vampList->__length__--;

            void *data = current->__data__;

            VampDestroyMemoryTrackerListNode(current);

            //Return the data to the user, so he can free them if necessary.
            return data;
        }

        current = current->__next__;
        i++;
    }

    return NULL;
}


static char ListIsEmpty(VampMemoryTrackerList *vampList)
{
    if (!vampList) return 0;

    return (!vampList->__head__->__next__ && !vampList->__tail__->__prev__);
}


static unsigned int ListGetLength(VampMemoryTrackerList *vampList)
{
    if (!vampList) return 0;

    return vampList->__length__;
}


static void *ListRemoveByCondition(struct VampMemoryTrackerList *vampList, VampMemoryTrackerListConditionFunc condFunc, void *cond)
{
    if (!vampList || !condFunc) return NULL;

    __VampMemoryTrackerListNode__ *current = vampList->__head__->__next__;

    //Loop through the list.
    while(current && current->__next__)
    {
        if ( condFunc(current->__data__, cond)  )
        {
            //The list has one element.
            if (vampList->__length__ == 1)
            {
                current->__next__ = NULL;
                current->__prev__ = NULL;

                vampList->__head__->__next__ = NULL;
                vampList->__tail__->__prev__ = NULL;
            }


            //The list has more than 1 elements.
            else
            {
                current->__next__->__prev__ = current->__prev__;
                current->__prev__->__next__ = current->__next__;
            }

            vampList->__length__--;

            void *data = current->__data__;

            VampDestroyMemoryTrackerListNode(current);

            return data;
        }

        current = current->__next__;
    }

    return NULL;
}


static void *ListGetByCondition(VampMemoryTrackerList *vampList, VampMemoryTrackerListConditionFunc condFunc, void *cond)
{
    if (!vampList || !condFunc) return NULL;

    __VampMemoryTrackerListNode__ *current = vampList->__head__->__next__;

    //Loop through the list.
    while(current && current->__next__)
    {
        if ( condFunc(current->__data__, cond)  )
            return current->__data__;

        current = current->__next__;
    }

    return NULL;
}


VampMemoryTrackerList *VampNewMemoryTrackerList()
{
    VampMemoryTrackerList *new_list = malloc( sizeof(VampMemoryTrackerList) );

    new_list->__head__ = VampNewMemoryTrackerListNode(NULL);
    new_list->__tail__ = VampNewMemoryTrackerListNode(NULL);

    new_list->__length__ = 0;

    new_list->Append                = ListAppend;
    new_list->GetAt                 = ListGetAt;
    new_list->RemoveAt              = ListRemoveAt;
    new_list->IsEmpty               = ListIsEmpty;
    new_list->GetLength             = ListGetLength;
    new_list->RemoveByCondition     = ListRemoveByCondition;
    new_list->GetByCondition        = ListGetByCondition;

    return new_list;
}

void VampDestroyMemoryTrackerList(VampMemoryTrackerList *vampList, VampMemoryTrackerListDestroyCallback callback)
{
     if (!vampList) return;

    __VampMemoryTrackerListNode__ *current   = vampList->__head__->__next__;
    __VampMemoryTrackerListNode__ *temp      = current;

    while(current && current->__next__)
    {
        //Call users callback, so he can destroy the data.
        if (callback) callback(current->__data__);

        current = current->__next__;
        VampDestroyMemoryTrackerListNode(temp);
        temp = current;
    }

    VampDestroyMemoryTrackerListNode(vampList->__head__);
    VampDestroyMemoryTrackerListNode(vampList->__tail__);

    free(vampList);
}
/*=======================Its Important that MemoryTracker will have it's OWN List Implementation.=======================*/
















/*===================================================== Memory Tracker===================================================*/
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

            fprintf(file, "%s:%d\n", data->__filepath__, data->__line_number__);
        }
    }

    if ( file && fclose(file) != 0 ) printf("Failed to close the memory tracker file.\n\n");
}









VampMemoryTracker *VampNewMemoryTracker()
{
    VampMemoryTracker *new_tracker = (VampMemoryTracker *)malloc(sizeof(VampMemoryTracker));

    new_tracker->__list__               = VampNewMemoryTrackerList();
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

    VampDestroyMemoryTrackerList(tracker->__list__, VampListDeconstructor);

    free(tracker);
}

VampMemoryTrackerData *VampNewMemoryTrackerData(void *pointer, const char *filepath, unsigned int line)
{
    VampMemoryTrackerData *new_data = (VampMemoryTrackerData *)malloc(sizeof(VampMemoryTrackerData));

    new_data->__filepath__          = sdsnew(filepath);
    new_data->__line_number__       = line;
    new_data->__point_in_memory__   = pointer;

    return new_data;
}

void VampDestroyMemoryTrackerData(VampMemoryTrackerData *data)
{
    if (!data) return;

    sdsfree(data->__filepath__);
    free(data);
}
/*===================================================== Memory Tracker===================================================*/
