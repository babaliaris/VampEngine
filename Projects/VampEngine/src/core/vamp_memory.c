#include <VampEngine/core/vamp_memory.h>
#include <VampEngine/debug/vamp_assert.h>
#include <VampEngine/core/vamp_platform.h>

#ifdef VAMP_DEBUG
static void *mallocImpl( VAMP_SIZE_T pSize, const char *pFilename, 
    const char *pFuncName, VAMP_SIZE_T pLine
)
{
    //Make sure the alignment is correct.
    #if VAMP_ALL_PC_PLATFORMS
    VAMP_ASSERT( alignof(VampAllocationMetadata) <= alignof(max_align_t), "Wrong Alignment" );
    #endif

    //Allocate a block large enought for:
    //  VampAllocationMetadata
    //  The users memory (determined by size)
    //  64 bits at the end of the block for the magic number.
    VampAllocationMetadata *new_node = 
    (VampAllocationMetadata *)vampMalloc( VAMP_SIZEOF(VampAllocationMetadata) + pSize + VAMP_SIZEOF(VAMP_UINT64) );

    VAMP_ASSERT(new_node != NULL, "Out Of Memory");

    //Initialize the metadata.
    new_node->m_magic_number    = VAMP_ALLOC_MAGIC;
    new_node->m_filename        = pFilename;
    new_node->m_function_name   = pFuncName;
    new_node->m_line            = pLine;
    new_node->m_user_size       = pSize;
    new_node->m_next            = NULL;
    new_node->m_prev            = NULL;

    //Add the magic number at the end of the allocation block.
    VAMP_UINT64 *ptr_to_magic_number    = (VAMP_UINT64 *)( (char *)new_node + VAMP_SIZEOF(VampAllocationMetadata) + pSize );
    *ptr_to_magic_number                = VAMP_ALLOC_MAGIC;

    //The allocation list is empty.
    if (VAMP_GLOBAL_MEMORY_DEBUGGER.m_head == NULL)
    {
        VAMP_GLOBAL_MEMORY_DEBUGGER.m_head = new_node;
        VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail = new_node;
    }

    //Push at the end of the list.
    else
    {
        VampAllocationMetadata *tail = VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail;

        tail->m_next        = new_node;
        new_node->m_prev    = tail;

        VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail = new_node;
    }

    //Increase the number of total allocations.
    VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations++;

    //Get the user pointer.
    char *userPtr = (char *)new_node + VAMP_SIZEOF(VampAllocationMetadata);

    //Initialize the users memory to zeros.
    char *tempUserPtrForLoop = userPtr;
    for (VAMP_SIZE_T i = 0; i < pSize; i++)
    {
        *tempUserPtrForLoop = 0;
         tempUserPtrForLoop++;
    }

    return (void *)userPtr;
}



static void freeImpl(void *pUserPtr)
{
    if (!pUserPtr) return;

    //The list can't be empty if at least one allocation has occured!
    //If it is empty and pUserPtr is provided, something is off...
    VAMP_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_head != NULL, "The lists should not be empty at this point! Something is off...");

    //Retrieve the original starting address of the allocation node.
    VampAllocationMetadata *node = (VampAllocationMetadata *)( (char *)pUserPtr - VAMP_SIZEOF(VampAllocationMetadata) );

    //Check if this node is a correct debug node.
    VAMP_ASSERT(node->m_magic_number == VAMP_ALLOC_MAGIC, "This is not a valid allocation block!");

    //Check the end of the block.
    VAMP_UINT64 *ptr_to_magic_number = (VAMP_UINT64 *)( (char *)pUserPtr + node->m_user_size );
    VAMP_ASSERT(*ptr_to_magic_number == VAMP_ALLOC_MAGIC, "Memory block overflow detected! Debug your code to find the cause!");

    //There is only one item in the list.
    if (VAMP_GLOBAL_MEMORY_DEBUGGER.m_head == VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail)
    {
        //Then node must be the same memory block as the single item in the list!
        VAMP_ASSERT(node == VAMP_GLOBAL_MEMORY_DEBUGGER.m_head, "This node should be the head of the list.");

        VAMP_GLOBAL_MEMORY_DEBUGGER.m_head = NULL;
        VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail = NULL;
    }

    //More than one item in the list.
    else
    {
        //Since there are more items in the list, this must be greater than 1.
        VAMP_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations > 1, 
            "Should be more than 1. Current value is %ld.", VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations);

        //The node is the head of the list.
        if (node == VAMP_GLOBAL_MEMORY_DEBUGGER.m_head)
        {
            VAMP_GLOBAL_MEMORY_DEBUGGER.m_head = node->m_next;
            node->m_next->m_prev = NULL;
        }

        //node is the tail of the list.
        else if (node == VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail)
        {
            VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail = node->m_prev;
            node->m_prev->m_next = NULL;
        }

        //node is between two other nodes.
        else
        {
            node->m_prev->m_next = node->m_next;

            node->m_next->m_prev = node->m_prev;
        }
    }

    //Decrease the number of total allocations.
    VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations--;

    vampFree( (void *)node );
}



