#pragma once

#ifdef PRESTO_PLATFORM_WINDOWS
#ifdef PRESTO_BUILD_DLL
#define PRESTO_API __declspec(dllexport)
#else
#define PRESTO_API __declspec(dllimport)
#endif
#endif

#define BIT(x) (1 << x)