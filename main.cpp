#include "q-format.h"
#include <iostream>

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
void print_q(const std::string &s, const q<T_numBits, T_denBits> &f)
{
    std::cout << s << f.toDouble() << "\t" << f.max().toDouble() << "\t"
              << f.eps().toDouble() << std::endl;
}

/**
 * @todo a musi byt unsigned
 */
void pair_shift(uint16_t &a, uint16_t &b, uint8_t len)
{
    a *= 2;
    if (b & (1 << len))
    {
        a += 1;
    }
    b *= 2;
    b = b & (1 << len);
}

uint8_t q_len(uint16_t q)
{
    return floor(log2(q));
}

int main()
{
    /*int_t<64> n1 = -8616761059752331528;
    int_t<64> n2 = 2456955197560417229;
    int_t<64> n3 = qf_mul128<64, 63>(n1, n2);

    std::cout << n3 << std::endl;*/

    // std::cout << sizeof (double) << " " << sizeof (long double) << std::endl;

    // https://stackoverflow.com/questions/12133810/non-restoring-division-algorithm

    // q/m = q,a

    uint16_t  a   = 0;
    uint16_t m   = 2;
    uint16_t q   = 128;
    uint8_t  len = q_len(q);
    uint8_t  i   = len;
    do {
        if (a & (1 << 16))
        {
            pair_shift(a, q, len);
            a += m;
        }
        else
        {
            pair_shift(a, q, len);
            a -= m;
        }
        if (!(a & (1 << 16)))
        {
            q += 1;
        }
        --i;
    } while (i > 0);

    /*if (a < 0)
    {
        a += m;
        --q;
    }*/

    std::cout << q << " " << a << std::endl;

    return 0;
}
