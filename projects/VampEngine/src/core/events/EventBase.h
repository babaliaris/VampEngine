#ifndef VAMP_ENGINE_EVENT_BASE_H
#define VAMP_ENGINE_EVENT_BASE_H

/**
 * @file
*/

#define VAMP_EVENT_KEY_PRESSED              0
#define VAMP_EVENT_KEY_RELEASED             1
#define VAMP_EVENT_KEY_REPEAT               2
#define VAMP_EVENT_MOUSE_PRESSED            3
#define VAMP_EVENT_MOUSE_RELEASED           4
#define VAMP_EVENT_MOUSE_POS                5
#define VAMP_EVENT_WINDOW_FOCUSED           6
#define VAMP_EVENT_WINDOW_LOST_FOCUS        7
#define VAMP_EVENT_WINDOW_CLOSE             8
#define VAMP_EVENT_WINDOW_MINIMIZED         9
#define VAMP_EVENT_WINDOW_MAXIMIZED         10
#define VAMP_EVENT_WINDOW_RESTORED          11
#define VAMP_EVENT_WINDOW_RESIZED           12
#define VAMP_EVENT_WINDOW_MOVED             13



/* The unknown key */
#define VAMP_KEY_UNKNOWN            -1

/* Printable keys */
#define VAMP_KEY_SPACE              32
#define VAMP_KEY_APOSTROPHE         39  /* ' */
#define VAMP_KEY_COMMA              44  /* , */
#define VAMP_KEY_MINUS              45  /* - */
#define VAMP_KEY_PERIOD             46  /* . */
#define VAMP_KEY_SLASH              47  /* / */
#define VAMP_KEY_0                  48
#define VAMP_KEY_1                  49
#define VAMP_KEY_2                  50
#define VAMP_KEY_3                  51
#define VAMP_KEY_4                  52
#define VAMP_KEY_5                  53
#define VAMP_KEY_6                  54
#define VAMP_KEY_7                  55
#define VAMP_KEY_8                  56
#define VAMP_KEY_9                  57
#define VAMP_KEY_SEMICOLON          59  /* ; */
#define VAMP_KEY_EQUAL              61  /* = */
#define VAMP_KEY_A                  65
#define VAMP_KEY_B                  66
#define VAMP_KEY_C                  67
#define VAMP_KEY_D                  68
#define VAMP_KEY_E                  69
#define VAMP_KEY_F                  70
#define VAMP_KEY_G                  71
#define VAMP_KEY_H                  72
#define VAMP_KEY_I                  73
#define VAMP_KEY_J                  74
#define VAMP_KEY_K                  75
#define VAMP_KEY_L                  76
#define VAMP_KEY_M                  77
#define VAMP_KEY_N                  78
#define VAMP_KEY_O                  79
#define VAMP_KEY_P                  80
#define VAMP_KEY_Q                  81
#define VAMP_KEY_R                  82
#define VAMP_KEY_S                  83
#define VAMP_KEY_T                  84
#define VAMP_KEY_U                  85
#define VAMP_KEY_V                  86
#define VAMP_KEY_W                  87
#define VAMP_KEY_X                  88
#define VAMP_KEY_Y                  89
#define VAMP_KEY_Z                  90
#define VAMP_KEY_LEFT_BRACKET       91  /* [ */
#define VAMP_KEY_BACKSLASH          92  /* \ */
#define VAMP_KEY_RIGHT_BRACKET      93  /* ] */
#define VAMP_KEY_GRAVE_ACCENT       96  /* ` */
#define VAMP_KEY_WORLD_1            161 /* non-US #1 */
#define VAMP_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define VAMP_KEY_ESCAPE             256
#define VAMP_KEY_ENTER              257
#define VAMP_KEY_TAB                258
#define VAMP_KEY_BACKSPACE          259
#define VAMP_KEY_INSERT             260
#define VAMP_KEY_DELETE             261
#define VAMP_KEY_RIGHT              262
#define VAMP_KEY_LEFT               263
#define VAMP_KEY_DOWN               264
#define VAMP_KEY_UP                 265
#define VAMP_KEY_PAGE_UP            266
#define VAMP_KEY_PAGE_DOWN          267
#define VAMP_KEY_HOME               268
#define VAMP_KEY_END                269
#define VAMP_KEY_CAPS_LOCK          280
#define VAMP_KEY_SCROLL_LOCK        281
#define VAMP_KEY_NUM_LOCK           282
#define VAMP_KEY_PRINT_SCREEN       283
#define VAMP_KEY_PAUSE              284
#define VAMP_KEY_F1                 290
#define VAMP_KEY_F2                 291
#define VAMP_KEY_F3                 292
#define VAMP_KEY_F4                 293
#define VAMP_KEY_F5                 294
#define VAMP_KEY_F6                 295
#define VAMP_KEY_F7                 296
#define VAMP_KEY_F8                 297
#define VAMP_KEY_F9                 298
#define VAMP_KEY_F10                299
#define VAMP_KEY_F11                300
#define VAMP_KEY_F12                301
#define VAMP_KEY_F13                302
#define VAMP_KEY_F14                303
#define VAMP_KEY_F15                304
#define VAMP_KEY_F16                305
#define VAMP_KEY_F17                306
#define VAMP_KEY_F18                307
#define VAMP_KEY_F19                308
#define VAMP_KEY_F20                309
#define VAMP_KEY_F21                310
#define VAMP_KEY_F22                311
#define VAMP_KEY_F23                312
#define VAMP_KEY_F24                313
#define VAMP_KEY_F25                314
#define VAMP_KEY_KP_0               320
#define VAMP_KEY_KP_1               321
#define VAMP_KEY_KP_2               322
#define VAMP_KEY_KP_3               323
#define VAMP_KEY_KP_4               324
#define VAMP_KEY_KP_5               325
#define VAMP_KEY_KP_6               326
#define VAMP_KEY_KP_7               327
#define VAMP_KEY_KP_8               328
#define VAMP_KEY_KP_9               329
#define VAMP_KEY_KP_DECIMAL         330
#define VAMP_KEY_KP_DIVIDE          331
#define VAMP_KEY_KP_MULTIPLY        332
#define VAMP_KEY_KP_SUBTRACT        333
#define VAMP_KEY_KP_ADD             334
#define VAMP_KEY_KP_ENTER           335
#define VAMP_KEY_KP_EQUAL           336
#define VAMP_KEY_LEFT_SHIFT         340
#define VAMP_KEY_LEFT_CONTROL       341
#define VAMP_KEY_LEFT_ALT           342
#define VAMP_KEY_LEFT_SUPER         343
#define VAMP_KEY_RIGHT_SHIFT        344
#define VAMP_KEY_RIGHT_CONTROL      345
#define VAMP_KEY_RIGHT_ALT          346
#define VAMP_KEY_RIGHT_SUPER        347
#define VAMP_KEY_MENU               348


