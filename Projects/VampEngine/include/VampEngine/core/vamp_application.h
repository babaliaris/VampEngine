#ifndef VAMP_APPLICATION_H
#define VAMP_APPLICATION_H
#include <VampEngine/core/vamp_platform.h>

/**
 * @file
 * @brief This is the entry VampEngine API. Everything starts here!
 * 
 * @author Babaliaris Nikolaos
 * @date 05 May 2025
 */


/**
 * @brief The VampEngine application.
 * 
 * The user MUST create and return an instance of this 
 * struct, using `vampCreateApplication()` within his
 * own implementation of `userApplicationEntry()`
 */
typedef struct VampApplication
{
    /**
     * @brief Runs the application and the gameloop.
     * 
     * @param pThis The instance of this application.
     */
    void (*run)(struct VampApplication *pThis);

}VampApplication;


/**
 * @brief Create a `VampApplication` instance.
 * 
 * @return The newly created `VampApplication`, NULL if out of memory.
 */
VAMP_API VampApplication *vampCreateApplication();


/**
 * @brief Destroys the application and sets the users variable to NULL.
 * 
 * @param pApp the adress memory of the users variable that holds the `VampApplication` instance.
 * 
 * @return 1 on success, 0 otherwise.
 */
VAMP_API char vampDestroyApplication(VampApplication **pApp);


/**
 * @brief The users entry point function.
 * 
 * This function must be implemented by the user and return an instance of
 * `VampApplication` by calling: `vampCreateApplication()`. It will be called
 * automatically from the vamp_entryPoint.h
 * 
 * Example:
 *      VampApplication *userApplicationEntry()
 *      {
 *          return vampCreateApplication();
 *      }
 */
VampApplication *userApplicationEntry();

#endif