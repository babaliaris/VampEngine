#include <VampPCH.h>
#include "Mesh.h"
#include <core/graphics/VertexArray.h>
#include <core/graphics/Shader.h>
#include <debug/MemoryTracker.h>



static void Bind(struct VampMesh *this)
{
    this->__vao__->Bind(this->__vao__);
    this->__shader__->Bind(this->__shader__);
}


static void UnBind(struct VampMesh *this)
{
    this->__vao__->Unbind(this->__vao__);
    this->__shader__->Unbind(this->__shader__);
}


VampMesh *VampNewMesh(VampVertexArray *vao, VampShader *shader)
{
    VampMesh *VAMP_MALLOC(new_mesh, sizeof(VampMesh));

    new_mesh->__vao__       = vao;
    new_mesh->__shader__    = shader;
    new_mesh->Bind          = Bind;
    new_mesh->UnBind        = UnBind;

    return new_mesh;
}

void VampDestroyMesh(VampMesh *mesh)
{
    VampDestroyVertexArray(mesh->__vao__);
    VampDestroyShader(mesh->__shader__);
    VAMP_FREE(mesh);
}