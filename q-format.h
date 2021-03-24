#ifndef QFORMAT_H
#define QFORMAT_H

#include <cmath>
#include <cstdint>
#include <limits>

// https://peter.bloomfield.online/using-cpp-templates-for-size-based-type-selection/

// clang-format off
template <std::uint8_t T_numBits>
using uint_t = typename std::enable_if<T_numBits <=64,
    typename std::conditional<T_numBits <= 8, std::uint8_t,
        typename std::conditional<T_numBits <= 16, std::uint16_t,
            typename std::conditional<T_numBits <= 32, std::uint32_t,
                std::uint64_t
                >::type
            >::type
        >::type>::type;
// clang-format on

// clang-format off
template <std::uint8_t T_numBits>
using int_t = typename std::enable_if<T_numBits <=64,
    typename std::conditional<T_numBits <= 8, std::int8_t,
        typename std::conditional<T_numBits <= 16, std::int16_t,
            typename std::conditional<T_numBits <= 32, std::int32_t,
                std::int64_t
                >::type
            >::type
        >::type>::type;
// clang-format on

template <std::uint8_t T_numBits, std::uint8_t T_denBits> class q
{
public:
    q() = default;
    q(double f) { n = d * f; }

    template <std::uint8_t O_numBits, std::uint8_t O_denBits>
    q(q<O_numBits, O_denBits> f)
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

    operator double() const { return n / double(d); }
    // q operator+(const q &f) {}

    constexpr static double eps()
    {
        return exp2(-T_denBits);
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
    int_t<T_numBits + T_denBits>           n       = 0;
    constexpr static uint_t<T_denBits + 1> d       = exp2(T_denBits);
    constexpr static std::uint8_t          numBits = T_numBits;
    constexpr static std::uint8_t          denBits = T_denBits;

    template <std::uint8_t O_numBits, std::uint8_t O_denBits> friend class q;

    /*template <std::uint8_t A_numBits, std::uint8_t A_denBits,
              std::uint8_t B_numBits, std::uint8_t B_denBits>
    friend q<A_numBits + B_numBits, A_denBits + B_denBits>
    operator*(q<A_numBits, A_denBits> f1, q<B_numBits, B_denBits> f2);*/
};

/*template <std::uint8_t A_numBits, std::uint8_t A_denBits,
          std::uint8_t B_numBits, std::uint8_t B_denBits>
q<A_numBits + B_numBits, A_denBits + B_denBits>
operator*(q<A_numBits, A_denBits> f1, q<B_numBits, B_denBits> f2)
{
}*/

#endif // QFORMAT_H
