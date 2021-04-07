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

    q<3,29> f1(2.0);

    q<3,29> f2 = f1.sqrt();

    print_q("f1: ",f1);
    print_q("f2: ",f2);

    return 0;
}
