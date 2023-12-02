#ifndef VAMP_ENGINE_GRAPHICS_CONTEXT_GLAD_H
#define VAMP_ENGINE_GRAPHICS_CONTEXT_GLAD_H


typedef struct VampApplication VampApplication;
typedef struct VampGraphicsContext VampGraphicsContext;


/**
 * The graphics context structure using OpenGL (GLAD).
*/
typedef struct VampGraphicsContextGLAD
{
    VampGraphicsContext *__base__; /**< The base class object. @private*/
}
VampGraphicsContextGLAD;



/**
 * Create the VampGraphicsContextGLAD object.
 * 
 * @param[in] app The VampApplication object.
 * 
 * @returns The newly created object.
*/
VampGraphicsContextGLAD *VampNewGraphicsContextGLAD(VampApplication *app);


/**
 * Destroys the VampGraphicsContextGLAD object.
 * 
 * @param[in] ctxGLAD The VampGraphicsContextGLAD to be destroyed.
*/
void VampDestroyGraphicsContextGLAD(VampGraphicsContextGLAD *ctxGLAD);


#endif