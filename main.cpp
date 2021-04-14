#include "q-format-ops-root.h"
#include "q-format.h"
#include <bitset>
#include <iostream>

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
void print_q(const std::string &s, const q<T_numBits, T_denBits> &f)
{
    std::cout << s << f.toDouble() << "\t " << f.max().toDouble() << "\t "
              << f.eps().toDouble() << std::endl;
}

int main()
{
    using q_t = q<1, 7>;
    for (int i = 1; i < 15; ++i)
    {
        q_t f1(0.515625);
        double d1 = f1.toDouble();
        q_t f2    = f1.pow(f1, i);
        double d2 = std::pow(d1, i);
        std::cout << i << "\t" << f1.toDouble() << "\t" << d1 << "\t"
                  << f2.toDouble() << "\t" << d2 << std::endl;
    }

    return 0;
}
