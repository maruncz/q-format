#ifndef TEST_LIMITS_H
#define TEST_LIMITS_H

#include "q-format.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

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
    EXPECT_NEAR(f.min().toDouble(), calc_min(n, d), exp2(-d));
}

template<uint8_t n, uint8_t d> void check_max()
{
    q<n, d> f;
    EXPECT_NEAR(f.max().toDouble(), calc_max(n, d), exp2(-d));
}

#endif // TEST_LIMITS_H
