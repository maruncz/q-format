#ifndef QFORMATOPERATIONSROOT_H
#define QFORMATOPERATIONSROOT_H

// https://math.stackexchange.com/questions/462443/calculating-non-integer-exponent

#include "q-format.h"
#include <iostream>

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::root(int8_t exp) const
{
    q ret(*this);
    ret    = max(q(1.0), ret / exp);
    q prev = ret;
    for (int i = 0; i < 10; ++i)
    {
        q f1 = pow(ret, exp) - *this;
        q f2 = q(static_cast<int_tt>(exp)) * pow(ret, exp - 1);
        ret  = ret - (f1 / f2);
        if (abs(ret - prev) < q::eps())
        {
            break;
        }
        prev = ret;
        std::cout << ret.toDouble() << std::endl;
    }
    return ret;
}

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::sqrt() const
{
    return root(2);
}

#endif // QFORMATOPERATIONSROOT_H
