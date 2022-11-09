#ifndef QFORMAT_H
#define QFORMAT_H

#include "int_types.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>

template<std::uint8_t T_numBits, std::uint8_t T_denBits> class q
{
    static_assert((T_numBits + T_denBits) <= 32, "moc velke");

public:
    using int_type = int_t<T_numBits + T_denBits>;

    q() = default;
    explicit q(double f) { n = std::exp2(T_denBits) * f; }
    explicit q(float f) { n = std::exp2f(T_denBits) * f; }
    explicit q(long double f) { n = std::exp2l(T_denBits) * f; }
    template<typename T, typename = typename std::enable_if<
                             std::is_integral<T>::value>::type>
    q(T i)
    {
        n = i << T_denBits;
    }

    q(const q &f) { n = f.n; }

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

    explicit operator double() const { return this->toDouble(); }
    explicit operator float() const { return this->toFloat(); }
    explicit operator long double() const { return this->toLongDouble(); }

    double toDouble() const { return n / std::exp2(T_denBits); }
    double toFloat() const { return n / std::exp2f(T_denBits); }
    long double toLongDouble() const { return n / std::exp2l(T_denBits); }

    q &operator=(const q &f)
    {
        n = f.n;
        return *this;
    }
    q &operator=(double d)
    {
        *this = q(d);
        return *this;
    }
    q &operator=(float d)
    {
        *this = q(d);
        return *this;
    }
    q &operator=(long double d)
    {
        *this = q(d);
        return *this;
    }
    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, q>::value operator=(T i)
    {
        *this = q(i);
        return *this;
    }

    q operator-()
    {
        q ret;
        ret.n = -n;
        return ret;
    }
    q operator+(const q &f) const;
    q operator-(const q &f);
    q operator*(const q &f);
    q operator*(const int_type &i);
    q operator/(const q &f);
    q operator/(const int_type &i) const;

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
        q<T_numBits, T_denBits> tmp;
        tmp.n = 1;
        return tmp;
    }

    constexpr static q max()
    {
        q ret;
        ret.n = std::exp2(T_numBits + T_denBits - 1) - 1;
        return ret;
    }

    constexpr static q min()
    {
        q ret;
        ret.n = -std::exp2(T_numBits + T_denBits - 1);
        return ret;
    }

    q sqrt() const;

    q pow(const q &f, uint8_t exp) const;

    template<typename T>
    static constexpr typename std::enable_if<std::is_integral<T>::value,
                                             q<T_numBits, T_denBits>>::value
    exp2(T e)
    {
        q ret{1.0f};
        if (e > 0)
        {
            ret.n << e;
        }
        else if (e < 0)
        {
            ret.n >> e;
        }
        return ret;
    }

    static constexpr q exp(const q &f);

private:
    constexpr static uint_t<T_denBits + 1> base() { return 1ull << T_denBits; }
    q root(uint8_t exp) const;

    int_type n = 0;

    template<std::uint8_t O_numBits, std::uint8_t O_denBits> friend class q;
    template<std::uint8_t O_numBits, std::uint8_t O_denBits>
    friend q<O_numBits, O_denBits> abs(const q<O_numBits, O_denBits> &f);
};

#endif // QFORMAT_H