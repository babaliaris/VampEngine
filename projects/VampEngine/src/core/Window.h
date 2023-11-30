#ifndef VAMP_ENGINE_WINDOW_H
#define VAMP_ENGINE_WINDOW_H


typedef struct VampApplication VampApplication;
typedef struct VampString VampString;

typedef struct VampWindow
{
    void *__child__;
    unsigned int __child_type__;

    int __width__;
    int __height__;
    char __is_running__;
    VampString *__title__;
    VampApplication *__app__;

    int (*GetWidth)(struct VampWindow *window);

    int (*GetHeight)(struct VampWindow *window);

    const char *(*GetTitle)(struct VampWindow *window);

    void (*Update)(struct VampWindow *window);
}
VampWindow;


VampWindow *VampNewWindow(VampApplication *app, const char *title, int width, int height);

void VampDestroyWindow(VampWindow *window);

#endif