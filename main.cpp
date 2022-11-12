#include "q-format.h"
#include <bitset>
#include <cmath>
#include <iostream>

template<std::uint8_t N, std::uint8_t D>
void print_q(const std::string &s, const q<N, D> &f)
{
    std::cout << s << f.toDouble() << "\t " << f.max().toDouble() << "\t "
              << f.eps().toDouble() << std::endl;
}

int main()
{


    return 0;
}
