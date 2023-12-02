#ifndef VAMP_ENGINE_ENTRY_POINT_H
#define VAMP_ENGINE_ENTRY_POINT_H


#ifdef VAMP_ENGINE_ENTRY_POINT
/**
 * The entry point supported by most operating systems.
*/
int main(int argc, char **argv)
{
    //Create the application using the users defined function.
    VampApplication *new_app = VampCreateUserApplication();

    //Set the function pointer to the users entry point (starting location of the user's code).
    new_app->__user_entry_point__(new_app);

    //Run the app.
    new_app->Run(new_app);

    //Destroy the application (which was created by the user).
    VampDestroyApplication(new_app);

    return 0;
}
#endif

#endif