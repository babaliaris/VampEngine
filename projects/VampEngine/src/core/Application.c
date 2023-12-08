#include <VampPCH.h>

#define VAMP_LOGGER_INIT
#define VAMP_MEMORY_TRACKER_INIT

#include <debug/Logger.h>
#include <debug/MemoryTracker.h>
#include "Application.h"
#include <debug/MemoryTracker.h>
#include <data-structures/list.h>
#include <core/Window.h>
#include <core/Layer.h>
#include <core/graphics/GraphicsContext.h>
#include <core/events/Events.h>
#include <core/graphics/Renderer2D.h>





#include <core/graphics/VertexArray.h>
#include <core/graphics/VertexBuffer.h>
#include <core/graphics/Shader.h>
#include <glad/glad.h>
#include <platform/opengl/debug/OpenGLCall.h>
#include <core/graphics/VertexAttributes.h>
#include <core/Types.h>
#include <core/graphics/Mesh.h>


VampLogger *VampGlobalGetEngineLogger()
{
    return VAMP_GLOBAL_ENGINE_LOGGER;
}


VampLogger *VampGlobalGetClientLogger()
{
    return VAMP_GLOBAL_CLIENT_LOGGER;
}


VampMemoryTracker *VampGlobalGetMemoryTracker()
{
    return VAMP_GLOBAL_MEMORY_TRACKER;
}


static void VampListLayersDecontructor(void *data)
{
    VampLayer *layer = (VampLayer *)data;

    VampDestroyLayer(layer);
}


static char HandleWindowCloseEvent(void *event, void *userPointer)
{
    VampWindowEvent *e = (VampWindowEvent *)event;
    e->__base__->__app__->__window__->__is_running__ = 0;
    return 0;
}


static void VampApplicationRun(VampApplication *this)
{
    this->__graphics_context__->SetClearColor(this->__graphics_context__, 0.4f, 0.4f, 0.4f);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,     1.0f, 0.0f,
        0.5f, 0.5f, 0.0f,     1.0f, 1.0f,

        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,     1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f,     0.0f, 1.0f
    };

    VampVertexArray *vao = VampCreateVertexArray();
    vao->Bind(vao);

    VampVertexBuffer *vbo = VampCreateVertexBuffer();
    vbo->Bind(vbo);

    vao->AddVertexBuffer(vao, vbo);

    vbo->WriteData(vbo, vertices, sizeof(vertices));

    VampVertexAttributes *va = VampCreateVertexAttributes();
    va->Push(va, 3, VAMP_TYPES_FLOAT32);
    va->Push(va, 2, VAMP_TYPES_FLOAT32);

    vbo->AddAttributes(vbo, va);

    VampShader *shader = VampCreateShader("projects/VampEngine/src/shaders/test_vertex.glsl", \
    "projects/VampEngine/src/shaders/test_fragment.glsl");
    shader->Bind(shader);

    VampMesh *mesh = VampNewMesh(vao, shader);

    this->__renderer2D__->PushDrawData(this->__renderer2D__, mesh);

    //----------------------------------Engine Loop----------------------------------//
    while (this->__window__->__is_running__)
    {   
        //Clear the draw Buffers (double buffer swap in use).
        this->__graphics_context__->ClearBuffers(this->__graphics_context__);

        //Run all the layers.
        for (unsigned int i = 0; i < this->__layers_list->__length__; i++)
        {
            VampLayer *layer = this->__layers_list->GetAt(this->__layers_list, i);
            if (layer->__OnUpdate__) layer->__OnUpdate__(layer->__child__);
        }

        //Draw all the meshes in the draw queue.
        this->__renderer2D__->DrawAllArrays(this->__renderer2D__);

        //Update the VampWindow.
        this->__window__->Update(this->__window__);
    }
    //----------------------------------Engine Loop----------------------------------//
}


