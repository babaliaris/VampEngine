#ifndef VAMP_ENGINE_VERTEX_BUFFER_H
#define VAMP_ENGINE_VERTEX_BUFFER_H

/**
 * @file
*/

typedef struct VampVertexAttributes VampVertexAttributes;

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


    /**
     * ITS IMPORTANT TO ADD THE ATTRIBUTES AFTER YOU HAVE PUSHED ALL
     * OF THEM USING VampVertexAttributes::Push() method!!!!!!!
     * 
     * Add a VampVertexAttributes object associated with this buffer.
     * Upon VampVertexBuffer destruction, the VampVertexAttributes object
     * is destroyed as well.
     * 
     * @param[in] this The VampVertexBuffer object.
     * @param[in] attribs The VampVertexAttributes object.
    */
    void (*AddAttributes)(struct VampVertexBuffer *this, VampVertexAttributes *attribs);


    /**
     * Get the number of verticies.
     * 
     * @param[in] this The vertex buffer object.
    */
    unsigned int (*GetNumOfVerts)(struct VampVertexBuffer *this);

    /**
     *Write the data to the buffer.
     * 
     * @param[in] this The vertex buffer object.
     * @param[in] data The pointer from where to read the data.
     * @param[in] size The size of the data read buffer.
    */
    void (*WriteData)(struct VampVertexBuffer *this, const void *data, signed long int size);

    void *__child__; /**< @private*/
    void (*__ChildDeconstructor__)(void *child); /**< @private*/
    signed long int __size__; /**< The buffer's size in bytes. @private*/
    VampVertexAttributes *__attributes__; /**< @private*/
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
