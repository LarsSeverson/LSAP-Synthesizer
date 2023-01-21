#pragma once

#ifdef LS_PLATFORM_WINDOWS
#ifdef LS_BUILD_DLL
#define LSAP_API _declspec(dllexport)
#else 
#define LSAP_API _declspec(dllimport)
#endif
#else 
#error LSAP is only for Windows.
#endif