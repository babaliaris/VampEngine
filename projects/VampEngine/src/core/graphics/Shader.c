#include <VampPCH.h>
#include "Shader.h"
#include <debug/MemoryTracker.h>
#include <sds.h>


#ifdef VAMP_LINUX
    #include <platform/opengl/OpenGLShader.h>
#endif


#ifdef VAMP_WINDOWS
    #include <platform/opengl/OpenGLShader.h>
#endif



static const char *GetVertexPath(VampShader *this)
{
    return this->__vertex_path__;
}



static const char *GetFragmentPath(VampShader *this)
{
    return this->__fragment_path__;
}



VampShader *VampCreateShader(const char *vertex_path, const char *fragment_path)
{
    #ifdef VAMP_LINUX
    return VampNewOpenGLShader(vertex_path, fragment_path)->__base__;
    #endif


    #ifdef VAMP_WINDOWS
    return VampNewOpenGLShader(vertex_path, fragment_path)->__base__;
    #endif
}


VampShader *__VampNewShader__(const char *vertex_path, const char *fragment_path)
{
    VampShader *VAMP_MALLOC(new_shader, sizeof(VampShader));

    new_shader->__child__               = NULL; //To be ovverriden.
    new_shader->__ChildDeconstructor__  = NULL; //To be ovverriden.
    new_shader->__vertex_path__         = sdsnew(vertex_path);
    new_shader->__fragment_path__       = sdsnew(fragment_path);

    new_shader->Bind            = NULL; //To be ovverriden.
    new_shader->Unbind          = NULL; //To be ovverriden.
    new_shader->GetVertexPath   = GetVertexPath;
    new_shader->GetFragmentPath = GetFragmentPath;

    return new_shader;
}


void VampDestroyShader(VampShader *shader)
{
    sdsfree(shader->__vertex_path__);
    sdsfree(shader->__fragment_path__);
    shader->__ChildDeconstructor__(shader->__child__);
    VAMP_FREE(shader);
}
