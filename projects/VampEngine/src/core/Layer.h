#ifndef VAMP_ENGINE_LAYER_H
#define VAMP_ENGINE_LAYER_H


/**
 * @file
*/

typedef struct VampApplication VampApplication;
typedef struct VampString VampString;


/**
 * An object used to run code in the game loop.
*/
typedef struct VampLayer
{


    VampApplication *(*GetApp)(struct VampLayer *layer);

    const char *(*GetDebugName)(struct VampLayer *layer);

    VampApplication *__app__; /**< @private*/
    VampString *__debug_name__; /**< @private*/

    /**
     * Gets called only ONCE after the layer has been
     * attached to the application.
     * 
     * @private
     * 
     * @param[in] layer The layer that has been attached.
    */
    void (*__OnAttach__)(struct VampLayer *layer);

    /**
     * Gets called only ONCE after the layer has been
     * removed from the application.
     * 
     * @private
     * 
     * @param[in] layer The layer that has been removed.
    */
    void (*__OnDetach__)(struct VampLayer *layer);

    /**
     * Gets called only on every frame update.
     * 
     * @private
     * 
     * @param[in] layer The layer that updates.
    */
    void (*__OnUpdate__)(struct VampLayer *layer);
}
VampLayer;


/**
 * User defined callback: Gets called only ONCE after the layer has been
 * attached to the application.
 * 
 * @param[in] layer The layer that has been attached.
*/
typedef void (*VampLayerOnAttachFunc)(VampLayer *layer);

/**
 * User defined callback: Gets called only ONCE after the layer has been
 * removed from the application.
 * 
 * @param[in] layer The layer that has been removed.
*/
typedef void (*VampLayerOnDetachFunc)(VampLayer *layer);

/**
 * User defined callback: Gets called in every frame update.
 * 
 * @param[in] layer The layer that has been updated.
*/
typedef void (*VampLayerOnUpdateFunc)(VampLayer *layer);




/**
 * Creates a new VampLayer object.
 * 
 * @param[in] debug_name A name for debug purposes.
 * @param[in] app The application object.
 * @param[in] onAttach The user defined VampLayerOnAttachFunc() callback.
 * @param[in] onDetach The user defined VampLayerOnDetachFunc() callback.
 * @param[in] onUpdate The user defined VampLayerOnUpdateFunc() callback.
 * 
 * @returns The newly created object.
*/
VampLayer *VampNewLayer(const char *debug_name,
                        VampApplication *app,
                        VampLayerOnAttachFunc onAttach,
                        VampLayerOnDetachFunc onDetach,
                        VampLayerOnUpdateFunc onUpdate
                        );




/**
 * Destroys a layer object.
 * 
 * @param[in] layer The VampLayer to be destroyed.
*/
void VampDestroyLayer(VampLayer *layer);

#endif