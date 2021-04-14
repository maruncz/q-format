#include "q-format-ops-root.h"
#include "q-format.h"
#include <bitset>
#include <iostream>

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
void print_q(const std::string &s, const q<T_numBits, T_denBits> &f)
{
    std::cout << s << f.toDouble() << "\t " << f.max().toDouble() << "\t "
              << f.eps().toDouble() << std::endl;
}

int main()
{
    uint8_t exp = 9;
    using q_t = q<1, 7>;
    double d1 = 0.1;
    q_t    f1(d1);
    q_t    f2 = f1.pow(f1, exp);

    double d2 = std::pow(d1, exp);

    print_q("f1: ", f1);
    print_q("f2: ", f2);

    std::cout << "d1: " << d1 << "\nd2: " << d2 << std::endl;

    return 0;
}
