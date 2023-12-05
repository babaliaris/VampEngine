#ifndef VAMP_ENGINE_VERTEX_BUFFER_H
#define VAMP_ENGINE_VERTEX_BUFFER_H

/**
 * @file
*/

/**
 * The Vertex buffer object.
*/
typedef struct VampVertexBuffer
{
    /**
     * Binds this vertex buffer object.
     * 
     * @param[in] this The vertex bufer object.
    */
    void (*Bind)(struct VampVertexBuffer *this);

    /**
     * UnBinds this vertex buffer object.
     * 
     * @param[in] this The vertex buffer object.
    */
    void (*Unbind)(struct VampVertexBuffer *this);

    void *__child__; /**< @private*/
    void (*__ChildDeconstructor__)(void *child); /**< @private*/
}
VampVertexBuffer;

/**
 * Creates the implementation depending on the operating system.
 * 
 * @return The newly created VampVertexBuffer object.
*/
VampVertexBuffer *VampCreateVertexBuffer();


/**
 * Destroys the VampVertexBuffer object.
 * 
 * @param[in] vbo The VampVertexBuffer to be destroyed.
*/
void VampDestroyVertexBuffer(VampVertexBuffer *vbo);

/**
 * @private
*/
VampVertexBuffer *__VampNewVertexBuffer__();


#endif