void checkForLeaksImpl(void)
{
    //If the list is not empty, we have a problem!
    if (VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations > 0)
    {
        //Since the list is not empty, the following must not be NULL!
        VAMP_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_head != NULL, "should not be NULL.");
        VAMP_ASSERT(VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail != NULL, "should not be NULL");

        VampAllocationMetadata *current = VAMP_GLOBAL_MEMORY_DEBUGGER.m_head;

        //Loop through the list and log some info.
        while(current)
        {
            VAMP_LOG_FORMAT_TYPE1(
                VAMP_COLOR_RED, 
                "MEMORY LEAK", 
                "VampMemoryDebugger", 
                current->m_filename,
                current->m_function_name,
                current->m_line,
                "Memory Leak! Fix it!"
            );

            current = current->m_next;
        }
    }
}


void vampMemoryDebuggerInit()
{
    VAMP_GLOBAL_MEMORY_DEBUGGER.m_total_allocations = 0;
    VAMP_GLOBAL_MEMORY_DEBUGGER.m_head              = NULL;
    VAMP_GLOBAL_MEMORY_DEBUGGER.m_tail              = NULL;
    VAMP_GLOBAL_MEMORY_DEBUGGER.malloc              = mallocImpl;
    VAMP_GLOBAL_MEMORY_DEBUGGER.free                = freeImpl;
    VAMP_GLOBAL_MEMORY_DEBUGGER.checkForLeaks       = checkForLeaksImpl;
}
#endif



static void *pushImpl(VampMemoryStack *pThis, VAMP_SIZE_T pSize, void *pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    VAMP_ASSERT(pValue != NULL, "This param is required!");

    //Stack is full or pSize does not fit to the remaining memory!
    if (pSize > pThis->m_size - pThis->m_pointer) return NULL;

    char *position = pThis->m_buffer + pThis->m_pointer;
    
    vampMemCopy((void *)position, pValue, pSize);

    pThis->m_pointer += pSize;

    return (void *)position;
}

static void resetImpl( VampMemoryStack *pThis)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    pThis->m_pointer = 0;
}

VAMP_SIZE_T remainingSizeImpl(struct VampMemoryStack *pThis)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");

    return (pThis->m_pointer > pThis->m_size) ? 0 : pThis->m_size - pThis->m_pointer;
}

VAMP_SIZE_T occupiedSizeImpl(struct VampMemoryStack *pThis)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return pThis->m_pointer;
}

static char *pushCharImpl( VampMemoryStack *pThis, char pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (char *)pThis->push(pThis, VAMP_SIZEOF(char), &pValue);
}

static float *pushFloatImpl( VampMemoryStack *pThis, float pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (float *)pThis->push(pThis, VAMP_SIZEOF(float), &pValue);
}

static double *pushDoubleImpl( VampMemoryStack *pThis, double pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (double *)pThis->push(pThis, VAMP_SIZEOF(double), &pValue);
}

