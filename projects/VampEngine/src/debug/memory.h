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


#define VAMP_MALLOC(variable, size, memory_tracker)\
    variable = malloc( size );\
    memory_tracker->Push(memory_tracker, variable, __FILE__, __LINE__)

#define VAMP_FREE(memory_tracker, pointer)\
    memory_tracker->Remove(memory_tracker, pointer);\
    free(pointer)


#endif