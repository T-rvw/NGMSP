#pragma once

#include <Core/HAL/BasicTypes.h>

namespace
{

template<typename T>
struct FastCRCTraits;

template<>
struct FastCRCTraits<uint32>
{
    using T = uint32;
    static constexpr T Polynomial = 0xEDB88320;
};

}

namespace ow
{

template<typename T>
constexpr T FastCRCHash(const char* data, uint64 length)
{
    using Traits = FastCRCTraits<T>;
    T crc = 0;
    while (length--)
    {
        crc ^= *data++;

        crc = (crc >> 1) ^ (-int(crc & 1) & Traits::Polynomial);
        crc = (crc >> 1) ^ (-int(crc & 1) & Traits::Polynomial);
        crc = (crc >> 1) ^ (-int(crc & 1) & Traits::Polynomial);
        crc = (crc >> 1) ^ (-int(crc & 1) & Traits::Polynomial);
        crc = (crc >> 1) ^ (-int(crc & 1) & Traits::Polynomial);
        crc = (crc >> 1) ^ (-int(crc & 1) & Traits::Polynomial);
        crc = (crc >> 1) ^ (-int(crc & 1) & Traits::Polynomial);
        crc = (crc >> 1) ^ (-int(crc & 1) & Traits::Polynomial);
    }
    return ~crc;
}

}