static VAMP_SIZE_T *pushSizetImpl( VampMemoryStack *pThis, VAMP_SIZE_T pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (VAMP_SIZE_T *)pThis->push(pThis, VAMP_SIZEOF(VAMP_SIZE_T), &pValue);
}

static VAMP_INT8 *pushInt8Impl( VampMemoryStack *pThis, VAMP_INT8 pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (VAMP_INT8 *)pThis->push(pThis, VAMP_SIZEOF(VAMP_INT8), &pValue);
}

static VAMP_INT16 *pushInt16Impl( VampMemoryStack *pThis, VAMP_INT16 pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (VAMP_INT16 *)pThis->push(pThis, VAMP_SIZEOF(VAMP_INT16), &pValue);
}

static VAMP_INT32 *pushInt32Impl( VampMemoryStack *pThis, VAMP_INT32 pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (VAMP_INT32 *)pThis->push(pThis, VAMP_SIZEOF(VAMP_INT32), &pValue);
}

static VAMP_INT64 *pushInt64Impl( VampMemoryStack *pThis, VAMP_INT64 pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (VAMP_INT64 *)pThis->push(pThis, VAMP_SIZEOF(VAMP_INT64), &pValue);
}

static VAMP_UINT8 *pushUint8Impl( VampMemoryStack *pThis, VAMP_UINT8 pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (VAMP_UINT8 *)pThis->push(pThis, VAMP_SIZEOF(VAMP_UINT8), &pValue);
}

static VAMP_UINT16 *pushUint16Impl( VampMemoryStack *pThis, VAMP_UINT16 pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (VAMP_UINT16 *)pThis->push(pThis, VAMP_SIZEOF(VAMP_UINT16), &pValue);
}

static VAMP_UINT32 *pushUint32Impl( VampMemoryStack *pThis, VAMP_UINT32 pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (VAMP_UINT32 *)pThis->push(pThis, VAMP_SIZEOF(VAMP_UINT32), &pValue);
}

static VAMP_UINT64 *pushUint64Impl( VampMemoryStack *pThis, VAMP_UINT64 pValue)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    return (VAMP_UINT64 *)pThis->push(pThis, VAMP_SIZEOF(VAMP_UINT64), &pValue);
}



VampMemoryStack *vampCreateMemoryStack(VAMP_SIZE_T pSize)
{
    VampMemoryStack *new_stack = (VampMemoryStack *)VAMP_MALLOC(VAMP_SIZEOF(VampMemoryStack));

    if (!new_stack)
    {
        VAMP_WARN("Out of memory!");
        return NULL;
    }

    new_stack->m_size               = pSize;
    new_stack->m_pointer            = 0;
    new_stack->m_buffer             = (char *)VAMP_MALLOC(pSize);

    if (!new_stack->m_buffer)
    {
        VAMP_WARN("Out of memory!");
        return NULL;
    }

    new_stack->push         = pushImpl;
    new_stack->reset        = resetImpl;
    new_stack->remainingSize= remainingSizeImpl;
    new_stack->occupiedSize = occupiedSizeImpl;
    new_stack->pushChar     = pushCharImpl;
    new_stack->pushFloat    = pushFloatImpl;
    new_stack->pushDouble   = pushDoubleImpl;
    new_stack->pushSizet    = pushSizetImpl;
    new_stack->pushInt8     = pushInt8Impl;
    new_stack->pushInt16    = pushInt16Impl;
    new_stack->pushInt32    = pushInt32Impl;
    new_stack->pushInt64    = pushInt64Impl;
    new_stack->pushUint8    = pushUint8Impl;
    new_stack->pushUint16   = pushUint16Impl;
    new_stack->pushUint32   = pushUint32Impl;
    new_stack->pushUint64   = pushUint64Impl;

    return new_stack;
}


