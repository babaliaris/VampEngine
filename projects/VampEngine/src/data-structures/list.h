#ifndef VAMP_ENGINE_LIST_H
#define VAMP_ENGINE_LIST_H


typedef struct __VampListNode__
{
    struct __VampListNode__ *__next__;
    struct __VampListNode__ *__prev__;
    void *__data__;
}
__VampListNode__;


typedef struct VampList
{
    __VampListNode__ *__head__;
    __VampListNode__ *__tail__;
    unsigned int __length__;

    void (*Append)(struct VampList *vampList, void *data);

    void *(*GetAt)(struct VampList *vampList, unsigned int position);

    void *(*RemoveAt)(struct VampList *vampList, unsigned int position);

    char (*IsEmpty)(struct VampList *vampList);
    
    unsigned int (*GetLength)(struct VampList *vampList);
}
VampList;


VampList *VampNewList();


void VampDestroyList(VampList *vampList);

#endif