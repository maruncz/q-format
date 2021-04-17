#ifndef QFORMAT_H
#define QFORMAT_H

#include "int_types.h"
#include <cmath>
#include <cstdint>
#include <limits>

template<std::uint8_t T_numBits, std::uint8_t T_denBits> class q
{
    static_assert((T_numBits + T_denBits) <= 32, "moc velke");

public:
    using int_type = int_t<T_numBits + T_denBits>;

    q() = default;
    q(double f) { n = exp2(T_denBits) * f; }
    q(float f) { n = exp2f(T_denBits) * f; }
    q(long double f) { n = exp2l(T_denBits) * f; }
    q(int_type i) { n = i << T_denBits; }

    template<std::uint8_t O_numBits, std::uint8_t O_denBits>
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

    double toDouble() const { return n / exp2(T_denBits); }
    double toFloat() const { return n / exp2f(T_denBits); }
    long double toLongDouble() const { return n / exp2l(T_denBits); }

    q operator+(const q &f);
    q operator-(const q &f);
    q operator*(const q &f);
    q operator/(const q &f);
    q operator/(const int_type &i);

    friend bool operator<(const q &f1, const q &f2) { return f1.n < f2.n; }
    friend bool operator>(const q &f1, const q &f2) { return f1.n > f2.n; }
    friend bool operator<=(const q &f1, const q &f2) { return f1.n <= f2.n; }
    friend bool operator>=(const q &f1, const q &f2) { return f1.n >= f2.n; }
    friend bool operator==(const q &f1, const q &f2) { return f1.n == f2.n; }
    friend bool operator!=(const q &f1, const q &f2) { return f1.n != f2.n; }

    q getInt() const
    {
        q ret(*this);
        auto sign = signum(ret.n);
        ret.n *= sign;
        ret.n &= (~(base() - 1ull));
        ret.n *= sign;
        return ret;
    }

    q getFrac() const
    {
        q ret(*this);
        auto sign = signum(ret.n);
        ret.n *= sign;
        ret.n &= (base() - 1ull);
        ret.n *= sign;
        return ret;
    }

    q max(const q &f1, const q &f2) const { return f1 > f2 ? f1 : f2; }
    q min(const q &f1, const q &f2) const { return f1 < f2 ? f1 : f2; }

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

    constexpr static uint_t<T_denBits + 1> base() { return 1ull << T_denBits; }

    q sqrt() const;

    q pow(const q &f, uint8_t exp) const;

private:
    q root(uint8_t exp) const;

    int_type n = 0;

    template<std::uint8_t O_numBits, std::uint8_t O_denBits> friend class q;
    template<std::uint8_t O_numBits, std::uint8_t O_denBits>
    friend q<O_numBits, O_denBits> abs(const q<O_numBits, O_denBits> &f);
};

#endif // QFORMAT_H
