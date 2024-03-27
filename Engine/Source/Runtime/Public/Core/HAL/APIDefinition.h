#pragma once

#ifdef _MSC_VER
#define API_EXPORT __declspec(dllexport)
#define API_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#define API_EXPORT __attribute__((visibility("default")))
#define API_IMPORT
#else
#define API_EXPORT
#define API_IMPORT
#endif

#ifdef ENGINE_BUILD_SHARED
#define ENGINE_API API_EXPORT
#define RHI_API API_EXPORT
#else
#define ENGINE_API API_IMPORT
#define RHI_API API_IMPORT
#endif