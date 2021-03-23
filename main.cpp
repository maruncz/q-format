#include <cmath>
#include <iostream>
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
    q() : n(0), d(std::exp2(T_denBits)), numBits(T_numBits), denBits(T_denBits)

    {
    }

    q(double f) : q() { n = d * f; }

    template <std::uint8_t O_numBits, std::uint8_t O_denBits>
    q(q<O_numBits, O_denBits> f) : q()
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

private:
    int_t<T_numBits + T_denBits> n;
    const uint_t<T_denBits>      d;
    const std::uint8_t           numBits;
    const std::uint8_t           denBits;

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

int main()
{
    /*q<2, 2> f1;
    q<2, 2> f2(1.5);
    double  d = f2;*/

    /*int32_t tmp = -1024;
    std::cout << (tmp >> 2) << std::endl;
    std::cout << (tmp << 2) << std::endl;*/
    q<2, 2> f1(-1.25);
    q<4, 4> f2(f1);

    return 0;
}
