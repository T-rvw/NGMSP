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

#define ENGINE_API API_EXPORT

#include <Core/HAL/BasicTypes.h>

#include <string>
#include <utility>
#include <vector>