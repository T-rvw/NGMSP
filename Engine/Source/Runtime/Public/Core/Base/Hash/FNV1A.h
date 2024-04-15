#pragma once

#include <Core/HAL/BasicTypes.h>

namespace
{

template<typename T>
struct FNV1ATraits;

template<>
struct FNV1ATraits<uint32>
{
    using T = uint32;
    static constexpr T Offset = 2166136261U;
    static constexpr T Prime = 16777619U;
};

template<>
struct FNV1ATraits<uint64>
{
    using T = uint64;
    static constexpr T Offset = 14695981039346656037ULL;
    static constexpr T Prime = 1099511628211ULL;
};

}

namespace ow
{

template<typename T>
constexpr T FNV1AHash(const char* data, uint64 length, T seed)
{
    using Traits = FNV1ATraits<T>;

    T result = seed;
    for (uint64 i = 0; i < length; ++i)
    {
        result = (result ^ static_cast<typename Traits::T>(data[i])) * Traits::Prime;
    }

    return result;
}

}