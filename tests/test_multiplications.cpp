#include "test_multiplications.h"
#include <iomanip>
#include <random>

/**
 * @todo opravit limity
 */
template<std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_multiplications()
{
    using q_t = q<T_numBits, T_denBits>;
    auto qmin = q_t::min().toLongDouble();
    auto qmax = q_t::max().toLongDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<long double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t f1(dist(generator));
        const long double d1 = f1.toLongDouble();

        const long double max = d1 / qmax;
        const long double min = d1 / qmin;

        std::uniform_real_distribution<long double> tmp(min, max);

        q_t f2(tmp(generator));
        const long double d2 = f2.toLongDouble();
        q_t f3               = f1 * f2;
        long double d3       = d1 * d2;

        if constexpr ((T_numBits + T_denBits) <= 52)
        {
            ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble())
                << "err at f1: " << f1.toDouble() << " f2: " << f2.toDouble();
        }
        else
        {
            long double diff = std::abs(d3 - f3.toLongDouble());
            ASSERT_TRUE(diff <=
                        (std::max(f3.eps().toLongDouble(),
                                  std::numeric_limits<long double>::epsilon())))
                << std::setprecision(20) << "err at\nf1:\t" << f1.toLongDouble()
                << "\nf2:\t" << f2.toLongDouble() << "\nd3:\t" << d3
                << "\nf3:\t" << f3.toLongDouble() << "\neps:\t"
                << f3.eps().toLongDouble() << "\ndiff:\t" << diff
                << "\ndiff rel:\t" << diff / f3.eps().toLongDouble();
        }
    }
}

TEST(operations, multiplication17)
{
    random_multiplications<1, 7>();
}

TEST(operations, multiplication115)
{
    random_multiplications<1, 15>();
}

TEST(operations, multiplication131)
{
    random_multiplications<1, 31>();
}
