#include "q-format-ops-basic.h"
#include "q-format-ops-root.h"
#include "q-format.h"
#include <random>
#include <testcasebasic.h>
#include <testmacros.h>

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
testBase::result random_sqrt()
{
    using q_t = q<T_numBits, T_denBits>;
    auto qmin = q_t::min().toDouble();
    auto qmax = q_t::max().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t f1(dist(generator));
        double d1 = f1.toDouble();
        q_t f2 = f1.sqrt();
        double d2 = sqrt(d1);
        ASSERT_NEAR(f2.toDouble(), d2, q_t::eps().toDouble());
    }
    return testBase::result(true);
}

TEST(sqrt, 1_7)
{
    return random_sqrt<1, 7>();
}

TEST(sqrt, 1_15)
{
    return random_sqrt<1, 15>();
}
