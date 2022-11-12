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
    using q_t = q<4, 4>;
    q_t fa{1.0625};
    q_t fb{0.125};
    q_t fc    = fa / fb;
    double dc = fa.toDouble() / fb.toDouble();

    std::cout << dc << '\t' << fc.toDouble() << '\n';

    return 0;
}
