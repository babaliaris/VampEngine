#include <VampPCH.h>
#include "list.h"
#include <debug/MemoryTracker.h>


__VampListNode__ *VampNewListNode(void *data)
{
    __VampListNode__ *VAMP_MALLOC( new_node, sizeof(__VampListNode__) );

    new_node->__next__ = NULL;
    new_node->__prev__ = NULL;
    new_node->__data__ = data;

    return new_node;
}


void VampDestroyListNode(__VampListNode__ *listNode)
{
    if (!listNode) return;
    VAMP_FREE(listNode);
}


static void ListAppend(VampList *vampList, void *data)
{
    if (!vampList || !data) return;

    __VampListNode__ *new_node = VampNewListNode(data);

    if ( vampList->IsEmpty(vampList) )
    {
        vampList->__head__->__next__ = new_node;
        vampList->__tail__->__prev__ = new_node;

        new_node->__next__ = vampList->__tail__;
        new_node->__prev__ = vampList->__head__;
    }

    else
    {
        new_node->__next__ = vampList->__tail__;
        new_node->__prev__ = vampList->__tail__->__prev__;

        vampList->__tail__->__prev__->__next__  = new_node;
        vampList->__tail__->__prev__            = new_node;
    }

    vampList->__length__++;
}


static void *ListGetAt(VampList *vampList, unsigned int position)
{
    if (!vampList) return NULL;

    unsigned int i = 0;
    __VampListNode__ *current = vampList->__head__->__next__;

    while(current && current->__next__)
    {
        if (i == position) return current->__data__;

        current = current->__next__;
        i++;
    }

    return NULL;
}


static void *ListRemoveAt(VampList *vampList, unsigned int position)
{
    if (!vampList) return NULL;

    unsigned int i = 0;
    __VampListNode__ *current = vampList->__head__->__next__;

    //Loop through the list.
    while(current && current->__next__)
    {
        if (i == position)
        {
            //The list has one element.
            if (vampList->__length__ == 1)
            {
                current->__next__ = NULL;
                current->__prev__ = NULL;

                vampList->__head__->__next__ = NULL;
                vampList->__tail__->__prev__ = NULL;
            }


            //The list has more than 1 elements.
            else
            {
                current->__next__->__prev__ = current->__prev__;
                current->__prev__->__next__ = current->__next__;
            }

            vampList->__length__--;

            void *data = current->__data__;

            VampDestroyListNode(current);

            //Return the data to the user, so he can free them if necessary.
            return data;
        }

        current = current->__next__;
        i++;
    }

    return NULL;
}


static char ListIsEmpty(VampList *vampList)
{
    if (!vampList) return 0;

    return (!vampList->__head__->__next__ && !vampList->__tail__->__prev__);
}


static unsigned int ListGetLength(VampList *vampList)
{
    if (!vampList) return 0;

    return vampList->__length__;
}


static void *ListRemoveByCondition(struct VampList *vampList, VampListConditionFunc condFunc, void *cond)
{
    if (!vampList || !condFunc) return NULL;

    __VampListNode__ *current = vampList->__head__->__next__;

    //Loop through the list.
    while(current && current->__next__)
    {
        if ( condFunc(current->__data__, cond)  )
        {
            //The list has one element.
            if (vampList->__length__ == 1)
            {
                current->__next__ = NULL;
                current->__prev__ = NULL;

                vampList->__head__->__next__ = NULL;
                vampList->__tail__->__prev__ = NULL;
            }


            //The list has more than 1 elements.
            else
            {
                current->__next__->__prev__ = current->__prev__;
                current->__prev__->__next__ = current->__next__;
            }

            vampList->__length__--;

            void *data = current->__data__;

            VampDestroyListNode(current);

            return data;
        }

        current = current->__next__;
    }

    return NULL;
}


static void *ListGetByCondition(struct VampList *vampList, VampListConditionFunc condFunc, void *cond)
{
    if (!vampList || !condFunc) return NULL;

    __VampListNode__ *current = vampList->__head__->__next__;

    //Loop through the list.
    while(current && current->__next__)
    {
        if ( condFunc(current->__data__, cond)  )
            return current->__data__;

        current = current->__next__;
    }

    return NULL;
}


VampList *VampNewList()
{
    VampList *VAMP_MALLOC( new_list, sizeof(VampList) );

    new_list->__head__ = VampNewListNode(NULL);
    new_list->__tail__ = VampNewListNode(NULL);

    new_list->__length__ = 0;

    new_list->Append                = ListAppend;
    new_list->GetAt                 = ListGetAt;
    new_list->RemoveAt              = ListRemoveAt;
    new_list->IsEmpty               = ListIsEmpty;
    new_list->GetLength             = ListGetLength;
    new_list->RemoveByCondition     = ListRemoveByCondition;
    new_list->GetByCondition        = ListGetByCondition;

    return new_list;
}

void VampDestroyList(VampList *vampList, VampListDestroyCallback callback)
{
     if (!vampList) return;

    __VampListNode__ *current   = vampList->__head__->__next__;
    __VampListNode__ *temp      = current;

    while(current && current->__next__)
    {
        //Call users callback, so he can destroy the data.
        if (callback) callback(current->__data__);

        current = current->__next__;
        VampDestroyListNode(temp);
        temp = current;
    }

    VampDestroyListNode(vampList->__head__);
    VampDestroyListNode(vampList->__tail__);

    VAMP_FREE(vampList);
}