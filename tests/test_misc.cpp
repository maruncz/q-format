#include "test_misc.h"
#include <cmath>
#include <iostream>

void assert_near_double(double d1, double d2, double eps,
                        const std::string &msg)
{
    double diff = std::abs(d1 - d2);
    if (diff > eps)
    {
        std::cout << "assert near error:\n"
                  << " in1: " << d1 << " in2: " << d2 << "\ndiff: " << diff
                  << " eps: " << eps << msg << "\n";
    }
}
