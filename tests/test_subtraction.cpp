#include "test_subtraction.h"
#include <random>

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_subtractions()
{
    using q_t                                   = q<T_numBits, T_denBits>;
    auto                                   qmin = q_t::min().toDouble();
    auto                                   qmax = q_t::max().toDouble();
    std::default_random_engine             generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t                                    f1(dist(generator));
        const double                           d1  = f1.toDouble();
        double                                 max = -std::min(qmax, qmax - d1);
        double                                 min = -std::max(qmin, qmin - d1);
        std::uniform_real_distribution<double> tmp_dist(min, max);
        q_t                                    f2(tmp_dist(generator));
        double                                 d2 = f2.toDouble();
        q_t                                    f3 = f1 - f2;
        double                                 d3 = d1 - d2;
        ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble());
    }
}

TEST(operations, subtraction17)
{
    random_subtractions<1, 7>();
}

TEST(operations, subtraction116)
{
    random_subtractions<1, 15>();
}

TEST(operations, subtraction131)
{
    random_subtractions<1, 31>();
}
