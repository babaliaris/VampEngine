#ifndef VAMP_ENGINE_MEMORY_H
#define VAMP_ENGINE_MEMORY_H

typedef struct VampList VampList;
typedef struct VampString VampString;

typedef struct VampMemoryTrackerData
{
    VampString *__filepath__;
    unsigned int __line_number__;
    void *__point_in_memory__;
}
VampMemoryTrackerData;



typedef struct VampMemoryTracker
{
    VampList *__list__;

    void (*Push)(struct VampMemoryTracker *tracker, void *pointer, const char *filepath, unsigned int line);
    void (*Remove)(struct VampMemoryTracker *tracker, void *pointer);
    void (*WriteMemoryLeaksFile)(struct VampMemoryTracker *tracker, const char *filename);
}
VampMemoryTracker;


VampMemoryTracker *VampNewMemoryTracker();

void VampDestroyMemoryTracker(VampMemoryTracker *tracker);

VampMemoryTrackerData *VampNewMemoryTrackerData(void *pointer, const char *filepath, unsigned int line);

void VampDestroyMemoryTrackerData(VampMemoryTrackerData *data);


#ifdef VAMP_MEMORY_TRACKER_INIT
VampMemoryTracker *VAMP_GLOBAL_MEMORY_TRACKER;
#endif

VampMemoryTracker *VampGlobalGetMemoryTracker();


#define VAMP_MALLOC(variable, size)\
    variable = malloc( size );\
    VampGlobalGetMemoryTracker()->Push(VampGlobalGetMemoryTracker(), variable, __FILE__, __LINE__)

#define VAMP_FREE(pointer)\
    VampGlobalGetMemoryTracker()->Remove(VampGlobalGetMemoryTracker(), pointer);\
    free(pointer)


#endif