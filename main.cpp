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
    /*int_t<64> n1 = -8616761059752331528;
    int_t<64> n2 = 2456955197560417229;
    int_t<64> n3 = qf_mul128<64, 63>(n1, n2);

    std::cout << n3 << std::endl;*/

    std::cout << sizeof (double) << " " << sizeof (long double) << std::endl;

    return 0;
}
