#include "q-format.h"
#include <iostream>

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
void print_q(const std::string &s, const q<T_numBits, T_denBits> &f)
{
    std::cout << s << f.toDouble() << "\t" << f.max().toDouble() << "\t"
              << f.eps().toDouble() << std::endl;
}

int main()
{
    int_t<16> n1 = 32767;
    int_t<16> n2 = 32767;
    int_t<16> n3 = qf_mul128<16, 15>(n1, n2);

    std::cout << n3 << std::endl;

    return 0;
}
