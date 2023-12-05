#ifndef VAMP_ENGINE_OPENG_GL_VAO_H
#define VAMP_ENGINE_OPENG_GL_VAO_H

typedef struct VampVertexArray VampVertexArray;

typedef struct VampOpenGLVao
{
    VampVertexArray *__base__;
    unsigned int __id__;
}
VampOpenGLVao;


VampOpenGLVao *VampNewOpenGLVao();

void VampDestroyOpenGLVao(VampOpenGLVao *this);

#endif