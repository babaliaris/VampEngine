#ifndef VAMP_ENGINE_OPENGL_VERTEX_ATTRIBUTES_H
#define VAMP_ENGINE_OPENGL_VERTEX_ATTRIBUTES_H

typedef struct VampVertexAttributes VampVertexAttributes;
typedef struct VampList VampList;


/**
 * The attribute data structure.
 * @private
*/
typedef struct __OpenGLVertexAttribsData__
{
    int __length__; /**< The number of attrib values (1, 2, 3, or 4)*/
    unsigned int __type__; /**< The OpenGL data type*/
    unsigned int __size__; /**< The size of the __type__ in bytes*/
}
__OpenGLVertexAttribsData__;


typedef struct VampOpenGLVertexAttributes
{
    VampVertexAttributes *__base__; /**< @private*/
    VampList *__list__; /**< @private*/
    unsigned int __num_of_verticies__; /**< @private*/
    int __stride__; /**< @private*/
}
VampOpenGLVertexAttributes;


/**
 * Creates a new VampOpenGLVertexAttributes object.
 * @returns The newly created VampOpenGLVertexAttributes object.
*/
VampOpenGLVertexAttributes *VampNewOpenGLVertexAttributes();


/**
 * Destroys a VampOpenGLVertexAttributes object.
 * 
 * @param[in] vaOpenGL The VampOpenGLVertexAttributes object to be destroyed.
*/
void VampDestroyOpenGLVertexAttributes(VampOpenGLVertexAttributes *openGLVa);


#endif