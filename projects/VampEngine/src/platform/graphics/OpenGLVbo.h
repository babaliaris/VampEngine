#ifndef VAMP_ENGINE_OPENG_GL_VBO_H
#define VAMP_ENGINE_OPENG_GL_VBO_H

/**
 * @file
*/

typedef struct VampVertexBuffer VampVertexBuffer;

/**
 * The opengl vertex buffer object.
*/
typedef struct VampOpenGLVbo
{
    VampVertexBuffer *__base__; /**< @private*/
    unsigned int __id__; /**< @private*/
}
VampOpenGLVbo;


/**
 * Creates a new VampOpenGLVbo object.
 * 
 * @returns The newly created VampOpenGLVbo object.
*/
VampOpenGLVbo *VampNewOpenGLVbo();


/**
 * Destroyed the VampOpenGLVbo object.
 * 
 * @param[in] glVbo The VampOpenGLVbo to be destroyed.
*/
void VampDestroyOpenGLVbo(VampOpenGLVbo *glVbo);

#endif