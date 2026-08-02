#pragma once

#define SHADOW_BEGIN_NAMESPACE namespace Shadow {
#define SHADOW_END_NAMESPACE }

#define BIT(x) (1 << x)

#ifdef SHADOW_PLATFORM_WINDOWS
    #ifdef SHADOW_BUILD_DLL
        #define SHADOW_API __declspec(dllexport)
    #else
        #define SHADOW_API __declspec(dllimport)
    #endif
#else
    #error "Only Windows platform is supported!"
#endif