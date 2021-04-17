#ifndef TEST_MISC_H
#define TEST_MISC_H

#include <array>
#include <cmath>
#include <cstdio>

void send_msg(const char *s);
void test_start(const char *s);
void test_done(const char *s);

template<typename T> void assert_near(T d1, T d2, T eps, const char *msg)
{
    T diff = std::abs(d1 - d2);
    if (diff > eps)
    {
        std::array<char, 500> s{};
        snprintf(
            s.begin(), 500,
            "assert near error:\nin1: %5f in2: %5f\ndiff: %5f eps: %5f\n%s\n",
            d1, d2, diff, eps, msg);
        send_msg(s.begin());
    }
}

#endif // TEST_MISC_H
