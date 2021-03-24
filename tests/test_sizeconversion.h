#ifndef TEST_SIZECONVERSION_H
#define TEST_SIZECONVERSION_H

#include "../q-format.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#define CONV_SIZE(n, d)                \
    do {                               \
        q<n, d>     f1(-exp2(-d));     \
        q<n, d + 1> f2(f1);            \
        EXPECT_NEAR(f1, f2, f1.eps()); \
    } while (0);

class test_conversion_size;

#endif // TEST_SIZECONVERSION_H
