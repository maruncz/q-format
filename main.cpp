#include "q-format.h"
#include <iostream>

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
void print_q(const std::string &s, const q<T_numBits, T_denBits> &f)
{
    std::cout << s << f.toDouble() << "\t" << f.max().toDouble() << "\t"
              << f.eps().toDouble() << std::endl;
}

int main()
{
    q<1, 7> f1 = q<1, 7>::min() + q<1, 7>::eps(); //-127
    q<1, 7> f2 = q<1, 7>::max();                  // 127
    q<1, 7> f3 = q<1, 7>::min() + q<1, 7>::eps(); //-127
    // double  d1 = 0.015625;
    // double  d2 = 0.9921875;
    // double  d3 = 1.0078125;

    print_q("f1:  ", f1);
    std::cout << "f1d: " << f1.toDouble() << '\n';

    print_q("f2:  ", f2);
    std::cout << "f2d: " << f2.toDouble() << '\n';

    print_q("f3:  ", f3);
    std::cout << "f3d: " << f3.toDouble() << '\n';

    f3 = f1 + f2;

    print_q("f3:  ", f3);
    std::cout << "f3d: " << f3.toDouble() << '\n';

    return 0;
}
