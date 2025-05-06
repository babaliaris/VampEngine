#ifndef VAMP_MEMORY_H
#define VAMP_MEMORY_H
#include <VampEngine/core/vamp_std.h>
#include <VampEngine/core/vamp_platform.h>

/**
 * @file
 * @brief This file contains usefull tools for memory management!
 * 
 * @author Babaliaris Nikolaos
 * @date 05 May 2025
 */



#ifdef VAMP_DEBUG

    #define VAMP_ALLOC_MAGIC 0xDEADBEEFDEADBEEF

    /**
     * @brief Metadata that reside above the actuall memory allocation.
     * 
     * How it will look in memory: [METADATA][USER_MEMORY][MAGIC_NUMBER_FOOTER]
     * The memory blocks are interconnected, forming a double linked list. At
     * the shutdown of the application, we loop through the list to retrieve 
     * memory leaks related information.
     */
    typedef struct VampAllocationMetadata
    {
        VAMP_UINT64 m_magic_number; ///< It tells us that this is a memory block.
        const char *m_filename; ///< The file where the allocation happened.
        const char *m_function_name; ///< The function where the allocation happened.
        VAMP_SIZE_T m_line; ///< The line in the filename, where the allocation happened.
        VAMP_SIZE_T m_user_size; ///< The size that the user asked to allocate.

        struct VampAllocationMetadata *m_next; ///< Next memory allocation.
        struct VampAllocationMetadata *m_prev; ///< Previous memory allocation.
    }VampAllocationMetadata;


    /**
     * @brief The memory debbuger.
     * 
     * The purpose of this, is to implement a basic double linked list
     * using VampAllocationMetadata as the Node. Actually the full allocation
     * including the users size, consists the node of this list. 
     * 
     * Full memory allocation: [MAGIC_NUMBER][METADATA][USER_SPACE][MAGIC_NUMBER]
     * 
     * The engine will define `VAMP_MEMORY_DEBUGGER_GLOBAL_INSTANCE`
     * inside `vampCreateApplication()` and a global variable
     * `VAMP_GLOBAL_MEMORY_DEBUGGER` will be available, that is being
     * used automatically by the `VAMP_MALLOC` and `VAMP_FREE` macros.
     */
    typedef struct VampMemoryDebugger
    {
        VAMP_SIZE_T m_total_allocations; ///< The length of the list.

        VampAllocationMetadata *m_head; ///< The first node of the list.
        VampAllocationMetadata *m_tail; ///< The last node of the list

        /**
         * @brief Allocates a new memory in the heap and returns the user pointer.
         * 
         * Memory: [MAGIC][METADATA][USERSPACE][MAGIC]
         * The returned pointer, points at the start address of [USERSPACE] and
         * of the allocated block!!!
         * 
         * @param pSize The requested allocation size (in bytes) by the user.
         * @param pFilename The filename from where malloc was called.
         * @param pFuncName The function name from where malloc was called.
         * @param pLine The line number from where malloc was called.
         * 
         * @return A pointer to the start address of the USERSPCACE block.
        */
        void *(*malloc)( VAMP_SIZE_T pSize, const char *pFilename, 
                        const char *pFuncName, VAMP_SIZE_T pLine
        );

        /**
         * @brief Frees the memory block and disconnects it from the list.
         * 
         * @param pUserPtr
         */
        void (*free)(void *pUserPtr);

        /**
         * @brief If the list is not empty, it reports memory leaks.
         */
        void (*checkForLeaks)(void);

    }VampMemoryDebugger;


    /**
     * @brief define VAMP_MEMORY_DEBUGGER_GLOBAL_INSTANCE if you use this standalone.
     * 
     * This is defined automatically inside vamp_application.h, but if you want
     * to use this file somewhere outside a VampEngine application, then you MUST
     * define VAMP_MEMORY_DEBUGGER_GLOBAL_INSTANCE in ONLY ONE .c or .cpp file!!!
     */
    #ifndef VAMP_MEMORY_DEBUGGER_GLOBAL_INSTANCE
        VAMP_API extern VampMemoryDebugger VAMP_GLOBAL_MEMORY_DEBUGGER;
    #else
        VampMemoryDebugger VAMP_GLOBAL_MEMORY_DEBUGGER;
    #endif


    /**
     * Initializes the memory debbuger. Must be called ONLY ONCE inside
     * an ifdef VAMP_DEBUG endif preprocessor statement.
     */
    void vampMemoryDebuggerInit();


    #define VAMP_MALLOC(size)\
        VAMP_GLOBAL_MEMORY_DEBUGGER.malloc(size, __FILE__, __func__, __LINE__)

    #define VAMP_FREE(ptr)\
        VAMP_GLOBAL_MEMORY_DEBUGGER.free(ptr)



