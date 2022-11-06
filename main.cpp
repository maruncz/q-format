#include "q-format-ops-exp.h"
#include "q-format.h"
#include <bitset>
#include <cmath>
#include <iostream>

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
void print_q(const std::string &s, const q<T_numBits, T_denBits> &f)
{
    std::cout << s << f.toDouble() << "\t " << f.max().toDouble() << "\t "
              << f.eps().toDouble() << std::endl;
}

int main()
{
    using q_t = q<1,7>;
    q_t f1{0.827181};
    double d1 = f1.toDouble();
    auto f2 = f1;
    auto d2 = d1;
    int it = 1;
    while (true)
    {
        f2 = f2 * f1;
        d2 *= d1;
        ++it;
        auto diff = std::abs(d2 - f2.toDouble());
        std::cout << it << '\t' << f2.toDouble() << '\t' << d2 << '\t' << diff
                  << "\t\t" << q_t::eps().toDouble() << std::endl;
        if (diff > q_t::eps().toDouble())
        {
            break;
        }
    }

    return 0;
}
