#ifndef QFORMAT_OPERATIONS_INL
#define QFORMAT_OPERATIONS_INL

#include "int_types.h"
#include <limits>

template<typename T> inline constexpr int signum(T x, std::false_type)
{
    return T(0) < x;
}

template<typename T> inline constexpr int signum(T x, std::true_type)
{
    return (T(0) < x) - (x < T(0));
}

template<typename T> inline constexpr int signum(T x)
{
    return signum(x, std::is_signed<T>());
}

// https://www.techiedelight.com/multiply-16-bit-integers-using-8-bit-multiplier/
template<std::uint8_t numRes, std::uint8_t denBits>
int_t<numRes> qf_mul128(int_t<numRes> m1, int_t<numRes> m2)
{
    auto sign = signum(m1) * signum(m2);
    m1        = m1 * signum(m1);
    m2        = m2 * signum(m2);

    constexpr uint_t<numRes> maskLow  = (1ull << (numRes / 2)) - 1;
    constexpr uint_t<numRes> maskHigh = ((1ull << (numRes / 2)) - 1)
                                        << numRes / 2;
    uint_t<numRes / 2> m1Low  = (m1 & maskLow);
    uint_t<numRes / 2> m1High = (m1 & maskHigh) >> numRes / 2;

    uint_t<numRes / 2> m2Low  = (m2 & maskLow);
    uint_t<numRes / 2> m2High = (m2 & maskHigh) >> numRes / 2;

    uint_t<numRes> H = m1High * m2High;
    uint_t<numRes> M = (m1High * m2Low) + (m1Low * m2High);
    uint_t<numRes> L = m1Low * m2Low;

    constexpr int8_t expH = numRes - denBits;
    constexpr int8_t expM = (numRes / 2) - denBits;
    constexpr int8_t expL = -denBits;

    uint_t<numRes> carryH = 0;
    uint_t<numRes> carryM = 0;

    if constexpr (expH > 0)
    {
        H = H << expH;
    }
    else
    {
        constexpr uint_t<numRes> maskH = (1ull << -expH) - 1;
        carryH                         = (H & maskH) >> (expH - expM);
        H                              = H >> -expH;
    }

    if constexpr (expM > 0)
    {
        M = M << expM;
    }
    else
    {
        constexpr uint_t<numRes> maskM = (1ull << -expM) - 1;
        carryM                         = (M & maskM);
        M                              = (M >> -expM) + carryH;
    }

    if constexpr (expL > 0)
    {
        L = L << expL;
    }
    else
    {
        carryM = carryM >> ((expM - expL) - 1);
        L      = (L >> (-expL - 1)) + carryM;
        if (L & 1)
        {
            L = (L >> 1) + 1;
        }
        else
        {
            L = L >> 1;
        }
    }

    return (H + M + L) * sign;
}

#endif // QFORMAT_OPERATIONS_INL
