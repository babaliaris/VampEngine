#ifndef VAMP_ENGINE_OPENGL_RENDERER_2D_H
#define VAMP_ENGINE_OPENGL_RENDERER_2D_H


/**
 * @file
*/

typedef struct VampRenderer2D VampRenderer2D;



/**
 * The renderer2D openGL implementation structure.
*/
typedef struct VampOpenGLRenderer2D
{
    VampRenderer2D *__base__; /**< @private*/
}
VampOpenGLRenderer2D;


/**
 * Create a new VampOpenGLRenderer2D object.
 * 
 * @returns The newly create VampOpenGLRenderer2D object.
*/
VampOpenGLRenderer2D *VampNewOpenGLRenderer2D();


/**
 * Destroys a VampOpenGLRenderer2D object.
 * 
 * @param[in] openglRenderer2D The openglRenderer2D object to be destroyed.
*/
void VampDestroyOpenGLRenderer2D(VampOpenGLRenderer2D *openglRenderer2D);



#endif