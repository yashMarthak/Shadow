#pragma once

#ifdef SHADOW_PLATFORM_WINDOWS
	#ifdef SHADOW_BUILD_DLL
		#define SHADOW_API __declspec(dllexport)
	#else
		#define SHADOW_API __declspec(dllimport)
    #endif
#else
	#error "Only Windows platform is supported!"
#endif