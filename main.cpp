#include "q-format.h"
#include <bitset>
#include <iostream>

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
void print_q(const std::string &s, const q<T_numBits, T_denBits> &f)
{
    std::cout << s << f.toDouble() << "\t" << f.max().toDouble() << "\t"
              << f.eps().toDouble() << std::endl;
}

void pair_shift(uint16_t &a, uint16_t &b, uint8_t len)
{
    a *= 2;
    if (b & (1 << len))
    {
        a += 1;
    }
    b *= 2;
    b = b & ((1 << (len + 1)) - 1);
}

uint8_t q_len(uint16_t q)
{
    return floor(log2(q));
}

union tmpA
{
    uint16_t u;
    int16_t  i;
};

int main()
{
    /*int_t<64> n1 = -8616761059752331528;
    int_t<64> n2 = 2456955197560417229;
    int_t<64> n3 = qf_mul128<64, 63>(n1, n2);

    std::cout << n3 << std::endl;*/

    // std::cout << sizeof (double) << " " << sizeof (long double) << std::endl;

    // https://stackoverflow.com/questions/12133810/non-restoring-division-algorithm

    // q/m = q,a

    tmpA a;
    a.u          = 0;
    uint16_t m   = 2;
    uint16_t q   = 127;
    uint8_t  len = q_len(q);
    int8_t   i   = len + 1;
    do {
        pair_shift(a.u, q, len);
        if (a.i < 0)
        {
            a.i += m;
        }
        else
        {
            a.i -= m;
        }
        if (a.i > 0)
        {
            q += 1;
        }
        --i;
    } while (i > 0);

    if (a.i < 0)
    {
        a.i += m;
        //--q;
    }

    std::cout << q << " " << a.i << std::endl;

    return 0;
}