//In release or dist modes, just use the classic allocation functions.
#else
    #define VAMP_MALLOC(size)\
        vampMalloc( size )

    #define VAMP_FREE(ptr)\
        vampFree( ptr )
#endif



/**
 * @brief Memory Stack Allocator Class
 * 
 * Create a instance of this class using `vampCreateMemoryStack`
 * and `vampDestroyMemoryStack` to destroy it. This creates a stack
 * memory block, that you can use in order to push data into it.
 * You cannot pop data, but you always get a pointer back to the data
 * every time use push something. This stack is meant to be push only
 * and be reseted by the user, depending on the life of the stack.
 * 
 * Example: Once per frame life duration. You push data / frame into the
 * stack, and at the end of each frame, you reset the stack (deleting everythnig).
 * This is good for frame operations (vertex buffers that change each frame, 
 * uniform buffers, particle system buffers etc since they change every frame).
 */
typedef struct VampMemoryStack
{
    VAMP_SIZE_T  m_size;
    VAMP_SIZE_T  m_pointer;
    char        *m_buffer;

    void *(*push)(struct VampMemoryStack *pThis, VAMP_SIZE_T pSize, void *pValue);

    void  (*reset)(struct VampMemoryStack *pThis);

    VAMP_SIZE_T (*remainingSize)(struct VampMemoryStack *pThis);

    VAMP_SIZE_T (*occupiedSize)(struct VampMemoryStack *pThis);

    char *(*pushChar)(struct VampMemoryStack *pThis, char pValue);

    float *(*pushFloat)(struct VampMemoryStack *pThis, float pValue);

    double *(*pushDouble)(struct VampMemoryStack *pThis, double pValue);

    VAMP_SIZE_T *(*pushSizet)(struct VampMemoryStack *pThis, VAMP_SIZE_T pValue);

    VAMP_INT8 *(*pushInt8)(struct VampMemoryStack *pThis, VAMP_INT8 pValue);

    VAMP_INT16 *(*pushInt16)(struct VampMemoryStack *pThis, VAMP_INT16 pValue);

    VAMP_INT32 *(*pushInt32)(struct VampMemoryStack *pThis, VAMP_INT32 pValue);

    VAMP_INT64 *(*pushInt64)(struct VampMemoryStack *pThis, VAMP_INT64 pValue);

    VAMP_UINT8 *(*pushUint8)(struct VampMemoryStack *pThis, VAMP_UINT8 pValue);

    VAMP_UINT16 *(*pushUint16)(struct VampMemoryStack *pThis, VAMP_UINT16 pValue);

    VAMP_UINT32 *(*pushUint32)(struct VampMemoryStack *pThis, VAMP_UINT32 pValue);

    VAMP_UINT64 *(*pushUint64)(struct VampMemoryStack *pThis, VAMP_UINT64 pValue);

}VampMemoryStack;


VAMP_API VampMemoryStack *vampCreateMemoryStack(VAMP_SIZE_T pSize);

VAMP_API void vampDestroyMemoryStack(VampMemoryStack **pThis);


typedef struct __VampMemoryPoolBlock__
{
    struct __VampMemoryPoolBlock__ *m_next;

}__VampMemoryPoolBlock__;

typedef struct VampMemoryPool
{
    VAMP_SIZE_T m_user_block_size;
    VAMP_SIZE_T m_user_block_count;
    VAMP_SIZE_T m_buffer_size;
    char        *m_buffer;
    char        *m_nextFreeBlock;
    char        *m_lastDirtyBlock;

    void *(*malloc)(struct VampMemoryPool *pThis, void *data);

    void (*free)(struct VampMemoryPool *pThis, void *ptr);

}VampMemoryPool;

VampMemoryPool *vampCreateMemoryPool(VAMP_SIZE_T pBlockSize, VAMP_SIZE_T pCount);

void vampDestroyMemoryPool(VampMemoryPool **pThis);

#endif
