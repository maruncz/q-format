#ifndef QFORMATOPERATIONSEXP_INL
#define QFORMATOPERATIONSEXP_INL

#include "q-format-ops-basic.h"
#include "q-format.h"

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::pow(const q &f,
                                                     uint8_t exp) const
{
    q ret{f};
    if constexpr (T_numBits == 1)
    {
        if (exp == 0)
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

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
constexpr q<T_numBits, T_denBits>
q<T_numBits, T_denBits>::exp(const q<T_numBits, T_denBits> &f)
{
    if (f == q(0))
    {
        return q(1);
    }
    if (f == q(1))
    {
        return q(M_E);
    }
    using int_tt = typename q::int_type;
    q ret(f+1);
    q term{f};
    for (int_tt i = 2; i < 100; ++i)
    {
        term *= f/i;
        if (term == q(0))
        {
            break;
        }
        ret += term;
    }

    return ret;
}

#endif // QFORMATOPERATIONSEXP_INL
