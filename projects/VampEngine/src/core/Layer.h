#ifndef VAMP_ENGINE_LAYER_H
#define VAMP_ENGINE_LAYER_H


/**
 * @file
*/

typedef struct VampApplication VampApplication;
typedef struct VampString VampString;
typedef struct VampEvent VampEvent;


/**
 * An object used to run code in the game loop.
*/
typedef struct VampLayer
{

    /**
     * Get the VampApplication object.
     * 
     * @param[in] this The VampLayer object.
     * @returns The VampApplication object.
    */
    VampApplication *(*GetApp)(struct VampLayer *this);


    /**
     * Gets called only ONCE after the layer has been
     * attached to the application.
     * 
     * @private
     * 
     * @param[in] layer The users custom layer that has been attached.
    */
    void (*__OnAttach__)(void *layer);

    /**
     * Gets called only ONCE after the layer has been
     * removed from the application.
     * 
     * @private
     * 
     * @param[in] layer The users custom layer that has been removed.
    */
    void (*__OnDetach__)(void *layer);

    /**
     * Gets called only on every frame update.
     * 
     * @private
     * 
     * @param[in] layer The users custom layer that updates.
    */
    void (*__OnUpdate__)(void *layer);

    /**
     * Gets called when an event occurs.
     * 
     * @private
     * 
     * @param[in] layer The users custom layer object.
     * @param[in] event The VampEvent that was caught.
    */
    void (*__OnEvent__)(void *layer, VampEvent *event);

    void *__child__; /**< @private*/
    void (*__ChildDeconstructor__)(void *); /**< @private*/
    VampApplication *__app__; /**< @private*/
}
VampLayer;


/**
 * User defined callback: Gets called only ONCE after the layer has been
 * attached to the application.
 * 
 * @param[in] this The users custom layer that has been attached.
*/
typedef void (*VampLayerOnAttachFunc)(void *this);

/**
 * User defined callback: Gets called only ONCE after the layer has been
 * removed from the application.
 * 
 * @param[in] this The users custom layer that has been removed.
*/
typedef void (*VampLayerOnDetachFunc)(void *this);

/**
 * User defined callback: Gets called in every frame update.
 * 
 * @param[in] this The users custom layer that has been updated.
*/
typedef void (*VampLayerOnUpdateFunc)(void *this);


/**
 * User defined callback: Gets called when an event occurs.
 * 
 * @param[in] this The users custom layer object.
*/
typedef void (*VampLayerOnEventFunc)(void *this, VampEvent *event);




/**
 * Creates a new VampLayer object.
 * 
 * @param[in] app The application object.
 * 
 * @private
 * 
 * @returns The newly created object.
*/
VampLayer *__VampNewLayer__(VampApplication *app);




/**
 * Destroys a layer object.
 * 
 * @param[in] layer The VampLayer to be destroyed.
*/
void VampDestroyLayer(VampLayer *layer);




/**
 * The users who want to implement a layer must create
 * their own structure and use this macro at the top
 * of the structure decleration:
 * struct MyStruct
 * {
 *      VAMP_LAYER_DECLERATION
 *      .
 *      <my other stuff here>
 *      .
 *      .
 *      .
 * }
*/
#define VAMP_LAYER_DECLERATION\
    VampLayer *__vamp_base__;



/**
 * Once MyStruct has been declared, the users must create a function
 * that returns a VampLayer * object. That function MUST have the
 * following macro at THE END, since it returns a
 * VampLayer * object. Also in the same file, you MUST define a 
 * static void Deconstructor(void *mylayer) where you will free/destroy
 * your_layer_object. 
*/
#define VAMP_LAYER_IMPLEMENTATION(your_layer_object, app, OnAttach, OnDetach, OnUpdate, OnEvent)\
    VampLayer *__vamp_new_layer__               = __VampNewLayer__(app);\
    __vamp_new_layer__->__OnAttach__            = OnAttach;\
    __vamp_new_layer__->__OnDetach__            = OnDetach;\
    __vamp_new_layer__->__OnUpdate__            = OnUpdate;\
    __vamp_new_layer__->__OnEvent__             = OnEvent;\
    __vamp_new_layer__->__child__               = your_layer_object;\
    __vamp_new_layer__->__ChildDeconstructor__  = Deconstructor;\
    your_layer_object->__vamp_base__            = __vamp_new_layer__;\
    return __vamp_new_layer__;




#endif