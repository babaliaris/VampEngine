#include <VampPCH.h>
#include "list.h"


__VampListNode__ *VampNewListNode(void *data)
{
    __VampListNode__ *new_node = (__VampListNode__ *)malloc( sizeof(__VampListNode__) );

    new_node->__next__ = NULL;
    new_node->__prev__ = NULL;
    new_node->__data__ = data;

    return new_node;
}


void VampDestroyListNode(__VampListNode__ *listNode)
{
    if (!listNode) return;
    free(listNode);
}


void VampListAppend(VampList *vampList, void *data)
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


void *VampListGetAt(VampList *vampList, unsigned int position)
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


void *VampListRemoveAt(VampList *vampList, unsigned int position)
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


char VampListIsEmpty(VampList *vampList)
{
    if (!vampList) return 0;

    return (!vampList->__head__->__next__ && !vampList->__tail__->__prev__);
}


unsigned int VampListGetLength(VampList *vampList)
{
    if (!vampList) return 0;

    return vampList->__length__;
}


void *VampListRemoveByCondition(struct VampList *vampList, VampListConditionFunc condFunc, void *cond)
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


void *VampListGetByCondition(struct VampList *vampList, VampListConditionFunc condFunc, void *cond)
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
    VampList *new_list = (VampList *)malloc( sizeof(VampList) );

    new_list->__head__ = VampNewListNode(NULL);
    new_list->__tail__ = VampNewListNode(NULL);

    new_list->__length__ = 0;

    new_list->Append                = VampListAppend;
    new_list->GetAt                 = VampListGetAt;
    new_list->RemoveAt              = VampListRemoveAt;
    new_list->IsEmpty               = VampListIsEmpty;
    new_list->GetLength             = VampListGetLength;
    new_list->RemoveByCondition     = VampListRemoveByCondition;
    new_list->GetByCondition        = VampListGetByCondition;

    return new_list;
}

void VampDestroyList(VampList *vampList)
{
     if (!vampList) return;

    __VampListNode__ *current   = vampList->__head__->__next__;
    __VampListNode__ *temp      = current;

    /*TODO If the user destroys a list that is NOT empty,
            they have to destroy/free all of their data first.
    */

    while(current && current->__next__)
    {
        current = current->__next__;
        VampDestroyListNode(temp);
        temp = current;
    }

    VampDestroyListNode(vampList->__head__);
    VampDestroyListNode(vampList->__tail__);

    free(vampList);
}