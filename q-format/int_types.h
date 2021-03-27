#ifndef INT_TYPES_H
#define INT_TYPES_H

#include <cstdint>
#include <type_traits>

// https://peter.bloomfield.online/using-cpp-templates-for-size-based-type-selection/

// clang-format off
template <std::uint8_t T_numBits>
using uint_t = typename std::enable_if<T_numBits <=64,
    typename std::conditional<T_numBits <= 8, std::uint8_t,
        typename std::conditional<T_numBits <= 16, std::uint16_t,
            typename std::conditional<T_numBits <= 32, std::uint32_t,
                std::uint64_t
                >::type
            >::type
        >::type>::type;
// clang-format on

// clang-format off
template <std::uint8_t T_numBits>
using int_t = typename std::enable_if<T_numBits <=64,
    typename std::conditional<T_numBits <= 8, std::int8_t,
        typename std::conditional<T_numBits <= 16, std::int16_t,
            typename std::conditional<T_numBits <= 32, std::int32_t,
                std::int64_t
                >::type
            >::type
        >::type>::type;
// clang-format on

#endif // INT_TYPES_H
