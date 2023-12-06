#ifndef VAMP_ENGINE_VERTEX_ARRAY_H
#define VAMP_ENGINE_VERTEX_ARRAY_H

/**
 * @file
*/

typedef struct VampVertexBuffer VampVertexBuffer;

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

    /**
     * Add a vertex buffer associated with this vertex array object.
     * On VampVertexArray destruction, the VampVertexBuffer object will 
     * be destroyed as well.
     * 
     * @param[in] this The vertex array object.
     * @param[in] vbo The VampVertexBuffer object.
    */
    void (*AddVertexBuffer)(struct VampVertexArray *this, VampVertexBuffer *vbo);

    void *__child__; /**< @private*/
    void (*__ChildDeconstructor__)(void *child); /**< @private*/
    VampVertexBuffer *__buffer__; /**< @private*/

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