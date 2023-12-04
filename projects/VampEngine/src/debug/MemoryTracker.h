#ifndef VAMP_ENGINE_MEMORY_H
#define VAMP_ENGINE_MEMORY_H


/**
 * @file
*/


//List
/*=======================Its Important that MemoryTracker will have it's OWN List Implementation.=======================*/
typedef char (*VampMemoryTrackerListConditionFunc)(void *data, void *cond); /**< @private*/
typedef void (*VampMemoryTrackerListDestroyCallback)(void *data); /**< @private*/


/**
 * @private
*/
typedef struct __VampMemoryTrackerListNode__
{
    struct __VampMemoryTrackerListNode__ *__next__;
    struct __VampMemoryTrackerListNode__ *__prev__;
    void *__data__;
}
__VampMemoryTrackerListNode__;


/**
 * @private
*/
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

/**
 * @private
*/
VampMemoryTrackerList *VampNewMemoryTrackerList();

/**
 * @private
*/
void VampDestroyMemoryTrackerList(VampMemoryTrackerList *vampList, VampMemoryTrackerListDestroyCallback callback);
/*=======================Its Important that MemoryTracker will have it's OWN List Implementation.=======================*/






/*===================================================== Memory Tracker===================================================*/
typedef char * sds;

/**
 * @private
*/
typedef struct VampMemoryTrackerData
{
    sds __filepath__;
    unsigned int __line_number__;
    void *__point_in_memory__;
}
VampMemoryTrackerData;



/**
 * Memory tracker object structure.
 * 
*/
typedef struct VampMemoryTracker
{
    /**
     * Push the location = "file:line" where the allocation has happened.
     * 
     * @param[in] tracker The memory tracker object.
     * @param[in] pointer The actual memory address that returned by malloc.
     * @param[in] filepath The __FILE__ where the allocation has happened.
     * @param[in] line The line number where the allocation has happened.
    */
    void (*Push)(struct VampMemoryTracker *tracker, void *pointer, const char *filepath, unsigned int line);


    /**
     * Remove the "file:line" where an allocation has happened, because the memory has been freed.
     * 
     * @param[in] tracker The memory tracker object.
     * @param[in] pointer The actual memory address that was freed.
    */
    void (*Remove)(struct VampMemoryTracker *tracker, void *pointer);


     /**
     * Write a log file that contains entries of filepath:line seperated by the new line character.
     * If there are no memory leaks, this file should be empty.
     * 
     * @param[in] tracker The memory tracker object.
     * @param[in] filename The filename to be created.
    */
    void (*WriteMemoryLeaksFile)(struct VampMemoryTracker *tracker, const char *filename);


    VampMemoryTrackerList *__list__; /**< @private*/
}
VampMemoryTracker;


/**
 * Creates a new VampMemoryTracker object.
 * 
 * @returns The newly created object.
*/
VampMemoryTracker *VampNewMemoryTracker();


/**
 * Destroys the VampMemoryTracker object.
 * 
 * @param[in] tracker The object to be destroyed.
*/
void VampDestroyMemoryTracker(VampMemoryTracker *tracker);


/**
 * @private
*/
VampMemoryTrackerData *VampNewMemoryTrackerData(void *pointer, const char *filepath, unsigned int line);


/**
 * @private
*/
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
