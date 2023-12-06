#include <VampPCH.h>
#include "OpenGLVertexAttributes.h"
#include <core/graphics/VertexAttributes.h>
#include <debug/MemoryTracker.h>
#include <debug/Logger.h>
#include <data-structures/list.h>
#include <core/Types.h>
#include <glad/glad.h>
#include "debug/OpenGLCall.h"
#include "VampTypeToOpenGlType.h"


static void Push(VampVertexAttributes *base, int length, unsigned int type)
{
    VampOpenGLVertexAttributes *this = (VampOpenGLVertexAttributes *)base->__child__;

    __OpenGLVertexAttribsData__ *VAMP_MALLOC(data, sizeof(__OpenGLVertexAttribsData__));

    //Initialize the data.
    data->__length__    = length; //Number of attribute values (1,2,3 or 4).
    data->__type__      = VampTypeToOpenGLType(type); //Store the OpenGL type.
    data->__size__      = VampGetOpenGLTypeSize( VampTypeToOpenGLType(type) ); //Get the size of the type in bytes.

    //Append the data into the list.
    this->__list__->Append(this->__list__, data);

    //Calculate the new stride of the whole vertex.
    this->__stride__ += data->__size__ * length;
}



static void Generate(VampVertexAttributes *base)
{
    VampOpenGLVertexAttributes *this = (VampOpenGLVertexAttributes *)base->__child__;

    void *offset = 0;

    //Loop through each element in the vertex attributes list.
    for (unsigned int i = 0; i < this->__list__->__length__; i++)
    {
        __OpenGLVertexAttribsData__ *data = (__OpenGLVertexAttribsData__ *)this->__list__->GetAt(this->__list__, i);

        VAMP_GLCALL(glEnableVertexAttribArray(i));
        VAMP_GLCALL(glVertexAttribPointer(i, data->__length__, data->__type__, GL_FALSE, this->__stride__, (const void *)offset));

        offset += data->__size__ * data->__length__;
    }
}


static void DataDeconstructor(void *data)
{
    __OpenGLVertexAttribsData__ *d = (__OpenGLVertexAttribsData__ *)data;
    VAMP_FREE(d);
}


static void Deconstructor(void *this)
{
    VampOpenGLVertexAttributes *t = (VampOpenGLVertexAttributes *)this;
    VampDestroyOpenGLVertexAttributes(t);
}


VampOpenGLVertexAttributes *VampNewOpenGLVertexAttributes()
{
    VampVertexAttributes *new_va = __VampNewVertexAttributes__();

    VampOpenGLVertexAttributes *VAMP_MALLOC(new_openGLVa, sizeof(VampOpenGLVertexAttributes));

    new_va->Push                    = Push;
    new_va->Generate                = Generate;
    new_va->__child__               = new_openGLVa;
    new_va->__ChildDeconstructor__  = Deconstructor;
    
    new_openGLVa->__base__              = new_va;
    new_openGLVa->__list__              = VampNewList();
    new_openGLVa->__num_of_verticies__  = 0;
    new_openGLVa->__stride__            = 0;
}



void VampDestroyOpenGLVertexAttributes(VampOpenGLVertexAttributes *openGLVa)
{
    VampDestroyList(openGLVa->__list__, DataDeconstructor);
    VAMP_FREE(openGLVa);
}
