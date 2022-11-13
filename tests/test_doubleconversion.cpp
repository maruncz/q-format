#include "q-format.h"
#include <random>
#include <testcasebasic.h>
#include <testmacros.h>

template<std::uint8_t N, std::uint8_t D>
testBase::result random_doubleConversions()
{
    using q_t = q<N, D>;
    auto qmin = q_t::min().toDouble();
    auto qmax = q_t::max().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 1000; ++i)
    {
        double d = dist(generator);
        q_t f(d);

        ASSERT_NEAR(d, f.toDouble(), f.eps().toDouble());
    }
    return testBase::result(true);
}

TEST(doubleConversions, 1_7)
{
    return random_doubleConversions<1, 7>();
}

TEST(doubleConversions, 1_15)
{
    return random_doubleConversions<1, 15>();
}

TEST(doubleConversions, 1_31)
{
    return random_doubleConversions<1, 31>();
}
