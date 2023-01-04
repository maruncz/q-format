#ifndef Q_IMPL_HPP
#define Q_IMPL_HPP

#include "int_types.h"
#include <algorithm>
#include <cmath>

namespace qfm
{

template<int I, int F> class q_base
{
    static_assert((I + F) <= 64, "unsupported width");
    static_assert(I >= 1, "not enough integer bits");
    static_assert(F >= 1, "not enough fractional bits");

    template<int, int> friend class q_base;

public:
    using int_type = int_t<I + F>;

    q_base() = default;

    template<typename T,
             std::enable_if_t<std::is_floating_point<T>::value> * = nullptr>
    explicit constexpr q_base(T f)
    {
        using int_tt = int_t<1 + I + F>;
        int_tt tmp   = base() * f * 2.0;
        if (f > 0)
        {
            tmp++;
        }
        else
        {
            tmp--;
        }
        tmp /= 2;
        n = tmp;
    }

    template<typename T,
             std::enable_if_t<std::is_integral<T>::value> * = nullptr>
    explicit constexpr q_base(T i)
    {
        n = q_base::int_type(i) * base();
    }

    constexpr q_base(const q_base &f) { n = f.n; }

    template<int I_O, int F_O, std::enable_if_t<(F_O <= F)> * = nullptr>
    explicit constexpr q_base(q_base<I_O, F_O> f)
    {
        constexpr auto shift                           = F - F_O;
        int_t<std::max(I, I_O) + std::max(F, F_O)> tmp = f.n;
        n                                              = tmp << shift;
    }

    template<int I_O, int F_O, std::enable_if_t<(F_O > F)> * = nullptr>
    explicit constexpr q_base(q_base<I_O, F_O> f)
    {
        constexpr auto shift = F_O - F;
        using std::abs;
        int_t<std::max(I, I_O) + F_O> tmp = f.n;
        tmp                               = abs(tmp);
        tmp += 1l << (shift - 1);
        tmp >>= shift;
        n = tmp;
        if (f.n < 0)
        {
            n = -n;
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
        constexpr uint8_t numBits = 2 * (I + F);
        using int_tt              = int_t<numBits>;
        using std::abs;
        int_tt tmp = abs(int_tt(a.n) * int_tt(b.n));
        tmp        = tmp >> (F - 1);
        tmp++;
        tmp /= 2;
        if (std::signbit(a.n) ^ std::signbit(b.n))
        {
            tmp = -tmp;
        }
        q_base ret;
        ret.n = tmp;
        return ret;
    }

    static q_base mul_no_rounding(const q_base &a, const q_base &b)
    {
        constexpr uint8_t numBits = 2 * (I + F);
        using int_tt              = int_t<numBits>;
        int_tt tmp                = int_tt(a.n) * int_tt(b.n);
        tmp                       = tmp >> F;
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
        constexpr uint8_t numBits = 2 * (I + F);
        using int_tt              = int_t<numBits>;
        int_tt tmp_n              = abs(int_tt(a.n));
        tmp_n                     = tmp_n * exp2_int<int_tt>(F + 1);
        tmp_n /= abs(int_tt(b.n));
        tmp_n++;
        tmp_n /= 2;
        if (std::signbit(a.n) ^ std::signbit(b.n))
        {
            tmp_n = -tmp_n;
        }
        q_base ret;
        ret.n = tmp_n;
        return ret;
    }

    q_base operator/(const int_type &i) const { return div_int_std(*this, i); }

    static q_base div_int_no_rounding(const q_base &a, const int_type &i)
    {
        q_base ret;
        ret.n = a.n / i;
        return ret;
    }

    static q_base div_int_std(const q_base &a, const int_type &i)
    {
        using std::abs;
        using int_tt = int_t<1 + I + F>;
        int_tt tmp   = abs(int_tt(a.n));
        tmp *= 2;
        tmp /= abs(int_tt(i));
        tmp++;
        tmp /= 2;
        q_base ret;
        ret.n = tmp;
        if (std::signbit(a.n) ^ std::signbit(i))
        {
            ret = -ret;
        }
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
    static constexpr typename std::enable_if<(I >= 3), T>::type
    exp(const q_base &f)
    {
        if (f == q_base(0))
        {
            return q_base(1);
        }
        if (f == q_base(1))
        {
            return q_base(2.718281828);
        }
        return exp_impl(f);
    }

    template<typename T = q_base>
    static constexpr typename std::enable_if<(I < 3), T>::type
    exp(const q_base &f)
    {
        return exp_impl_less_than_one_two_step(f);
    }

    constexpr static q_base max()
    {
        q_base ret;
        ret.n = exp2_int<int_t<I + F + 1>>(I + F - 1) - 1;
        return ret;
    }

    constexpr static q_base min()
    {
        q_base ret;
        ret.n = -exp2_int<int_t<I + F + 1>>(I + F - 1);
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

    constexpr static uint_t<F + 1> base() { return exp2_int<uint_t<F + 1>>(F); }

protected:
    template<int N_A, int D_A, int N_B, int D_B>
    static constexpr q_base<N_A + N_B, D_A + D_B> mul(q_base<N_A, D_A> a,
                                                      q_base<N_B, D_B> b)
    {
        q_base<N_A + N_B, D_A + D_B> ret;
        ret.n = a.n;
        ret.n *= b.n;
        return ret;
    }

    template<int N_A, int D_A, int N_B, int D_B>
    static constexpr q_base<N_A + D_B, D_A + N_B> div(q_base<N_A, D_A> a,
                                                      q_base<N_B, D_B> b)
    {
        using int_tt = int_t<N_A + D_B + D_A + N_B>;
        int_tt tmp   = a.n;
        tmp *= exp2_int<int_tt>(D_A + D_B);
        tmp /= b.n;
        q_base<N_A + D_B, D_A + N_B> ret;
        ret.n = tmp;
        return ret;
    }

private:
    constexpr static q_base exp_impl(const q_base &f)
    {
        q_base ret(f + q_base(1));
        q_base term{f};
        for (uint8_t i = 2; i < 100; ++i)
        {
            q_base tmp = f / i;
            term *= tmp;
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
        using q_tmp = q_base<std::max(I, 3), F - std::max(0, 3 - I)>;
        const q_tmp exp{f};
        q_tmp tmpret(exp + q_tmp(1));
        q_tmp tmpterm{exp};
        for (uint8_t i = 2; i < 100; ++i)
        {
            auto tmp = exp / i;
            tmpterm *= tmp;
            tmpret += tmpterm;
            if (tmpterm == q_tmp(0))
            {
                ++i;
                break;
            }
        }
        return q_base(tmpret);
    }

    constexpr static q_base exp_impl_less_than_one_two_step(const q_base &f)
    {
        using std::abs;
        q_base ret{0};
        q_base term{0};
        uint8_t i = 2;
        {
            using q_tmp = q_base<std::max(I, 3), F - std::max(0, 3 - I)>;
            const q_tmp exp{f};
            q_tmp tmpret(exp + q_tmp(1));
            q_tmp tmpterm{exp};
            for (; i < 100; ++i)
            {
                auto tmp = exp / i;
                tmpterm *= tmp;
                tmpret += tmpterm;
                if (q_tmp::abs(tmpret) < q_tmp(1))
                {
                    ++i;
                    break;
                }
            }
            ret  = q_base(tmpret);
            term = q_base(tmpterm);
        }

        {
            for (; i < 100; ++i)
            {
                auto tmp = f / i;
                term *= tmp;
                if (term == q_base(0))
                {
                    break;
                }
                ret += term;
            }
        }

        return ret;
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
