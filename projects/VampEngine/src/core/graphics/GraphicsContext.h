#ifndef VAMP_ENGINE_GRAPHICS_CONTEXT_H
#define VAMP_ENGINE_GRAPHICS_CONTEXT_H

typedef struct VampApplication VampApplication;


/**
 * The graphics context structure.
*/
typedef struct VampGraphicsContext
{
    /**
     * Sets the clear color of the color buffer.
     * 
     * @param[in] ctx The VampGraphicsContext object.
     * @param[in] r The red value of the color.
     * @param[in] g The green value of the color.
     * @param[in] b The blue value of the color.
    */
    void (*SetClearColor)(struct VampGraphicsContext *ctx, float r, float g, float b);

    /**
     * Clears all the buffers.
     * 
     * @param[in] ctx The VampGraphicsContext object.
    */
    void (*ClearBuffers)(struct VampGraphicsContext *ctx);



    void *__child__; /**< @private*/
    void (*__child_deconstructor__)(void *child); /**< @private*/

    VampApplication *__app__; /**< @private*/
    float __clear_color_r; /**< @private*/
    float __clear_color_g; /**< @private*/
    float __clear_color_b; /**< @private*/
}
VampGraphicsContext;



/**
 * Creates the GraphicsContext implementation depending on the operating system.
 * 
 * @param[in] app The VampApplication object.
 * 
 * @returns The newly created object.
*/
VampGraphicsContext *VampCreateGraphicsContext(VampApplication *app);



/**
 * Initializes the graphics context based on the operating system
 * and graphics specification that is used.
 * 
 * @param[in] data The data needed for the initialization.
*/
void VampInitGraphicsContext(void *data);



/**
 * Destroys the VampGraphicsContext object.
 * 
 * @param[in] ctx The VampGraphicsContext object to be destroyed.
*/
void VampDestroyGraphicsContext(VampGraphicsContext *ctx);



/**
 * Creates the VampGraphicsContext object.
 * @private
 * 
 * @param[in] app The VampApplication object.
 * 
 * @returns The newly created object.
*/
VampGraphicsContext *__VampNewGraphicsContext__(VampApplication *app);

#endif