#ifndef VAMP_MEMORY_H
#define VAMP_MEMORY_H
#include <VampEngine/core/vamp_std.h>

#ifdef VAMP_DEBUG

    #define VAMP_ALLOC_MAGIC 0xDEADBEEFDEADBEEF

    typedef struct VampAllocationMetadata
    {   
        VAMP_UINT64 m_magic_number;
        const char *m_filename;
        const char *m_function_name;
        VAMP_SIZE_T m_line;
        VAMP_SIZE_T m_user_size;

        struct VampAllocationMetadata *m_next;
        struct VampAllocationMetadata *m_prev;
    }VampAllocationMetadata;



    typedef struct VampMemoryDebugger
    {
        VAMP_SIZE_T m_total_allocations;

        VampAllocationMetadata *m_head;
        VampAllocationMetadata *m_tail;

        void *(*malloc)( VAMP_SIZE_T size, const char *pFilename, 
                        const char *pFuncName, VAMP_SIZE_T pLine
        );

        void (*free)(void *pUserPtr);

        void (*checkForLeaks)(void);

    }VampMemoryDebugger;


    #ifndef VAMP_MEMORY_DEBUGGER_GLOBAL_INSTANCE
        extern VampMemoryDebugger VAMP_GLOBAL_MEMORY_DEBUGGER;
    #else
        VampMemoryDebugger VAMP_GLOBAL_MEMORY_DEBUGGER;
    #endif


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


#endif
