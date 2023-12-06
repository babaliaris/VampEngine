#ifndef VAMP_ENGINE_OPENGL_SHADER_H
#define VAMP_ENGINE_OPENGL_SHADER_H

/**
 * @file
*/


typedef struct VampShader VampShader;

/**
 * The opengl shader structure.
*/
typedef struct VampOpenGLShader
{
    VampShader *__base__; /**< @private*/
    unsigned int __id__; /**< @private*/
}
VampOpenGLShader;



/**
 * Creates a new VampOpenGLShader object.
 * 
 * @param[in] vertex_path The filename path that contains the vertex's shader code.
 * @param[in] fragment_path The filename path that contains the fragment's shader code.
*/
VampOpenGLShader *VampNewOpenGLShader(const char *vertex_path, const char *fragment_path);



/**
 * Destroys the VampOpenGLShader object.
 * 
 * @param[in] opnGLShader The VampOpenGLShader to be destroyed.
*/
void VampDestroyOpenGLShader(VampOpenGLShader *openGLShader);

#endif