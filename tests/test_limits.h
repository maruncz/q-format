#ifndef TEST_LIMITS_H
#define TEST_LIMITS_H

#include "q-format.h"
#include "test_misc.h"

inline double calc_max(uint8_t numBits, uint8_t denBits)
{
    return (exp2(numBits + denBits - 1) - 1) / exp2(denBits);
}

inline double calc_min(uint8_t numBits, uint8_t denBits)
{
    return -exp2(numBits + denBits - 1) / exp2(denBits);
}

template<uint8_t n, uint8_t d> void check_min()
{
    q<n, d> f;
    assert_near_double(f.min().toDouble(), calc_min(n, d), exp2(-d), "");
}

template<uint8_t n, uint8_t d> void check_max()
{
    q<n, d> f;
    assert_near_double(f.max().toDouble(), calc_max(n, d), exp2(-d), "");
}

void test_limits_max8();
void test_limits_max16();
void test_limits_max32();

void test_limits_min8();
void test_limits_min16();
void test_limits_min32();

#endif // TEST_LIMITS_H
