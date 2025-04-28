#ifndef VAMP_APPLICATION_H
#define VAMP_APPLICATION_H
#include <VampEngine/core/vamp_platform.h>

typedef struct VampApplication
{

    void (*run)(struct VampApplication *pThis);

}VampApplication;


VAMP_API VampApplication *vampCreateApplication();

VAMP_API char vampDestroyApplication(VampApplication **pApp);

//The user must implement this function!
VampApplication *userApplicationEntry();

#endif