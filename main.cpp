#include "q-format.h"
#include <bitset>
#include <iostream>

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
void print_q(const std::string &s, const q<T_numBits, T_denBits> &f)
{
    std::cout << s << f.toDouble() << "\t" << f.max().toDouble() << "\t"
              << f.eps().toDouble() << std::endl;
}

int main()
{
    auto     ret = qf_div128<32>(-89, 5);
    int_t<8> i3  = ret.first;

    std::cout << +i3 << std::endl;


    return 0;
}
