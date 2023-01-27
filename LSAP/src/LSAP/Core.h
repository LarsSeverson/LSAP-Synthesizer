#pragma once

#ifdef LS_PLATFORM_WINDOWS
#if LS_DYNAMIC_LINK
#ifdef LS_BUILD_DLL
#define LSAP_API _declspec(dllexport)
#else 
#define LSAP_API _declspec(dllimport)
#endif
#else
#define LSAP_API
#endif

#else 
#error LSAP is only for Windows.
#endif

#ifdef LS_DEBUG
#define LS_ENABLE_ASSERTS
#endif

#ifdef LS_ENABLE_ASSERTS
#define LS_ASSERT(x, ...) { if (!(x)) {LS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#define LS_CORE_ASSERT(x, ...) { if (!(x)) {LS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#define BIT(x) (1 << x)
#define LS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#endif