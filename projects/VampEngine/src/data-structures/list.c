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


static void ListAppend(VampList *this, void *data)
{
    if (!this || !data) return;

    __VampListNode__ *new_node = VampNewListNode(data);

    if ( this->IsEmpty(this) )
    {
        this->__head__->__next__ = new_node;
        this->__tail__->__prev__ = new_node;

        new_node->__next__ = this->__tail__;
        new_node->__prev__ = this->__head__;
    }

    else
    {
        new_node->__next__ = this->__tail__;
        new_node->__prev__ = this->__tail__->__prev__;

        this->__tail__->__prev__->__next__  = new_node;
        this->__tail__->__prev__            = new_node;
    }

    this->__length__++;
}


static void *ListGetAt(VampList *this, unsigned int position)
{
    if (!this) return NULL;

    unsigned int i = 0;
    __VampListNode__ *current = this->__head__->__next__;

    while(current && current->__next__)
    {
        if (i == position) return current->__data__;

        current = current->__next__;
        i++;
    }

    return NULL;
}


static void *ListRemoveAt(VampList *this, unsigned int position)
{
    if (!this) return NULL;

    unsigned int i = 0;
    __VampListNode__ *current = this->__head__->__next__;

    //Loop through the list.
    while(current && current->__next__)
    {
        if (i == position)
        {
            //The list has one element.
            if (this->__length__ == 1)
            {
                current->__next__ = NULL;
                current->__prev__ = NULL;

                this->__head__->__next__ = NULL;
                this->__tail__->__prev__ = NULL;
            }


            //The list has more than 1 elements.
            else
            {
                current->__next__->__prev__ = current->__prev__;
                current->__prev__->__next__ = current->__next__;
            }

            this->__length__--;

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


static char ListIsEmpty(VampList *this)
{
    if (!this) return 0;

    return (!this->__head__->__next__ && !this->__tail__->__prev__);
}


static unsigned int ListGetLength(VampList *this)
{
    if (!this) return 0;

    return this->__length__;
}


static void *ListRemoveByCondition(VampList *this, VampListConditionFunc condFunc, void *cond)
{
    if (!this || !condFunc) return NULL;

    __VampListNode__ *current = this->__head__->__next__;

    //Loop through the list.
    while(current && current->__next__)
    {
        if ( condFunc(current->__data__, cond)  )
        {
            //The list has one element.
            if (this->__length__ == 1)
            {
                current->__next__ = NULL;
                current->__prev__ = NULL;

                this->__head__->__next__ = NULL;
                this->__tail__->__prev__ = NULL;
            }


            //The list has more than 1 elements.
            else
            {
                current->__next__->__prev__ = current->__prev__;
                current->__prev__->__next__ = current->__next__;
            }

            this->__length__--;

            void *data = current->__data__;

            VampDestroyListNode(current);

            return data;
        }

        current = current->__next__;
    }

    return NULL;
}


static void *ListGetByCondition(VampList *this, VampListConditionFunc condFunc, void *cond)
{
    if (!this || !condFunc) return NULL;

    __VampListNode__ *current = this->__head__->__next__;

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