void vampDestroyMemoryStack(VampMemoryStack **pThis)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    VAMP_ASSERT(*pThis != NULL, "The value of *pThis must not be NULL!");

    VAMP_FREE( (*pThis)->m_buffer );
    VAMP_FREE( *pThis );

    *pThis = NULL;
}



static void *mallocMemPoolImpl(VampMemoryPool *pThis, void *data)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    VAMP_ASSERT(data != NULL, "This param is required!");

    char *currentBlock  = pThis->m_nextFreeBlock;

    if (!currentBlock) return NULL;

    void *userBlock     = (void *)(currentBlock + VAMP_SIZEOF(__VampMemoryPoolBlock__));

    vampMemCopy(userBlock, data, pThis->m_user_block_size);

    char * buffer_end_address       = pThis->m_buffer + pThis->m_buffer_size;
    VAMP_SIZE_T next_insert_offset  = pThis->m_user_block_size + VAMP_SIZEOF(__VampMemoryPoolBlock__);

    //Current block is being used for the first time and its not the last block in the buffer.
    if (currentBlock == pThis->m_lastDirtyBlock && (currentBlock + next_insert_offset) !=  buffer_end_address)
    {
        pThis->m_nextFreeBlock = currentBlock + next_insert_offset;
        pThis->m_lastDirtyBlock = pThis->m_nextFreeBlock;
    }

    //Current block is being used for the first time and its the last block in the buffer!
    else if (currentBlock == pThis->m_lastDirtyBlock && (currentBlock + next_insert_offset) ==  buffer_end_address)
    {
        pThis->m_nextFreeBlock = NULL;
        pThis->m_lastDirtyBlock = NULL;
    }

    //The current block has its m_next member initialized.
    else
    {
        __VampMemoryPoolBlock__ *currMemBlock = (__VampMemoryPoolBlock__ *)currentBlock;

        pThis->m_nextFreeBlock = currMemBlock->m_next;
    }

    return userBlock;
}

static void freeMemPoolImpl(VampMemoryPool *pThis, void *ptr)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    VAMP_ASSERT(ptr != NULL, "This param is required!");

    __VampMemoryPoolBlock__ *currentBlock  = (__VampMemoryPoolBlock__ *)( (char *)ptr - VAMP_SIZEOF(__VampMemoryPoolBlock__) );

    currentBlock->m_next = pThis->m_nextFreeBlock;
    
    pThis->m_nextFreeBlock = (char *)currentBlock;
}



VampMemoryPool *vampCreateMemoryPool(VAMP_SIZE_T pBlockSize, VAMP_SIZE_T pCount)
{
    VampMemoryPool *new_pool = (VampMemoryPool *)VAMP_MALLOC(VAMP_SIZEOF(VampMemoryPool));

    if (!new_pool)
    {
        VAMP_WARN("Out of memory!");
        return NULL;
    }
    
    new_pool->m_buffer_size = ( VAMP_SIZEOF(__VampMemoryPoolBlock__) + pBlockSize ) * pCount;
    new_pool->m_buffer      = (char *)VAMP_MALLOC( new_pool->m_buffer_size );

    if (!new_pool->m_buffer)
    {
        VAMP_WARN("Out of memory!");
        VAMP_FREE(new_pool);
        return NULL;
    }

    new_pool->m_user_block_size = pBlockSize;
    new_pool->m_user_block_count= pCount;
    new_pool->m_nextFreeBlock   = new_pool->m_buffer;
    new_pool->m_lastDirtyBlock  = new_pool->m_buffer;
    new_pool->malloc            = mallocMemPoolImpl;
    new_pool->free              = freeMemPoolImpl;

    return new_pool;
}


void vampDestroyMemoryPool(VampMemoryPool **pThis)
{
    VAMP_ASSERT(pThis != NULL, "This param is required!");
    VAMP_ASSERT(*pThis != NULL, "This param is required!");
    VAMP_ASSERT((*pThis)->m_buffer != NULL, "Should not be NULL at this point!");

    VAMP_FREE((*pThis)->m_buffer);
    VAMP_FREE(*pThis);

    *pThis = NULL;
}
