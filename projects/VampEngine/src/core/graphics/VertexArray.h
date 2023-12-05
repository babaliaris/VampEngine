#ifndef VAMP_ENGINE_VERTEX_ARRAY_H
#define VAMP_ENGINE_VERTEX_ARRAY_H

typedef struct VampVertexArray
{
    void (*Bind)(struct VampVertexArray *this);
    void (*Unbind)(struct VampVertexArray *this);

    void *__child__;
    void (*__ChildDeconstructor__)(void *child);
}
VampVertexArray;

VampVertexArray *VampCreateVertexArray();

void VampDestroyVertexArray(VampVertexArray *this);

VampVertexArray *__VampNewVertexArray__();


#endif