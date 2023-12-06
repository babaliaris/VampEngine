#include <VampPCH.h>
#include "OpenGLRenderer2D.h"
#include <core/graphics/Renderer2D.h>
#include <core/graphics/VertexArray.h>
#include <core/graphics/VertexBuffer.h>
#include <core/graphics/VertexAttributes.h>
#include <core/graphics/Shader.h>
#include <debug/MemoryTracker.h>
#include <glad/glad.h>
#include "debug/OpenGLCall.h"




static void DrawArrays(VampRenderer2D *this, VampRendererData2D *data2D)
{
    data2D->__vao__->Bind(data2D->__vao__);
    data2D->__shader__->Bind(data2D->__shader__);

    VAMP_GLCALL(glDrawArrays( GL_TRIANGLES, 0, data2D->__vao__->__buffer__->GetNumOfVerts(data2D->__vao__->__buffer__) ));

    data2D->__vao__->Unbind(data2D->__vao__);
    data2D->__shader__->Unbind(data2D->__shader__);
}


static void Destructor(void *this)
{
    VampOpenGLRenderer2D *t = (VampOpenGLRenderer2D *)this;
    VampDestroyOpenGLRenderer2D(t);
}



VampOpenGLRenderer2D *VampNewOpenGLRenderer2D()
{
    VampRenderer2D *renderer_2D = __VampNewRenderer2D__();

    VampOpenGLRenderer2D *VAMP_MALLOC(opengl_renderer2D, sizeof(VampOpenGLRenderer2D));

    renderer_2D->DrawArrays             = DrawArrays;
    renderer_2D->__child__              = opengl_renderer2D;
    renderer_2D->__ChildDeconstructor__ = Destructor;

    opengl_renderer2D->__base__ = renderer_2D;

    return opengl_renderer2D;
}


void VampDestroyOpenGLRenderer2D(VampOpenGLRenderer2D *openglRenderer2D)
{
    VAMP_FREE(openglRenderer2D);
}