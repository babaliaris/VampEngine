#ifndef VAMP_ENGINE_OPENG_GL_VAO_H
#define VAMP_ENGINE_OPENG_GL_VAO_H

/**
 * @file
*/

typedef struct VampVertexArray VampVertexArray;

/**
 * The opengl vertex array object.
*/
typedef struct VampOpenGLVao
{
    VampVertexArray *__base__; /**< @private*/
    unsigned int __id__; /**< @private*/
}
VampOpenGLVao;


/**
 * Creates a new VampOpenGLVao object.
 * 
 * @returns The newly created VampOpenGLVao object.
*/
VampOpenGLVao *VampNewOpenGLVao();


/**
 * Destroyed the VampOpenGLVao object.
 * 
 * @param[in] this The VampOpenGLVao to be destroyed.
*/
void VampDestroyOpenGLVao(VampOpenGLVao *this);

#endif