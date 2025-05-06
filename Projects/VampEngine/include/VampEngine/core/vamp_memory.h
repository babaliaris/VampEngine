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

    /**
     * @brief Push data into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pSize The data size.
     * @param pValue The address of some data to be be copied.
     * 
     * @return A pointer to the start address of the data.
     */
    void *(*push)(struct VampMemoryStack *pThis, VAMP_SIZE_T pSize, void *pValue);

    /**
     * @brief Resets the stack (Without deleting the data.)
     * 
     * The Pointer of the stack gets reseted and every time you push
     * something new, the data are getting overitten.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * 
     */
    void  (*reset)(struct VampMemoryStack *pThis);

    /**
     * @brief Get the remaining size (in bytes) of the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * 
     * @return The remaining (free) size of the stack in bytes.
     */
    VAMP_SIZE_T (*remainingSize)(struct VampMemoryStack *pThis);

    /**
     * @brief Get the occupied (used) size (in bytes) of the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * 
     * @return The occupied (used) size of the stack in bytes.
     */
    VAMP_SIZE_T (*occupiedSize)(struct VampMemoryStack *pThis);

    /**
     * @brief Push a `char` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    char *(*pushChar)(struct VampMemoryStack *pThis, char pValue);

    /**
     * @brief Push a `float` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    float *(*pushFloat)(struct VampMemoryStack *pThis, float pValue);

    /**
     * @brief Push a `double` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    double *(*pushDouble)(struct VampMemoryStack *pThis, double pValue);

    /**
     * @brief Push a `VAMP_SIZE_T` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    VAMP_SIZE_T *(*pushSizet)(struct VampMemoryStack *pThis, VAMP_SIZE_T pValue);

    /**
     * @brief Push a `VAMP_INT8` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    VAMP_INT8 *(*pushInt8)(struct VampMemoryStack *pThis, VAMP_INT8 pValue);

    /**
     * @brief Push a `VAMP_INT16` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    VAMP_INT16 *(*pushInt16)(struct VampMemoryStack *pThis, VAMP_INT16 pValue);

    /**
     * @brief Push a `VAMP_INT32` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    VAMP_INT32 *(*pushInt32)(struct VampMemoryStack *pThis, VAMP_INT32 pValue);

    /**
     * @brief Push a `VAMP_INT64` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    VAMP_INT64 *(*pushInt64)(struct VampMemoryStack *pThis, VAMP_INT64 pValue);

    /**
     * @brief Push a `VAMP_UINT8` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    VAMP_UINT8 *(*pushUint8)(struct VampMemoryStack *pThis, VAMP_UINT8 pValue);

    /**
     * @brief Push a `VAMP_UINT16` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    VAMP_UINT16 *(*pushUint16)(struct VampMemoryStack *pThis, VAMP_UINT16 pValue);

    /**
     * @brief Push a `VAMP_UINT32` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    VAMP_UINT32 *(*pushUint32)(struct VampMemoryStack *pThis, VAMP_UINT32 pValue);

    /**
     * @brief Push a `VAMP_UINT64` into the stack.
     * 
     * @param pThis This `VampMemoryStack` instance.
     * @param pValue The value to be stored.
     * 
     * @return The start address of the data inside the stack.
     */
    VAMP_UINT64 *(*pushUint64)(struct VampMemoryStack *pThis, VAMP_UINT64 pValue);

}VampMemoryStack;


/**
 * @brief Create an instance of `VampMemoryStack`.
 * 
 * @param pSize The size (in bytes) of the stack.
 * 
 * @return The `VampMemoryStack` instance.
 */
VAMP_API VampMemoryStack *vampCreateMemoryStack(VAMP_SIZE_T pSize);

/**
 * @brief Destroy a `VampMemoryStack` instance.
 * 
 * @param pThis The users local variable that contains the `VampMemoryStack` instance.
 */
VAMP_API void vampDestroyMemoryStack(VampMemoryStack **pThis);




/**
 * @brief Memory Pool Allocator Block For Metadata.
 * 
 * You should not touch this. The engine will handle it.
 */
typedef struct __VampMemoryPoolBlock__
{
    struct __VampMemoryPoolBlock__ *m_next;

}__VampMemoryPoolBlock__;



/**
 * @brief Memory Pool Allocator.
 * 
 * A memory pool acts as a dynamic allocator (malloc-free)
 * but with a Single Size block! This means that, once you
 * create a pool, the block allocation size is determined from 
 * the start!
 */
typedef struct VampMemoryPool
{
    VAMP_SIZE_T m_user_block_size; ///< The users block size.
    VAMP_SIZE_T m_user_block_count; ///< The users request amount of blocks.
    VAMP_SIZE_T m_buffer_size; ///< The actual buffer size.
    VAMP_SIZE_T m_block_size; ///< The full block size (including metadata).
    VAMP_SIZE_T m_blocks_in_used; ///< How many blocks are in use.
    char        *m_buffer; ///< The actual buffer that holds the data.
    char        *m_nextFreeBlock; ///< Next free block pointer.
    char        *m_lastDirtyBlock; ///< Last dirty block (Thas was never initialized).

    /**
     * @brief Allocate a new block of `m_user_block_size`.
     * 
     * @param pThis The `VampMemoryPool` instance!
     * @param pData The address of some data to initialize the allocation.
     * 
     * @return The start address of the newly allocated data.
     */
    void *(*malloc)(struct VampMemoryPool *pThis, void *pData);

    /**
     * @brief Frees a block.
     * 
     * @param pThis The `VampMemoryPool` instance!
     * @param pPtr The memory block to be freed.
     */
    void (*free)(struct VampMemoryPool *pThis, void *pPtr);

    /**
     * @brief Information about the remaining free size in bytes.
     * 
     * @param pThis The `VampMemoryPool` instance!
     * 
     * @return The remaining free size of the pool in bytes.
     */
    VAMP_SIZE_T (*remainingSize)(struct VampMemoryPool *pThis);

    /**
     * @brief Information about the occupied (in use) size in bytes.
     * 
     * @param pThis The `VampMemoryPool` instance!
     * 
     * @return The occupied (in use) size of the pool in bytes.
     */
    VAMP_SIZE_T (*occupiedSize)(struct VampMemoryPool *pThis);

}VampMemoryPool;


/**
 * @brief Create a new instance of `VampMemoryPool`.
 * 
 * @param pBlockSize The block size of each block.
 * @param pCount The total amount of blocks which determined the size of the pool.
 * 
 * @return The newly created `VampMemoryPool` instance.
 */
VampMemoryPool *vampCreateMemoryPool(VAMP_SIZE_T pBlockSize, VAMP_SIZE_T pCount);

/**
 * @brief Destroys an instance of `VampMemoryPool`.
 * 
 * @param pThis The users local variable that holds the instance of `VampMemoryPool`.
 */
void vampDestroyMemoryPool(VampMemoryPool **pThis);

#endif
