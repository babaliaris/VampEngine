#ifndef VAMP_ENGINE_OPENGL_RENDERER_2D_H
#define VAMP_ENGINE_OPENGL_RENDERER_2D_H

typedef struct VampRenderer2D VampRenderer2D;

typedef struct VampOpenGLRenderer2D
{
    VampRenderer2D *__base__;
}
VampOpenGLRenderer2D;


VampOpenGLRenderer2D *VampNewOpenGLRenderer2D();


void VampDestroyOpenGLRenderer2D(VampOpenGLRenderer2D *openglRenderer2D);



#endif