#ifndef QFORMAT_H
#define QFORMAT_H

#include "int_types.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>

template<std::uint8_t N, std::uint8_t D> class q
{
    static_assert((N + D) <= 32, "unsupported width");

public:
    using int_type = int_t<N + D>;

    q() = default;
    explicit constexpr q(double f) { n = std::exp2(D) * f; }
    explicit constexpr q(float f) { n = std::exp2f(D) * f; }
    explicit constexpr q(long double f) { n = std::exp2l(D) * f; }
    template<typename T, typename = typename std::enable_if<
                             std::is_integral<T>::value>::type>
    explicit constexpr q(T i)
    {
        n = q::int_type(i) * base();
    }

    constexpr q(const q &f) { n = f.n; }

    template<std::uint8_t N_O, std::uint8_t D_O>
    explicit constexpr q(q<N_O, D_O> f)
    {
        constexpr auto shift                           = D_O - D;
        int_t<std::max(N, N_O) + std::max(D, D_O)> tmp = f.n;
        if (D_O > D)
        {
            n = tmp >> shift;
        }
        else
        {
            n = tmp << -shift;
        }
    }

    constexpr double toDouble() { return double(n) / base(); }
    constexpr double toFloat() const { return n / base(); }
    constexpr long double toLongDouble() const { return n / base(); }

    q &operator=(const q &f)
    {
        n = f.n;
        return *this;
    }

    q operator-() const
    {
        q ret;
        ret.n = -n;
        return ret;
    }
    q operator+(const q &f) const
    {
        q tmp;
        tmp.n = n + f.n;
        return tmp;
    }

    q operator-(const q &f) const
    {
        q tmp;
        tmp.n = n - f.n;
        return tmp;
    }

    q operator*(const q &f) const
    {
        constexpr uint8_t numBits = 2 * (N + D);
        using int_tt              = int_t<numBits>;
        int_tt tmp                = int_tt(n) * int_tt(f.n);
        tmp                       = tmp >> D;
        q ret;
        ret.n = tmp;
        return ret;
    }

    q operator*(const int_type &i) const
    {
        q ret;
        ret.n = n * i;
        return ret;
    }

    q operator/(const q &f) const { return div_std(*this, f); }

    static q div_no_rounding(const q &a, const q &b)
    {
        constexpr uint8_t numBits = 2 * (N + D);
        using int_tt              = int_t<numBits>;
        int_tt tmp_n              = a.n;
        tmp_n                     = tmp_n * exp2_int<int_tt>(D);
        q ret;
        ret.n = tmp_n / b.n;
        return ret;
    }

    static q div_std(const q &a, const q &b)
    {
        using std::abs;
        constexpr uint8_t numBits = 2 * (N + D);
        using int_tt              = int_t<numBits>;
        int_tt tmp_n              = abs(a.n);
        tmp_n                     = tmp_n * exp2_int<int_tt>(D + 1);
        tmp_n /= abs(b.n);
        tmp_n++;
        tmp_n /= 2;
        q ret;
        ret.n = tmp_n;
        if (std::signbit(a.n) ^ std::signbit(b.n))
        {
            ret = -ret;
        }
        return ret;
    }

    q operator/(const int_type &i) const
    {
        q ret;
        ret.n = n / i;
        return ret;
    }

    q operator+=(const q &f)
    {
        *this = *this + f;
        return *this;
    }

    q operator-=(const q &f)
    {
        *this = *this - f;
        return *this;
    }

    q operator*=(const q &f)
    {
        *this = *this * f;
        return *this;
    }

    q operator/=(const q &f)
    {
        *this = *this / f;
        return *this;
    }

    q operator/=(const int_type &i)
    {
        *this = *this / i;
        return *this;
    }

    friend bool operator<(const q &f1, const q &f2) { return f1.n < f2.n; }

    friend bool operator>(const q &f1, const q &f2) { return f1.n > f2.n; }

    friend bool operator<=(const q &f1, const q &f2) { return f1.n <= f2.n; }

    friend bool operator>=(const q &f1, const q &f2) { return f1.n >= f2.n; }

    friend bool operator==(const q &f1, const q &f2) { return f1.n == f2.n; }

    friend bool operator!=(const q &f1, const q &f2) { return f1.n != f2.n; }

    constexpr static q max(const q &f1, const q &f2)
    {
        return f1 > f2 ? f1 : f2;
    }
    constexpr static q min(const q &f1, const q &f2)
    {
        return f1 < f2 ? f1 : f2;
    }

    constexpr static q eps()
    {
        q tmp;
        tmp.n = 1;
        return tmp;
    }

    template<typename T>
    static constexpr
        typename std::enable_if<std::is_integral<T>::value, q<N, D>>::type
        exp2(T e)
    {
        q ret{1.0f};
        if (e > 0)
        {
            ret.n <<= e;
        }
        else if (e < 0)
        {
            ret.n >>= e;
        }
        return ret;
    }

    static constexpr q exp(const q &f) { return exp_impl(f); }

    constexpr static q max()
    {
        q ret;
        ret.n = exp2_int<int_t<N + D + 1>>(N + D - 1) - 1;
        return ret;
    }

    constexpr static q min()
    {
        q ret;
        ret.n = -exp2_int<int_t<N + D + 1>>(N + D - 1);
        return ret;
    }

    constexpr static q abs(const q &f)
    {
        q ret = f;
        if (ret.n < 0)
        {
            ret = -ret;
        }
        return ret;
    }

    constexpr static uint_t<D + 1> base() { return exp2_int<uint_t<D + 1>>(D); }

private:
    constexpr static q exp_impl(const q &f)
    {
        if (f == q(0))
        {
            return q(1);
        }
        if (f == q(1))
        {
            return q(M_E);
        }
        q ret(f + q(1));
        q term{f};
        for (uint8_t i = 2; i < 100; ++i)
        {
            term *= f / i;
            if (term == q(0))
            {
                break;
            }
            ret += term;
        }
        return ret;
    }

    template<typename T=q> constexpr static T exp2_int(int8_t e)
    {
        T ret{1};
        if (e > 0)
        {
            ret <<= e;
        }
        else if (e < 0)
        {
            ret >>= e;
        }
        return ret;
    }

    int_type n = 0;
};

#endif // QFORMAT_H
