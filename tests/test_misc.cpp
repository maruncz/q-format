#include "test_misc.h"
#include <cmath>
#ifndef LIBOPENCM3
#    include <iostream>
#endif
#include <cstdio>

void assert_near_double(double d1, double d2, double eps, const char *msg)
{
    double diff = std::abs(d1 - d2);
    if (diff > eps)
    {
        char s[500];
        snprintf(
            s, 500,
            "assert near error:\nin1: %5f in2: %5f\ndiff: %5f eps: %5f\n%s\n",
            d1, d2, diff, eps, msg);
        send_msg(s);
    }
}

void send_msg(const char *s)
{
#ifndef LIBOPENCM3
    std::cout << s;
#else

#endif
}

void test_start(const char *s)
{
    char ss[200];
    snprintf(ss,200,"%s start\n",s);
    send_msg(ss);
}

void test_done(const char *s)
{
    char ss[200];
    snprintf(ss,200,"%s done\n",s);
    send_msg(ss);
}
