#pragma once

using int8 = signed char;
using int16 = signed short int;
using int32 = signed int;
using int64 = signed long long;
using uint8 = unsigned char;
using uint16 = unsigned short int;
using uint32 = unsigned int;
using uint64 = unsigned long long;

static_assert(1 == sizeof(int8));
static_assert(2 == sizeof(int16));
static_assert(4 == sizeof(int32));
static_assert(8 == sizeof(int64));
static_assert(1 == sizeof(uint8));
static_assert(2 == sizeof(uint16));
static_assert(4 == sizeof(uint32));
static_assert(8 == sizeof(uint64));

#define UNUSED(a) (a)

#include <cassert>