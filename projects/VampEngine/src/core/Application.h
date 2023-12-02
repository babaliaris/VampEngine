#ifndef VAMP_ENGINE_APPLICATION_H
#define VAMP_ENGINE_APPLICATION_H

/**
 * @file
 * @brief The Application.h header file.
*/


typedef struct VampLogger VampLogger;
typedef struct VampMemoryTracker VampMemoryTracker;
typedef struct VampWindow VampWindow;

/**
 * The application object.
*/
typedef struct VampApplication
{
    VampWindow *__window__; /**< The window to draw stuff in it.*/

    /**
     * The entry point of the user.
     * 
     * @param[in] app The application object.
    */
    void (*__user_entry_point__)(struct VampApplication *app);

    /**
     * Runs the application. It is called automatically 
     * by the the EntryPoint.h
     * 
     * @param[in] The application object.
    */
    void (*Run)(struct VampApplication *app);
}
VampApplication;


/**
 * Function pointer type: A function defined by the user
 * and passed to VampNewApplication() . VampApplication
 * will call the user entry point once the application has started.
 * 
 * @param[in] app The VampApplication object.
*/
typedef void (*UserEntryPoint)(VampApplication *app);


/**
 * A function that MUST be implemented by the user. This function
 * should return a @ref VampApplication * application by calling
 * VampNewApplication() .
 * 
 * @returns The created application.
*/
VampApplication *VampCreateUserApplication();


/**
 * Used to create a new Application. Should be return by VampCreateUserApplication.
 * 
 * @param[in] user The UserEntryPoint() defined by the user.
 * @param[in] title The VampWindow Title
 * @param[in] width The VampWindow Width
 * @param[in] height The VampWindow Height.
 * 
 * @returns The created application.
*/
VampApplication *VampNewApplication(UserEntryPoint user, const char *title, int width, int height);


/**
 * Destroys the application. This is going to be called automatically by the EntryPoint.h
 * and it will destroy the application object that the user provided by the VampCreateUserApplication()
 * function.
 * 
 * @param[in] app The VampApplication to be destroyed.
*/
void VampDestroyApplication(VampApplication *app);

#endif