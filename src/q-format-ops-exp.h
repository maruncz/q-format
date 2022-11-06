#ifndef QFORMATOPERATIONSEXP_INL
#define QFORMATOPERATIONSEXP_INL

#include "q-format.h"
#include "q-format-ops-basic.h"

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::pow(const q &f,
                                                     uint8_t  exp) const
{
    q ret{f};
    if constexpr (T_numBits == 1)
    {
        if(exp == 0)
        {
            return q::max();
        }
    }
    --exp;
    while (exp--)
    {
        ret = ret * f;
    }
    return ret;
}

#endif // QFORMATOPERATIONSEXP_INL
