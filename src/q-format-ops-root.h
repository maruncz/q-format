#ifndef QFORMATOPERATIONSROOT_H
#define QFORMATOPERATIONSROOT_H

// https://math.stackexchange.com/questions/462443/calculating-non-integer-exponent

#include "q-format-ops-basic.h"
#include "q-format-ops-exp.h"
#include "q-format.h"

/**
 * @bug nefunguje protoze f2 se zaokrouhli na 0
 */
template <std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::root(uint8_t exp) const
{
    q ret(*this);
    ret    = max(q(1.0), ret / exp);
    q prev = ret;
    for (int i = 0; i < 10; ++i)
    {
        q f1 = pow(ret, exp) - ret;
        q f2 = pow(ret, exp - 1) * exp;
        q f3 = f1/f2;
        ret  = ret - f3;
        if (abs(ret - prev) < q::eps())
        {
            break;
        }
        prev = ret;
    }
    return ret;
}

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::sqrt() const
{
    return root(2);
}

#endif // QFORMATOPERATIONSROOT_H
