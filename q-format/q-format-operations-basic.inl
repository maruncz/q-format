#ifndef QFORMATOPERATIONSBASIC_INL
#define QFORMATOPERATIONSBASIC_INL

#include "q-format.h"

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::operator+(const q &f)
{
    q tmp;
    tmp.n = n + f.n;
    return tmp;
}

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::operator-(const q &f)
{
    q tmp;
    tmp.n = n - f.n;
    return tmp;
}

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::operator*(const q &f)
{
    constexpr uint8_t numBits = 2 * (T_numBits + T_denBits);
    using int_tt              = int_t<numBits>;
    int_tt tmp                = int_tt(n) * int_tt(f.n);
    tmp                       = tmp >> T_denBits;
    q ret;
    ret.n = tmp;
    return ret;
}

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::operator/(const q &f)
{
    constexpr uint8_t numBits = 2 * (T_numBits + T_denBits);
    using int_tt              = int_t<numBits>;
    int_tt tmp_n              = n;
    tmp_n                     = tmp_n << T_denBits;
    q ret;
    ret.n = tmp_n / f.n;
    return ret;
}

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
q<T_numBits, T_denBits> q<T_numBits, T_denBits>::operator/(const int_tt &i)
{
    q ret;
    ret.n = n / i;
    return ret;
}

#endif // QFORMATOPERATIONSBASIC_INL
