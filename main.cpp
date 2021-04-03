#include "q-format.h"
#include <bitset>
#include <iostream>

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
void print_q(const std::string &s, const q<T_numBits, T_denBits> &f)
{
    std::cout << s << f.toDouble() << "\t" << f.max().toDouble() << "\t"
              << f.eps().toDouble() << std::endl;
}

int main()
{

    q<2,6> f1(-1.5);

    print_q("f1:   ",f1);
    print_q("int:  ",f1.getInt());
    print_q("frac: ",f1.getFrac());

    return 0;
}
