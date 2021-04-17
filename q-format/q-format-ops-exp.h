#ifndef QFORMATOPERATIONSEXP_INL
#define QFORMATOPERATIONSEXP_INL

#include "q-format.h"

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::pow(const q &f,
                                                     uint8_t  exp) const
{
    q ret;
    if constexpr (T_numBits == 1)
    {
        if (exp == 0)
        {
            return q::max();
        }
        ret = q::max();
        exp--;
    }
    else
    {
        ret = q(1.0);
    }
    while (exp--)
    {
        ret = ret * f;
    }
    return ret;
}

#endif // QFORMATOPERATIONSEXP_INL
