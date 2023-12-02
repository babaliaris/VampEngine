#ifndef VAMP_ENGINE_MEMORY_H
#define VAMP_ENGINE_MEMORY_H


//List
/*=======================Its Important that MemoryTracker will have it's OWN List Implementation.=======================*/
typedef char (*VampMemoryTrackerListConditionFunc)(void *data, void *cond);
typedef void (*VampMemoryTrackerListDestroyCallback)(void *data);


typedef struct __VampMemoryTrackerListNode__
{
    struct __VampMemoryTrackerListNode__ *__next__;
    struct __VampMemoryTrackerListNode__ *__prev__;
    void *__data__;
}
__VampMemoryTrackerListNode__;


typedef struct VampMemoryTrackerList
{
    __VampMemoryTrackerListNode__ *__head__;
    __VampMemoryTrackerListNode__ *__tail__;
    unsigned int __length__;

    void (*Append)(struct VampMemoryTrackerList *vampList, void *data);

    void *(*GetAt)(struct VampMemoryTrackerList *vampList, unsigned int position);

    void *(*RemoveAt)(struct VampMemoryTrackerList *vampList, unsigned int position);

    char (*IsEmpty)(struct VampMemoryTrackerList *vampList);

    unsigned int (*GetLength)(struct VampMemoryTrackerList *vampList);

    void *(*RemoveByCondition)(struct VampMemoryTrackerList *vampList, VampMemoryTrackerListConditionFunc condFunc, void *cond);

    void *(*GetByCondition)(struct VampMemoryTrackerList *vampList, VampMemoryTrackerListConditionFunc condFunc, void *cond);
}
VampMemoryTrackerList;


VampMemoryTrackerList *VampNewMemoryTrackerList();


void VampDestroyMemoryTrackerList(VampMemoryTrackerList *vampList, VampMemoryTrackerListDestroyCallback callback);
/*=======================Its Important that MemoryTracker will have it's OWN List Implementation.=======================*/






/*===================================================== Memory Tracker===================================================*/
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
    VampMemoryTrackerList *__list__;

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



#ifdef VAMP_DEBUG
    #define VAMP_MALLOC(variable, size)\
        variable = malloc( size );\
        VampGlobalGetMemoryTracker()->Push(VampGlobalGetMemoryTracker(), variable, __FILE__, __LINE__)

    #define VAMP_FREE(pointer)\
        VampGlobalGetMemoryTracker()->Remove(VampGlobalGetMemoryTracker(), pointer);\
        free(pointer)

#else
    #define VAMP_MALLOC(variable, size) variable = malloc( size )
    #define VAMP_FREE(pointer) free(pointer)

#endif


#endif
/*===================================================== Memory Tracker===================================================*/
