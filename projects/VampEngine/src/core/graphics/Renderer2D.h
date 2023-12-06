#ifndef VAMP_ENGINE_RENDERER_2D_H
#define VAMP_ENGINE_RENDERER_2D_H

typedef struct VampList VampList;
typedef struct VampVertexArray VampVertexArray;
typedef struct VampShader VampShader;


typedef struct VampRendererData2D
{
    VampVertexArray *__vao__;
    VampShader      *__shader__;
}
VampRendererData2D;


typedef struct VampRenderer2D
{
    void (*PushDrawData)(struct VampRenderer2D *this, VampVertexArray *vao, VampShader *shader);

    void (*DrawArrays)(struct VampRenderer2D *this, VampRendererData2D *data2D);

    void (*DrawAllArrays)(struct VampRenderer2D *this);

    VampList *__list__;
    void *__child__;
    void (*__ChildDeconstructor__)(void *child);
}
VampRenderer2D;


VampRenderer2D *VampCreateRenderer2D();


void VampDestroyRenderer2D(VampRenderer2D *renderer2D);


VampRendererData2D *VampNewRendererData2D(VampVertexArray *vao, VampShader *shader);

void VampDestroyRendererData2D(VampRendererData2D *data2D);

VampRenderer2D *__VampNewRenderer2D__();

#endif