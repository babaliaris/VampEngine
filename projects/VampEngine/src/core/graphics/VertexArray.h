#ifndef VAMP_ENGINE_VERTEX_ARRAY_H
#define VAMP_ENGINE_VERTEX_ARRAY_H

/**
 * @file
*/

/**
 * The Vertex Array object.
*/
typedef struct VampVertexArray
{
    /**
     * Binds this vertex array object.
     * 
     * @param[in] this The vertex array object.
    */
    void (*Bind)(struct VampVertexArray *this);

    /**
     * UnBinds this vertex array object.
     * 
     * @param[in] this The vertex array object.
    */
    void (*Unbind)(struct VampVertexArray *this);

    void *__child__; /**< @private*/
    void (*__ChildDeconstructor__)(void *child); /**< @private*/
}
VampVertexArray;

/**
 * Creates the implementation depending on the operating system.
 * 
 * @return The newly created VampVertexArray object.
*/
VampVertexArray *VampCreateVertexArray();


/**
 * Destroys the VampVertexArray object.
 * 
 * @param[in] vao The VampVertexArray to be destroyed.
*/
void VampDestroyVertexArray(VampVertexArray *vao);

/**
 * @private
*/
VampVertexArray *__VampNewVertexArray__();


#endif