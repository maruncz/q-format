#include "test_sizeconversion.h"

TEST(conversion, size)
{
    {
        q<1, 1>  f1(-0.5);
        q<1, 31> f2(f1);
        EXPECT_NEAR(f1.toDouble(), f2.toDouble(), f1.eps().toDouble());
    }
    {
        q<1, 31> f1(-0.5);
        q<1, 1>  f2(f1);
        EXPECT_NEAR(f1.toDouble(), f2.toDouble(), f2.eps().toDouble());
    }
    {
        q<1, 2>  f1(0.25);
        q<1, 31> f2(f1);
        EXPECT_NEAR(f1.toDouble(), f2.toDouble(), f1.eps().toDouble());
    }

    CONV_SIZE(2, 2);
}
