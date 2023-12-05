#ifndef VAMP_ENGINE_OPENGL_CALL_H
#define VAMP_ENGINE_OPENGL_CALL_H

void __VampOpenGLCrearAllErrors__();
void __VampOpenGLRetrieveErrors__();


#ifdef VAMP_DEBUG
    #define VAMP_GLCALL(code)\
        __VampOpenGLCrearAllErrors__();\
        code;\
        __VampOpenGLRetrieveErrors__()


#else
    #define VAMP_GLCALL(code) code

#endif

#endif