/*! @} */

/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

/*! @brief If this bit is set one or more Shift keys were held down.
 *
 *  If this bit is set one or more Shift keys were held down.
 */
#define VAMP_MOD_SHIFT           0x0001
/*! @brief If this bit is set one or more Control keys were held down.
 *
 *  If this bit is set one or more Control keys were held down.
 */
#define VAMP_MOD_CONTROL         0x0002
/*! @brief If this bit is set one or more Alt keys were held down.
 *
 *  If this bit is set one or more Alt keys were held down.
 */
#define VAMP_MOD_ALT             0x0004
/*! @brief If this bit is set one or more Super keys were held down.
 *
 *  If this bit is set one or more Super keys were held down.
 */
#define VAMP_MOD_SUPER           0x0008
/*! @brief If this bit is set the Caps Lock key is enabled.
 *
 *  If this bit is set the Caps Lock key is enabled and the @ref
 *  VAMP_LOCK_KEY_MODS input mode is set.
 */
#define VAMP_MOD_CAPS_LOCK       0x0010
/*! @brief If this bit is set the Num Lock key is enabled.
 *
 *  If this bit is set the Num Lock key is enabled and the @ref
 *  VAMP_LOCK_KEY_MODS input mode is set.
 */
#define VAMP_MOD_NUM_LOCK        0x0020

/*! @} */

/*! @defgroup buttons Mouse buttons
 *  @brief Mouse button IDs.
 *
 *  See [mouse button input](@ref input_mouse_button) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define VAMP_MOUSE_BUTTON_1         0
#define VAMP_MOUSE_BUTTON_2         1
#define VAMP_MOUSE_BUTTON_3         2
#define VAMP_MOUSE_BUTTON_4         3
#define VAMP_MOUSE_BUTTON_5         4
#define VAMP_MOUSE_BUTTON_6         5
#define VAMP_MOUSE_BUTTON_7         6
#define VAMP_MOUSE_BUTTON_8         7
#define VAMP_MOUSE_BUTTON_LAST      VAMP_MOUSE_BUTTON_8
#define VAMP_MOUSE_BUTTON_LEFT      VAMP_MOUSE_BUTTON_1
#define VAMP_MOUSE_BUTTON_RIGHT     VAMP_MOUSE_BUTTON_2
#define VAMP_MOUSE_BUTTON_MIDDLE    VAMP_MOUSE_BUTTON_3


/*! @} */

