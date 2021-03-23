#ifndef TESTS_H
#define TESTS_H

#include "../q-format.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <type_traits>

using MyTypes =
    ::testing::Types<std::integral_constant<uint8_t,0>,std::integral_constant<uint8_t,49>>;

using namespace testing;

double calc_max(uint8_t numBits, uint8_t denBits)
{
    return (exp2(numBits + denBits - 1) - 1) / exp2(denBits);
}

double calc_min(uint8_t numBits, uint8_t denBits)
{
    return -exp2(numBits + denBits - 1) / exp2(denBits);
}

#define CHECK_MIN(n, d)                                 \
    do                                                  \
    {                                                   \
        q<n, d> f;                                      \
        EXPECT_NEAR(f.min(), calc_min(n, d), exp2(-d)); \
    } while (0);

TEST(limits, max)
{
    {
        q<2, 2> f;
        double d = calc_max(2, 2);
        EXPECT_NEAR(f.max(), d, exp2(-2));
    }
    {
        q<2, 6> f;
        double d = calc_max(2, 6);
        EXPECT_NEAR(f.max(), d, exp2(-6));
    }
}

TEST(limits, min)
{
    {
        q<2, 2> f;
        double d = calc_min(2, 2);
        EXPECT_NEAR(f.min(), d, exp2(-2));
    }
    {
        q<2, 6> f;
        double d = calc_min(2, 6);
        EXPECT_NEAR(f.min(), d, exp2(-6));
    }
    CHECK_MIN(1, 7);
    CHECK_MIN(2, 6);
    CHECK_MIN(3, 5);
    CHECK_MIN(4, 4);
    CHECK_MIN(5, 3);
    CHECK_MIN(6, 2);
    CHECK_MIN(7, 1);
}

TEST(floatConversion, floatConversion22)
{
    for (double i = q<2, 2>::min(); i < q<2, 2>::max(); i += q<2, 2>::eps())
    {
        EXPECT_NEAR(i, double(q<2, 2>(i)), double(q<2, 2>::eps()));
    }
}

#endif // TESTS_H
