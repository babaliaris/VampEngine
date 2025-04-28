#ifndef VAMP_PLATFORM_H
#define VAMP_PLATFORM_H

    //Define a useful macro, to indicate all supported PC operating systems.
    #if defined(VAMP_LINUX) || defined(VAMP_WINDOWS) || defined(VAMP_MACOS)
        #define VAMP_ALL_PC_PLATFORMS 1

    //If we compile for other platforms (like playstation) that is not
    //a PC desctop platform.
    #else
        #define VAMP_ALL_PC_PLATFORMS 0
        #error This platform is not supported yet...

    #endif
    
    //This is only required by the Microsoft Compiler!
    #if defined(VAMP_WINDOWS) && defined(_MSC_VER)
        #define VAMP_API __declspec( dllexport )

    //Else, just define VAMP_API to be nothing.
    #else
        #define VAMP_API
    #endif
    
#endif