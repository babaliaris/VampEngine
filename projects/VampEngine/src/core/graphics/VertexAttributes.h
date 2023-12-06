#ifndef VAMP_ENGINE_VERTEX_ATTRIBUTES_H
#define VAMP_ENGINE_VERTEX_ATTRIBUTES_H

typedef struct VampVertexAttributes
{
    /**
     * Push an attribute definition into the attributes list.
     * 
     * @param[in] this The VampVertexAttributes object.
     * @param[in] length The length of the vertex attribute (How many values does it have?)
     * @param[in] type The data type of each vertex attribute value.
    */
    void (*Push)(struct VampVertexAttributes *this, int length, unsigned int type);

    /**
     * Generate the vertex attributes from the pushed data.
     * 
     * @param[in] this The VampVertexAttributes object.
    */
    void (*Generate)(struct VampVertexAttributes *this);



    void *__child__; /**< @private*/
    void (*__ChildDeconstructor__)(void *child); /**< @private*/
}
VampVertexAttributes;


/**
 * Creates a new VampVertexAttributes object implementation based on the operating system.
 * 
 * @returns The newly created VampVertexAttributes object.
*/
VampVertexAttributes *VampCreateVertexAttributes();


/**
 * Destroys a VampVertexAttributes object.
 * 
 * @param[in] va The VampVertexAttributes object to be destroyed.
*/
void VampDestroyVertexAttributes(VampVertexAttributes *va);


/**
 * Creates a new VampVertexAttributes object.
 * @private
 * @returns The newly created VampVertexAttributes object.
*/
VampVertexAttributes *__VampNewVertexAttributes__();

#endif