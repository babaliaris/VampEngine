#ifndef VAMP_ENGINE_ENTRY_POINT_H
#define VAMP_ENGINE_ENTRY_POINT_H


#ifdef VAMP_ENGINE_ENTRY_POINT
int main(int argc, char **argv)
{
    VampApplication *new_app = VampCreateUserApplication();
    new_app->__user_entry_point__(new_app);
    new_app->Run(new_app);
    VampDestroyApplication(new_app);
    return 0;
}
#endif

#endif