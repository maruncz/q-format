#ifndef TEST_LIMITS_H
#define TEST_LIMITS_H

#include "../q-format.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

inline double calc_max(uint8_t numBits, uint8_t denBits)
{
    return (exp2(numBits + denBits - 1) - 1) / exp2(denBits);
}

inline double calc_min(uint8_t numBits, uint8_t denBits)
{
    return -exp2(numBits + denBits - 1) / exp2(denBits);
}

#define CHECK_MIN(n, d)                                            \
    do {                                                           \
        q<n, d> f;                                                 \
        EXPECT_NEAR(f.min().toDouble(), calc_min(n, d), exp2(-d)); \
    } while (0);

#define CHECK_MAX(n, d)                                            \
    do {                                                           \
        q<n, d> f;                                                 \
        EXPECT_NEAR(f.max().toDouble(), calc_max(n, d), exp2(-d)); \
    } while (0);

class limits_min8;
class limits_min16;
class limits_min32;
class limits_min64;

class limits_max8;
class limits_max16;
class limits_max32;
class limits_max64;

#endif // TEST_LIMITS_H
