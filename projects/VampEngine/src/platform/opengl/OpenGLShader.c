#include <VampPCH.h>
#include "OpenGLShader.h"
#include <core/graphics/Shader.h>
#include <debug/MemoryTracker.h>
#include <debug/Logger.h>
#include <glad/glad.h>
#include "debug/OpenGLCall.h"
#include <sds.h>



static void CreateTheProgram(VampOpenGLShader *this, const char *vertex_path, const char *fragment_path);
static sds GetSourceFromFile(const char *filename);
void CompileShader(unsigned int shader, sds source, const char *filepath);
void CheckProgramStatus(unsigned int program, unsigned int check);


static void Bind(VampShader *base)
{
    VampOpenGLShader *this = (VampOpenGLShader *)base->__child__;
    VAMP_GLCALL(glUseProgram(this->__id__));
}


static void UnBind(VampShader *base)
{
    VampOpenGLShader *this = (VampOpenGLShader *)base->__child__;
    VAMP_GLCALL(glUseProgram(0));
}


static void Deconstructor(void *this)
{
    VampOpenGLShader *t = (VampOpenGLShader *)this;
    VampDestroyOpenGLShader(t);
}


VampOpenGLShader *VampNewOpenGLShader(const char *vertex_path, const char *fragment_path)
{
    VampShader *new_shader = __VampNewShader__(vertex_path, fragment_path);

    VampOpenGLShader *VAMP_MALLOC(new_openGLShader, sizeof(VampOpenGLShader));

    new_shader->__child__               = new_openGLShader;
    new_shader->__ChildDeconstructor__  = Deconstructor;
    new_shader->Bind                    = Bind;
    new_shader->Unbind                  = UnBind;
    
    new_openGLShader->__base__  = new_shader;
    new_openGLShader->__id__    = 0;

    CreateTheProgram(new_openGLShader, vertex_path, fragment_path);

    return new_openGLShader;
}




void VampDestroyOpenGLShader(VampOpenGLShader *openGLShader)
{   
    VAMP_GLCALL(glDeleteProgram(openGLShader->__id__));
    VAMP_FREE(openGLShader);
}



static void CreateTheProgram(VampOpenGLShader *this, const char *vertex_path, const char *fragment_path)
{   
    //Create the program.
    VAMP_GLCALL(this->__id__ = glCreateProgram());

    //Create the shaders.
    VAMP_GLCALL(unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER));
    VAMP_GLCALL(unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER));

    //Compile Vertex Shader.
    sds vertex_source = GetSourceFromFile(vertex_path);
    CompileShader(vertex_shader, vertex_source, vertex_path);
    sdsfree(vertex_source);

    //Compile Fragment Shader.
    sds fragment_source = GetSourceFromFile(fragment_path);
    CompileShader(fragment_shader, fragment_source, fragment_path);
    sdsfree(fragment_source);

    //Attach the shaders.
    VAMP_GLCALL(glAttachShader(this->__id__, vertex_shader));
    VAMP_GLCALL(glAttachShader(this->__id__, fragment_shader));

    //Link and check for error..
    VAMP_GLCALL(glLinkProgram(this->__id__));
    CheckProgramStatus(this->__id__, GL_LINK_STATUS);

    //Validate and check for errors.
    VAMP_GLCALL(glValidateProgram(this->__id__));
    CheckProgramStatus(this->__id__, GL_VALIDATE_STATUS);

    //Delete the shaders.
    VAMP_GLCALL(glDeleteShader(vertex_shader));
    VAMP_GLCALL(glDeleteShader(fragment_shader));
}


/**
 * Reads the whole file at once!
 * @private
*/
static sds GetSourceFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");

    long size = 0;

    //Failed to open the file.
    if (!file)
    {
        VAMP_ERROR("Failed to open file: %s", filename);
        return NULL;
    }

    //Seek at the end of the file.
    if ( fseek(file, 0, SEEK_END) > 0 )
    {
        VAMP_ERROR("Failed to seek in the file: %s", filename);
        return NULL;
    }

    //Get the size of the file.
    size = ftell(file);

    //Seek back to the beggining of the file.
    if ( fseek(file, 0, SEEK_SET) > 0 )
    {
        VAMP_ERROR("Failed to seek in the file: %s", filename);
        return NULL;
    }

    //Create an empty sds string of file size.
    //sds makes sure to be size + 1 for the \0 character at the end.
    sds src = sdsnewlen(NULL, size);

    //Read the file and check for errors.
    if (fread(src, size, 1, file) != 1)
    {
        sdsfree(src);
        VAMP_ERROR("Failed to read the file: %s", filename);
        return NULL;
    }

    return src;
}



void CompileShader(unsigned int shader, sds source, const char *filepath)
{
    VAMP_GLCALL(glShaderSource(shader, 1, (const char * const*)&source, NULL));

    VAMP_GLCALL(glCompileShader(shader));

    int success;

    VAMP_GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));

    if (!success)
    {   
        int info_size;
        VAMP_GLCALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_size));

        sds info = sdsnewlen(NULL, info_size);

        VAMP_GLCALL(glGetShaderInfoLog(shader, info_size, NULL, info));

        VAMP_ERROR("[Shader Compilation Failed: %s]\n\t\tError Message: %s", filepath, info);

        sdsfree(info);
    }
}


void CheckProgramStatus(unsigned int program, unsigned int check)
{
    int success;

    VAMP_GLCALL(glGetProgramiv(program, check, &success));

    if (!success)
    {   
        int info_size;
        VAMP_GLCALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_size));

        sds info = sdsnewlen(NULL, info_size);

        VAMP_GLCALL(glGetProgramInfoLog(program, info_size, NULL, info));

        if (check == GL_LINK_STATUS)
        {
            VAMP_ERROR("[Program Linkage Failed]\n\t\tError Message: %s", info);
        }

        else
        {
            VAMP_ERROR("[Program Validation Failed]\n\t\tError Message: %s", info);
        }

        sdsfree(info);
    }
}