#include "test_sizeconversion.h"

TEST(conversion,size)
{
    {
        q<1,1> f1(-0.5);
        q<1,63> f2(f1);
        EXPECT_NEAR(f1,f2,f1.eps());
    }
    {
        q<1,63> f1(-0.5);
        q<1,1> f2(f1);
        EXPECT_NEAR(f1,f2,f2.eps());
    }
    {
        q<1,2> f1(0.25);
        q<1,63> f2(f1);
        EXPECT_NEAR(f1,f2,f1.eps());
    }

    CONV_SIZE(2,2);
}
