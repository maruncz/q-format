#include "qfm/qfm.hpp"
#include <random>
#include <testcasebasic.h>
#include <testmacros.h>

template<std::uint8_t N, std::uint8_t D> testBase::result random_additions()
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
        double max      = std::min(qmax, qmax - d1);
        double min      = std::max(qmin, qmin - d1);
        std::uniform_real_distribution<double> tmp_dist(min, max);
        q_t f2(tmp_dist(generator));
        double d2 = f2.toDouble();
        q_t f3    = f1 + f2;
        double d3 = d1 + d2;
        ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble() / 2);
    }
    return testBase::result(true);
}

TEST(addition, 1_7)
{
    return random_additions<1, 7>();
}

TEST(addition, 1_15)
{
    return random_additions<1, 15>();
}

TEST(addition, 1_31)
{
    return random_additions<1, 31>();
}
