#ifndef VAMP_ENGINE_APPLICATION_H
#define VAMP_ENGINE_APPLICATION_H


typedef struct VampLogger VampLogger;
typedef struct VampMemoryTracker VampMemoryTracker;
typedef struct VampWindow VampWindow;

typedef struct VampApplication
{
    VampWindow *__window__;

    void (*__user_entry_point__)(struct VampApplication *app);

    void (*Run)(struct VampApplication *app);
}
VampApplication;

typedef void (*UserEntryPoint)(VampApplication *app);

VampApplication *VampCreateUserApplication();

VampApplication *VampNewApplication(UserEntryPoint user, const char *title, int width, int height);

void VampDestroyApplication(VampApplication *app);

#endif