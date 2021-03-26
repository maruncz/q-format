#include "test_doubleconversion.h"
#include <random>

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_doubleConversions()
{
    using q_t                                   = q<T_numBits, T_denBits>;
    auto                                   qmin = q_t::min().toDouble();
    auto                                   qmax = q_t::max().toDouble();
    std::default_random_engine             generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 1000; ++i)
    {
        double d = dist(generator);
        q_t    f(d);

        ASSERT_NEAR(d, f.toDouble(), f.eps().toDouble());
    }
}

TEST(conversion, doubleConversion17)
{
    random_doubleConversions<1, 7>();
}

TEST(conversion, doubleConversion115)
{
    random_doubleConversions<1, 15>();
}

TEST(conversion, doubleConversion131)
{
    random_doubleConversions<1, 31>();
}

TEST(conversion, doubleConversion163)
{
    random_doubleConversions<1, 63>();
}
