#pragma once

#include <cstdint>
#include <cstddef>

namespace Bang
{
using GLId = uint64_t;
using Byte = uint8_t;
using BoolByte = Byte;
using EpochTime = uint64_t;

template <class EnumT>
constexpr EnumT Undef()
{
    return static_cast<EnumT>(-1);
}

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};
}