static void VampApplicationAppendLayer(VampApplication *this, VampLayer *layer)
{
    this->__layers_list->Append(this->__layers_list, layer);
    if (layer->__OnAttach__) layer->__OnAttach__(layer->__child__);
}




static char LayerRemoveCondition(void *data, void *cond)
{
    return data == cond;
}

static VampLayer *VampApplicationRemoveLayer(VampApplication *this, VampLayer *layer)
{
    //Remove the layer from the list.
    VampLayer *removed_layer = this->__layers_list->RemoveByCondition(this->__layers_list, LayerRemoveCondition, layer);

    //Layer removed and OnDetach exists.
    if (removed_layer && layer->__OnDetach__) layer->__OnDetach__(layer->__child__);

    return removed_layer;
}



static void EventHandler(VampEvent *event)
{
    //Close the application if the X button is pressed.
    event->Dispatch(event, VAMP_EVENT_WINDOW_CLOSE, HandleWindowCloseEvent, NULL);

    //Propagate the event in the layers backwards.
    //Length is unsigned int so i can not be < 0.
    //This means i is not the actual position of the element
    //but i-1 is. Do it carefully, else segmetation fault will happen.
    VampList *layers = event->__app__->__layers_list;
    for (unsigned int i = layers->__length__; i > 0; i--)
    {
        VampLayer *layer = (VampLayer *)layers->GetAt(layers, i-1);

        if (layer->__OnEvent__ && !event->__has_been_handled__)
            layer->__OnEvent__(layer->__child__, event);
    }
}




VampApplication *VampNewApplication(UserEntryPoint user, const char *title, int width, int height)
{
    VampApplication *new_app = (VampApplication *)malloc( sizeof(VampApplication) );

    VAMP_GLOBAL_ENGINE_LOGGER        = VampNewLogger("VampEngine");
    VAMP_GLOBAL_CLIENT_LOGGER        = VampNewLogger("Client");
    VAMP_GLOBAL_MEMORY_TRACKER       = VampNewMemoryTracker();

    new_app->__user_entry_point__   = user;

    new_app->__window__                     = VampCreateWindow(new_app, title, width, height);
    new_app->__window__->__event_callback__ = EventHandler;

    new_app->__layers_list          = VampNewList();
    new_app->__graphics_context__   = VampCreateGraphicsContext(new_app);
    new_app->__renderer2D__         = VampCreateRenderer2D();

    new_app->__Run__                = VampApplicationRun;
    new_app->AppendLayer            = VampApplicationAppendLayer;
    new_app->RemoveLayer            = VampApplicationRemoveLayer;



    return new_app;

}


void VampDestroyApplication(VampApplication *app)
{

    //Destroy the Renderer2D.
    VampDestroyRenderer2D(app->__renderer2D__);

    //Destroy all the layers.
    VampDestroyList(app->__layers_list, VampListLayersDecontructor);

    //Destroy Graphics Context.
    VampDestroyGraphicsContext(app->__graphics_context__);

    //Destroy the window.
    VampDestroyWindow(app->__window__);

    //If the memory tracker list is not empty, there are memory leaks.
    #ifdef VAMP_DEBUG
    if (!VAMP_GLOBAL_MEMORY_TRACKER->__list__->IsEmpty(VAMP_GLOBAL_MEMORY_TRACKER->__list__))
    {
        VAMP_WARN("There are memory leaks, check out mem.leaks.txt");
    }
    #endif

    //Destroy the loggers.
    VampDestroyLogger(VAMP_GLOBAL_ENGINE_LOGGER);
    VampDestroyLogger(VAMP_GLOBAL_CLIENT_LOGGER);

    //Log any memory leaks to a file and then destroy the tracker.
    VAMP_GLOBAL_MEMORY_TRACKER->WriteMemoryLeaksFile(VAMP_GLOBAL_MEMORY_TRACKER, "mem.leaks.txt");
    VampDestroyMemoryTracker(VAMP_GLOBAL_MEMORY_TRACKER);

    free(app);
}