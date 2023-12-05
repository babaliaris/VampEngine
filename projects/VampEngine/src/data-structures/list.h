#ifndef VAMP_ENGINE_LIST_H
#define VAMP_ENGINE_LIST_H

/**
 * @file
*/


//-----------------------------------TYPEDEFS-----------------------------------//

/**
 * User defined function.
 * @param[in] data The data passed by the list to the user.
 * @param[in] cond The condition object containing the information to be used against the data.
 * 
 * @returns  > 0 (True) if the condition is met, 0 otherwise.
*/
typedef char (*VampListConditionFunc)(void *data, void *cond);

/**
 * Destroys the users data objects. This function is going to be called by
 * VampDestroyList() for each element in the list.
 * 
 * @param[in] data The data to be destroyed.
*/
typedef void (*VampListDestroyCallback)(void *data);

//-----------------------------------TYPEDEFS-----------------------------------//






/**
 * This is a structure representing the nodes (elements) of the list.
 * @private
*/
typedef struct __VampListNode__
{
    struct __VampListNode__ *__next__;
    struct __VampListNode__ *__prev__;
    void *__data__;
}
__VampListNode__;



/**
 * A double linked list data structure.
*/
typedef struct VampList
{
    /**
     * Append at the end of the list some data.
     * 
     * @param[in] this The list object to append the new data.
     * @param[in] data The data to be appended in the list.
    */
    void (*Append)(struct VampList *this, void *data);

    /**
     * Get the data inside the list at a specified position.
     * 
     * @param[in] this The list object from where the data might be retreived.
     * @param[in] position The position of the data to be retrieved.
     * 
     * @returns The data at that position, NULL if not found.
    */
    void *(*GetAt)(struct VampList *this, unsigned int position);

    /**
     * Get the data inside the list at a specified position.
     * 
     * @param[in] this The list object from where the data will be removed.
     * @param[in] position The position of the data to be removed.
     * 
     * @returns The data that has been removed, NULL if no data where removed.
    */
    void *(*RemoveAt)(struct VampList *this, unsigned int position);

    /**
     * Checks if the list is empty.
     * 
     * @param[in] this The list object to be checked.
     * 
     * @returns Greater than zero if empty, zero otherwise.
    */
    char (*IsEmpty)(struct VampList *this);
    

    /**
     * Get the length of the list.
     * 
     * @param[in] this The list object.
     * 
     * @returns The length (number of elements) of the list.
    */
    unsigned int (*GetLength)(struct VampList *this);


    /**
     * Remove the data based on a custom condition that returns > 0 (true) if the data must be removed.
     * 
     * @param[in] this The list object from where the data might be removed.
     * @param[in] condFunc The user defined function that returns true(>0) or false(0) 
     * @param[in] cond The object that contains the information to be checked against the data.
     * 
     * @returns The data that have been removed, NULL if no data where removed.
    */
    void *(*RemoveByCondition)(struct VampList *this, VampListConditionFunc condFunc, void *cond);


    /**
     * Get the data based on a custom condition that returns > 0 (true) if the data where found.
     * 
     * @param[in] this The list object from where the data might be retreived from.
     * @param[in] condFunc The user defined function that returns true(>0) or false(0) 
     * @param[in] cond The object that contains the information to be checked against the data.
     * 
     * @returns The data that have been found, NULL if not found.
    */
    void *(*GetByCondition)(struct VampList *this, VampListConditionFunc condFunc, void *cond);


    __VampListNode__ *__head__; /**< This is the head of the list. @private*/
    __VampListNode__ *__tail__; /**< This is the tail of the list. @private*/
    unsigned int __length__;  /**< @private*/
}
VampList;




/**
 * Instantiates a new VampList object.
 * @return The newly created object.
*/
VampList *VampNewList();


/**
 * Destroys the list.
 * 
 * @param[in] vampList The VampList object to be destroyed.
 * @param[in] callback The callback user defined function that handles how the data should be freed.
*/
void VampDestroyList(VampList *vampList, VampListDestroyCallback callback);

#endif