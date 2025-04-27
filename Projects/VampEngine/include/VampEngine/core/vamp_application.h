#ifndef VAMP_APPLICATION_H
#define VAMP_APPLICATION_H

typedef struct VampApplication
{

    void (*run)(struct VampApplication *pThis);

}VampApplication;


VampApplication *vampCreateApplication();

char vampDestroyApplication(VampApplication **pApp);

//The user must implement this function!
VampApplication *userApplicationEntry();

#endif