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
