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
    using q_t = q<16,16>;
    printf("%5s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", "exp", "f1", "d1", "f2",
           "d2", "diff", "reldiff");
    for (uint8_t i = 0; i < 15; ++i)
    {
        q_t f1(0.5);
        double d1      = f1.toDouble();
        q_t f2         = f1.pow(f1, i);
        double d2      = std::pow(d1, i);
        double diff    = d2 - f2.toDouble();
        double reldiff = diff / d2;
        printf("%5hhu\t%10f\t%10f\t%10f\t%10f\t%10f\t%10f\n", i, f1.toDouble(),
               d1, f2.toDouble(), d2, diff, reldiff);
    }

    return 0;
}
