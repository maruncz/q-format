#include "test_addition.h"
#include <random>

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_additions()
{
    using q_t                                   = q<T_numBits, T_denBits>;
    auto                                   qmin = q_t::min().toDouble();
    auto                                   qmax = q_t::max().toDouble();
    std::default_random_engine             generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 1000; ++i)
    {
        q_t                                    f1(dist(generator));
        const double                           d1  = f1.toDouble();
        double                                 max = std::min(qmax, qmax - d1);
        double                                 min = std::max(qmin, qmin - d1);
        std::uniform_real_distribution<double> tmp_dist(min, max);
        q_t                                    f2(tmp_dist(generator));
        double                                 d2 = f2.toDouble();
        q_t                                    f3 = f1 + f2;
        double                                 d3 = d1 + d2;
        if (std::abs(d3 - f3.toDouble()) >= f3.eps().toDouble())
            ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble());
    }
}

TEST(operations, addition)
{
    {
        q<2, 6> f1(1.9);
        q<4, 4> f2(5.4);
        q<4, 4> f3 = f2 + q<4, 4>(f1);
        ASSERT_NEAR(f3.toDouble(), 5.4 + 1.9, f3.eps().toDouble());
    }
}

TEST(operations, addition17)
{
    random_additions<1, 7>();
}

TEST(operations, addition116)
{
    random_additions<1, 16>();
}

TEST(operations, addition131)
{
    random_additions<1, 31>();
}
