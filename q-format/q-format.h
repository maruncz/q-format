#ifndef QFORMAT_H
#define QFORMAT_H

#include "int_types.h"
#include "q-format_operations.inl"
#include <cmath>
#include <cstdint>
#include <limits>

template <std::uint8_t T_numBits, std::uint8_t T_denBits> class q
{
public:
    q() = default;
    q(double f) { n = exp2(T_denBits) * f; }
    q(float f) { n = exp2f(T_denBits) * f; }
    q(long double f) { n = exp2l(T_denBits) * f; }

    template <std::uint8_t O_numBits, std::uint8_t O_denBits>
    explicit q(q<O_numBits, O_denBits> f)
    {
        if constexpr ((T_numBits == O_numBits) && (T_denBits == O_denBits))
        {
            n = f.n;
        }
        else
        {
            constexpr auto shift = O_denBits - T_denBits;
            int_t<std::max(T_numBits, O_numBits) +
                  std::max(T_denBits, O_denBits)>
                tmp = f.n;
            if constexpr (O_denBits > T_denBits)
            {
                n = tmp >> shift;
            }
            else
            {
                n = tmp << -shift;
            }
        }
    }

    double      toDouble() const { return n / exp2(T_denBits); }
    double      toFloat() const { return n / exp2f(T_denBits); }
    long double toLongDouble() const { return n / exp2l(T_denBits); }

    q operator+(const q &f)
    {
        q tmp;
        tmp.n = n + f.n;
        return tmp;
    }

    q operator-(const q &f)
    {
        q tmp;
        tmp.n = n - f.n;
        return tmp;
    }

    q operator*(const q &f)
    {
        if constexpr ((2 * (T_numBits + T_denBits)) <= 64)
        {
            using int_tt = int_t<2 * (T_numBits + T_denBits)>;
            int_tt tmp   = int_tt(n) * int_tt(f.n);
            tmp          = tmp >> T_denBits;
            q ret;
            ret.n = tmp;
            return ret;
        }
        else
        {
            q ret;
            ret.n = qf_mul128<(T_numBits + T_denBits), T_denBits>(n, f.n);
            return ret;
        }
    }

    q operator/(const q &f)
    {
        using int_tt = int_t<T_numBits + 2 * T_denBits>;
        int_tt tmp_n = int_tt(n << T_denBits);
        q      ret;
        ret.n = tmp_n / f.n;
        return ret;
    }

    constexpr static q eps()
    {
        q<T_numBits, T_denBits> tmp;
        tmp.n = 1;
        return tmp;
    }

    constexpr static q max()
    {
        q ret;
        if constexpr ((T_numBits + T_denBits) == 64)
        {
            ret.n = std::numeric_limits<int64_t>::max();
        }
        else
        {
            ret.n = exp2(T_numBits + T_denBits - 1) - 1;
        }
        return ret;
    }

    constexpr static q min()
    {
        q ret;
        ret.n = -exp2(T_numBits + T_denBits - 1);
        return ret;
    }

private:
    int_t<T_numBits + T_denBits> n = 0;

    template <std::uint8_t O_numBits, std::uint8_t O_denBits> friend class q;
};

#endif // QFORMAT_H
