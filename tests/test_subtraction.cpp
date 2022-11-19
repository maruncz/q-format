#include "qfm/qfm.hpp"
#include <random>
#include <testcasebasic.h>
#include <testmacros.h>

template<std::uint8_t N, std::uint8_t D> testBase::result random_subtractions()
{
    using q_t = qfm::q<N, D>;
    auto qmin = q_t::min().toDouble();
    auto qmax = q_t::max().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t f1(dist(generator));
        const double d1 = f1.toDouble();
        double max      = (d1 > 0) ? qmax : qmax + d1;
        double min      = (d1 > 0) ? d1 - qmax : qmin;
        std::uniform_real_distribution<double> tmp_dist(min, max);
        q_t f2(tmp_dist(generator));
        double d2 = f2.toDouble();
        q_t f3    = f1 - f2;
        double d3 = d1 - d2;
        ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble() / 2);
    }
    return testBase::result(true);
}

TEST(subtraction, 1_7)
{
    return random_subtractions<1, 7>();
}

TEST(subtraction, 4_4)
{
    return random_subtractions<4, 4>();
}

TEST(subtraction, 1_15)
{
    return random_subtractions<1, 15>();
}

TEST(subtraction, 8_8)
{
    return random_subtractions<8, 8>();
}

TEST(subtraction, 1_31)
{
    return random_subtractions<1, 31>();
}

TEST(subtraction, 16_16)
{
    return random_subtractions<16, 16>();
}
