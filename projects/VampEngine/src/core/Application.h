#ifndef VAMP_ENGINE_APPLICATION_H
#define VAMP_ENGINE_APPLICATION_H


typedef struct VampLogger VampLogger;
typedef struct VampMemoryTracker VampMemoryTracker;

typedef struct VampApplication
{
    VampLogger *__engine_logger__;
    VampLogger *__client_logger__;
    VampMemoryTracker *__memory_tracker__;

    void (*__user_entry_point__)(struct VampApplication *app);

    void (*Run)(struct VampApplication *app);

    VampMemoryTracker * (*GetTracker)(struct VampApplication *app);
}
VampApplication;

typedef void (*UserEntryPoint)(VampApplication *app);

VampApplication *VampCreateUserApplication();

VampApplication *VampNewApplication(UserEntryPoint user);

void VampDestroyApplication(VampApplication *app);

#endif