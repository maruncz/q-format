#include "test_misc.h"
#include <cmath>
#include <iostream>
#include <sstream>

void assert_near_double(double d1, double d2, double eps,
                        const std::string &msg)
{
    double diff = std::abs(d1 - d2);
    if (diff > eps)
    {
        std::stringstream s;
        s << "assert near error:\n"
                  << " in1: " << d1 << " in2: " << d2 << "\ndiff: " << diff
                  << " eps: " << eps << msg << "\n";
        send_msg(s.str());
    }
}

void send_msg(const std::string &s)
{
    std::cout << s;
}

void test_start(const char *s)
{
    std::stringstream ss;
    ss << s << " start\n";
    send_msg(ss.str());
}

void test_done(const char *s)
{
    std::stringstream ss;
    ss << s << " done\n";
    send_msg(ss.str());
}
