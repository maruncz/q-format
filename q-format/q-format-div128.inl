#ifndef QFORMATDIV128_INL
#define QFORMATDIV128_INL

#include "int_types.h"
#include <cmath>
#include <utility>

template <std::uint8_t T_numBits>
void pair_shift(uint_t<T_numBits> &a, uint_t<T_numBits> &b, uint8_t len)
{
    a *= 2;
    if (b & (1 << len))
    {
        a += 1;
    }
    b *= 2;
    b = b & ((1 << (len + 1)) - 1);
}

template <std::uint8_t T_numBits> uint8_t q_len(uint_t<T_numBits> q)
{
    return floor(log2(q));
}

template <std::uint8_t T_numBits> union tmpA
{
    uint_t<T_numBits> u;
    int_t<T_numBits>  i;
};

// https://stackoverflow.com/questions/12133810/non-restoring-division-algorithm

template <std::uint8_t numRes>
std::pair<int_t<numRes>, int_t<numRes>> qf_div128(int_t<numRes> m1,
                                                  int_t<numRes> m2)
{
    // m1/m2
    auto sign = signum(m1) * signum(m2);
    m1        = m1 * signum(m1);
    m2        = m2 * signum(m2);
    tmpA<numRes> a;
    a.u = 0;

    // q/m = q,a
    uint_t<numRes> m   = m2;
    uint_t<numRes> q   = m1;
    uint8_t        len = q_len<numRes>(q);
    int8_t         i   = len + 1;

    do {
        pair_shift<numRes>(a.u, q, len);
        if (a.i < 0)
        {
            a.i += m;
        }
        else
        {
            a.i -= m;
        }
        if (a.i > 0)
        {
            q += 1;
        }
        --i;
    } while (i > 0);

    if (a.i < 0)
    {
        a.i += m;
        //--q;
    }

    return std::pair<int_t<numRes>, int_t<numRes>>(q * sign, a.i * sign);
}

#endif // QFORMATDIV128_INL