/*! @defgroup joysticks Joysticks
 *  @brief Joystick IDs.
 *
 *  See [joystick input](@ref joystick) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define VAMP_JOYSTICK_1             0
#define VAMP_JOYSTICK_2             1
#define VAMP_JOYSTICK_3             2
#define VAMP_JOYSTICK_4             3
#define VAMP_JOYSTICK_5             4
#define VAMP_JOYSTICK_6             5
#define VAMP_JOYSTICK_7             6
#define VAMP_JOYSTICK_8             7
#define VAMP_JOYSTICK_9             8
#define VAMP_JOYSTICK_10            9
#define VAMP_JOYSTICK_11            10
#define VAMP_JOYSTICK_12            11
#define VAMP_JOYSTICK_13            12
#define VAMP_JOYSTICK_14            13
#define VAMP_JOYSTICK_15            14
#define VAMP_JOYSTICK_16            15



/*! @} */

/*! @defgroup gamepad_buttons Gamepad buttons
 *  @brief Gamepad buttons.
 *
 *  See @ref gamepad for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define VAMP_GAMEPAD_BUTTON_A               0
#define VAMP_GAMEPAD_BUTTON_B               1
#define VAMP_GAMEPAD_BUTTON_X               2
#define VAMP_GAMEPAD_BUTTON_Y               3
#define VAMP_GAMEPAD_BUTTON_LEFT_BUMPER     4
#define VAMP_GAMEPAD_BUTTON_RIGHT_BUMPER    5
#define VAMP_GAMEPAD_BUTTON_BACK            6
#define VAMP_GAMEPAD_BUTTON_START           7
#define VAMP_GAMEPAD_BUTTON_GUIDE           8
#define VAMP_GAMEPAD_BUTTON_LEFT_THUMB      9
#define VAMP_GAMEPAD_BUTTON_RIGHT_THUMB     10
#define VAMP_GAMEPAD_BUTTON_DPAD_UP         11
#define VAMP_GAMEPAD_BUTTON_DPAD_RIGHT      12
#define VAMP_GAMEPAD_BUTTON_DPAD_DOWN       13
#define VAMP_GAMEPAD_BUTTON_DPAD_LEFT       14

#define VAMP_GAMEPAD_BUTTON_CROSS       VAMP_GAMEPAD_BUTTON_A
#define VAMP_GAMEPAD_BUTTON_CIRCLE      VAMP_GAMEPAD_BUTTON_B
#define VAMP_GAMEPAD_BUTTON_SQUARE      VAMP_GAMEPAD_BUTTON_X
#define VAMP_GAMEPAD_BUTTON_TRIANGLE    VAMP_GAMEPAD_BUTTON_Y



/*! @} */

/*! @defgroup gamepad_axes Gamepad axes
 *  @brief Gamepad axes.
 *
 *  See @ref gamepad for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define VAMP_GAMEPAD_AXIS_LEFT_X        0
#define VAMP_GAMEPAD_AXIS_LEFT_Y        1
#define VAMP_GAMEPAD_AXIS_RIGHT_X       2
#define VAMP_GAMEPAD_AXIS_RIGHT_Y       3
#define VAMP_GAMEPAD_AXIS_LEFT_TRIGGER  4
#define VAMP_GAMEPAD_AXIS_RIGHT_TRIGGER 5






/**
 * User Defined Function: This is the callback function that
 * the VampEvent Dispatcher will call.
 * 
 * @param[in] event The event object that has been dispatched.
 * @returns 1 (true) to stop propagating this event higher to the layers list. 0 (false) otherwise.
*/
typedef char (*VampEventDispatchFunc)(void *event, void *userPointer);


typedef struct VampApplication VampApplication;


/**
 * Event structure.
*/
typedef struct VampEvent
{
    /**
     * Get the application object.
     * 
     * @param[in] event The event object.
     * @returns The VampApplication object.
    */
    VampApplication *(*GetApp)(struct VampEvent *event);


    /**
     * Dispatches the event into a callback that gets called only if the event type
     * matches the type parameter of the Despatch() method.
     * 
     * @param[in] event The VampEvent object to be dispatched.
     * @param[in] type The VAMP_EVENT type that is required.
     * @param[in] callback The VampEventDispatchFunc() user defined function.
    */
    void (*Dispatch)(struct VampEvent *event, unsigned int type, VampEventDispatchFunc callback, void *userPointer);



    void *__child__; /**< @private*/
    void (*__ChildDecontructor__)(void *child); /**< @private*/
    VampApplication *__app__; /**< @private*/
    unsigned int __type__; /**< @private*/
    char __has_been_handled__; /**< @private*/
}
VampEvent;


/**
 * @private
*/
VampEvent *__VampNewEvent__(VampApplication *app, unsigned int type);


/**
 * Destroys the VampEvent object.
 * 
 * @param[in] event
*/
void VampDestroyEvent(VampEvent *event);



/**
 * Return a sting representing the VAMP_EVENT type definition.
 * 
 * @param[in] type the VAMP_EVENT type definition.
*/
const char *VampEventTypeToString(unsigned int type);


#endif