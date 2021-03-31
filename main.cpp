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

int main()
{
    q<1, 7> f1(0.3515625);
    q<1, 7> f2(0.03125);
    q<1, 7> f3 = f1 / f2;
    double  d1 = f1.toDouble();
    double  d2 = f2.toDouble();
    double  d3 = d1 / d2;

    print_q("f3: ", f3);
    std::cout << d3 << std::endl;

    return 0;
}
