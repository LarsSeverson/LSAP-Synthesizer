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

#define LS_ASSERT(x, ...) { if (!(x)) {LS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#define LS_CORE_ASSERT(x, ...) { if (!(x)) {LS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#define BIT(x) (1 << x)