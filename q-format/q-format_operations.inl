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
    static_assert(numRes > denBits, "error: !(numRes > denBits)");

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

    {
        uint_t<numRes> carry = 0;
        uint_t<numRes> tmpM  = (M & maskLow) << (numRes / 2);
        if ((tmpM > 0) &&
            (L > (std::numeric_limits<uint_t<numRes>>::max() - tmpM)))
        {
            carry = 1;
        }
        L += tmpM;

        tmpM = (M & maskHigh) >> (numRes / 2);
        H    = H + tmpM + carry;
    }

    constexpr int8_t expH = numRes - denBits;
    constexpr int8_t expL = denBits;

    H                    = (H << expH);
    uint_t<numRes> tmpL  = (L >> (expL - 1));
    uint_t<numRes> round = tmpL & 1;
    L                    = tmpL >> 1;

    return (H + L + round) * sign;
}

#endif // QFORMAT_OPERATIONS_INL
