#include "q-format.h"
#include <iostream>

int main()
{
    /*q<2, 2> f1;
    q<2, 2> f2(1.5);
    double  d = f2;*/

    /*int32_t tmp = -1024;
    std::cout << (tmp >> 2) << std::endl;
    std::cout << (tmp << 2) << std::endl;*/
    q<2, 2> f1(-exp2(-2));
    q<4, 4> f2(f1);

    std::cout << f1 << std::endl;
    std::cout << f2 << std::endl;

    return 0;
}
