#ifndef INT_TYPES_H
#define INT_TYPES_H

#include <cstdint>
#include <type_traits>

// https://peter.bloomfield.online/using-cpp-templates-for-size-based-type-selection/

// clang-format off
template <std::uint8_t N>
using uint_t = typename std::enable_if<N <=64,
    typename std::conditional<N <= 8, std::uint8_t,
        typename std::conditional<N <= 16, std::uint16_t,
            typename std::conditional<N <= 32, std::uint32_t,
                std::uint64_t
                >::type
            >::type
        >::type>::type;
// clang-format on

// clang-format off
template <std::uint8_t N>
using int_t = typename std::enable_if<N <=64,
    typename std::conditional<N <= 8, std::int8_t,
        typename std::conditional<N <= 16, std::int16_t,
            typename std::conditional<N <= 32, std::int32_t,
                std::int64_t
                >::type
            >::type
        >::type>::type;
// clang-format on

// clang-format off
template <std::uint8_t N>
using uint_fast_t = typename std::enable_if<N <=64,
    typename std::conditional<N <= 8, std::uint_fast8_t,
        typename std::conditional<N <= 16, std::uint_fast16_t,
            typename std::conditional<N <= 32, std::uint_fast32_t,
                std::uint_fast64_t
                >::type
            >::type
        >::type>::type;
// clang-format on

// clang-format off
template <std::uint8_t N>
using int_fast_t = typename std::enable_if<N <=64,
    typename std::conditional<N <= 8, std::int_fast8_t,
        typename std::conditional<N <= 16, std::int_fast16_t,
            typename std::conditional<N <= 32, std::int_fast32_t,
                std::int_fast64_t
                >::type
            >::type
        >::type>::type;
// clang-format on

template<typename T> inline constexpr T signum(T x, std::false_type)
{
    return T(0) < x;
}

template<typename T> inline constexpr T signum(T x, std::true_type)
{
    return (T(0) < x) - (x < T(0));
}

template<typename T> inline constexpr T signum(T x)
{
    return signum(x, std::is_signed<T>());
}

#endif // INT_TYPES_H
