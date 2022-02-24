#pragma once

#ifdef PRESTO_PLATFORM_WINDOWS
#ifdef PRESTO_DLL
#ifdef PRESTO_BUILD_DLL
#define PRESTO_API __declspec(dllexport)
#else
#define PRESTO_API __declspec(dllimport)
#endif
#else
#define PRESTO_API
#endif
#endif

#ifdef PRESTO_DEBUG
#define PRESTO_ENABLE_ASSERTS
#endif

#ifdef PRESTO_ENABLE_ASSERTS
#define PRESTO_ASSERT(x, ...) { if(!(x)) { PRESTO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define PRESTO_CORE_ASSERT(x, ...) { if(!(x)) { PRESTO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define PRESTO_ASSERT(x, ...)
#define PRESTO_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x, y) std::bind(&x, y, std::placeholders::_1)