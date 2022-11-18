#ifndef Q_IMPL_HPP
#define Q_IMPL_HPP

#include "int_types.h"
#include <algorithm>
#include <cmath>

namespace qfm
{

template<int N, int D> class q_base
{
    static_assert((N + D) <= 64, "unsupported width");
    static_assert(N >= 1, "not enough integer bits");
    static_assert(D >= 1, "not enough fractional bits");

    template<int, int> friend class q_base;

public:
    using int_type = int_t<N + D>;

    q_base() = default;
    explicit constexpr q_base(double f) { n = base() * f; }
    explicit constexpr q_base(float f) { n = base() * f; }
    explicit constexpr q_base(long double f) { n = base() * f; }
    template<typename T, typename = typename std::enable_if<
                             std::is_integral<T>::value>::type>
    explicit constexpr q_base(T i)
    {
        n = q_base::int_type(i) * base();
    }

    constexpr q_base(const q_base &f) { n = f.n; }

    template<int N_O, int D_O> explicit constexpr q_base(q_base<N_O, D_O> f)
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

    constexpr double toDouble() { return static_cast<double>(n) / base(); }
    constexpr double toFloat() const { return static_cast<float>(n) / base(); }
    constexpr long double toLongDouble() const
    {
        return static_cast<long double>(n) / base();
    }

    q_base &operator=(const q_base &f)
    {
        n = f.n;
        return *this;
    }

    q_base operator-() const
    {
        q_base ret;
        ret.n = -n;
        return ret;
    }
    q_base operator+(const q_base &f) const
    {
        q_base tmp;
        tmp.n = n + f.n;
        return tmp;
    }

    q_base operator-(const q_base &f) const
    {
        q_base tmp;
        tmp.n = n - f.n;
        return tmp;
    }

    q_base operator*(const q_base &f) const { return mul_std(*this, f); }

    static q_base mul_std(const q_base &a, const q_base &b)
    {
        constexpr uint8_t numBits = 2 * (N + D);
        using int_tt              = int_t<numBits>;
        using std::abs;
        int_tt tmp = abs(int_tt(a.n) * int_tt(b.n));
        tmp        = tmp >> (D - 1);
        tmp++;
        tmp /= 2;
        q_base ret;
        ret.n = tmp;
        if (std::signbit(a.n) ^ std::signbit(b.n))
        {
            ret = -ret;
        }
        return ret;
    }

    static q_base mul_no_rounding(const q_base &a, const q_base &b)
    {
        constexpr uint8_t numBits = 2 * (N + D);
        using int_tt              = int_t<numBits>;
        int_tt tmp                = int_tt(a.n) * int_tt(b.n);
        tmp                       = tmp >> D;
        q_base ret;
        ret.n = tmp;
        return ret;
    }

    q_base operator*(const int_type &i) const
    {
        q_base ret;
        ret.n = n * i;
        return ret;
    }

    q_base operator/(const q_base &f) const { return div_std(*this, f); }

    static q_base div_std(const q_base &a, const q_base &b)
    {
        using std::abs;
        constexpr uint8_t numBits = 2 * (N + D);
        using int_tt              = int_t<numBits>;
        int_tt tmp_n              = abs(a.n);
        tmp_n                     = tmp_n * exp2_int<int_tt>(D + 1);
        tmp_n /= abs(b.n);
        tmp_n++;
        tmp_n /= 2;
        q_base ret;
        ret.n = tmp_n;
        if (std::signbit(a.n) ^ std::signbit(b.n))
        {
            ret = -ret;
        }
        return ret;
    }

    q_base operator/(const int_type &i) const
    {
        q_base ret;
        ret.n = n / i;
        return ret;
    }

    q_base operator+=(const q_base &f)
    {
        *this = *this + f;
        return *this;
    }

    q_base operator-=(const q_base &f)
    {
        *this = *this - f;
        return *this;
    }

    q_base operator*=(const q_base &f)
    {
        *this = *this * f;
        return *this;
    }

    q_base operator*=(const int_type &i)
    {
        *this = *this * i;
        return *this;
    }

    q_base operator/=(const q_base &f)
    {
        *this = *this / f;
        return *this;
    }

    q_base operator/=(const int_type &i)
    {
        *this = *this / i;
        return *this;
    }

    friend bool operator<(const q_base &f1, const q_base &f2)
    {
        return f1.n < f2.n;
    }

    friend bool operator>(const q_base &f1, const q_base &f2)
    {
        return f1.n > f2.n;
    }

    friend bool operator<=(const q_base &f1, const q_base &f2)
    {
        return f1.n <= f2.n;
    }

    friend bool operator>=(const q_base &f1, const q_base &f2)
    {
        return f1.n >= f2.n;
    }

    friend bool operator==(const q_base &f1, const q_base &f2)
    {
        return f1.n == f2.n;
    }

    friend bool operator!=(const q_base &f1, const q_base &f2)
    {
        return f1.n != f2.n;
    }

    constexpr static q_base max(const q_base &f1, const q_base &f2)
    {
        return f1 > f2 ? f1 : f2;
    }
    constexpr static q_base min(const q_base &f1, const q_base &f2)
    {
        return f1 < f2 ? f1 : f2;
    }

    constexpr static q_base eps()
    {
        q_base tmp;
        tmp.n = 1;
        return tmp;
    }

    template<typename T>
    static constexpr
        typename std::enable_if<std::is_integral<T>::value, q_base>::type
        exp2(T e)
    {
        q_base ret{1};
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

    template<typename T = q_base>
    static constexpr typename std::enable_if<(N > 1), T>::type
    exp(const q_base &f)
    {
        if (f == q_base(0))
        {
            return q_base(1);
        }
        if (f == q_base(1))
        {
            return q_base(M_E);
        }
        return exp_impl(f);
    }

    template<typename T = q_base>
    static constexpr typename std::enable_if<(N <= 1), T>::type
    exp(const q_base &f)
    {
        return exp_impl(f);
    }

    constexpr static q_base max()
    {
        q_base ret;
        ret.n = exp2_int<int_t<N + D + 1>>(N + D - 1) - 1;
        return ret;
    }

    constexpr static q_base min()
    {
        q_base ret;
        ret.n = -exp2_int<int_t<N + D + 1>>(N + D - 1);
        return ret;
    }

    constexpr static q_base abs(const q_base &f)
    {
        q_base ret = f;
        if (ret.n < 0)
        {
            ret = -ret;
        }
        return ret;
    }

    constexpr static uint_t<D + 1> base() { return exp2_int<uint_t<D + 1>>(D); }

private:
    constexpr static q_base exp_impl(const q_base &f)
    {
        q_base ret(f + q_base(1));
        q_base term{f};
        for (uint8_t i = 2; i < 100; ++i)
        {
            term *= f / i;
            if (term == q_base(0))
            {
                break;
            }
            ret += term;
        }
        return ret;
    }

    constexpr static q_base exp_impl_less_than_one(const q_base &f)
    {
        using q_tmp = q_base<std::max(N, 2), D>;
        const q_tmp exp{f};
        q_tmp ret(exp + q_tmp(1));
        q_tmp term{exp};
        for (uint8_t i = 2; i < 100; ++i)
        {
            term *= exp / i;
            if (term == q_tmp(0))
            {
                break;
            }
            ret += term;
        }
        return q_base(ret);
    }

    template<typename T>
    constexpr static
        typename std::enable_if<std::is_integral<T>::value, T>::type
        exp2_int(int8_t e)
    {
        T ret{1};
        if (e > 0)
        {
            ret <<= e;
        }
        else if (e < 0)
        {
            ret >>= -e;
        }
        return ret;
    }

    int_type n = 0;
};

} // namespace qfm

#endif // Q_IMPL_HPP
