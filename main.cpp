#include <iostream>
#include "q-format.h"


int main()
{
    /*q<2, 2> f1;
    q<2, 2> f2(1.5);
    double  d = f2;*/

    /*int32_t tmp = -1024;
    std::cout << (tmp >> 2) << std::endl;
    std::cout << (tmp << 2) << std::endl;*/
    q<2, 2> f1(-1.25);
    q<4, 4> f2(f1);

    std::cout << f1.eps() << std::endl;
    std::cout << f2.eps() << std::endl;

    return 0;
}
