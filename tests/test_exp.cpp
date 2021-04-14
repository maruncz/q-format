#include "test_exp.h"
#include "q-format-ops-exp.h"
#include <random>

template<std::uint8_t T_numBits, std::uint8_t T_denBits> void random_pow_int()
{
    using q_t = q<T_numBits, T_denBits>;
    auto qmin = q_t::min().toDouble();
    auto qmax = q_t::max().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    std::uniform_int_distribution<uint8_t> dist2(0, 15);
    for (int i = 0; i < 10000; ++i)
    {
        if (i == 19)
        {
            std::cout << "stop" << std::endl;
        }
        q_t f1(dist(generator));
        double d1   = f1.toDouble();
        uint8_t exp = dist2(generator);
        q_t f2      = f1.pow(f1, exp);
        double d2   = std::pow(d1, exp);

        ASSERT_NEAR(f2.toDouble(), d2, q_t::eps().toDouble())
            << "i: " << i << "\nexp: " << +exp << "\nf1: " << f1.toDouble()
            << "\nf2: " << f2.toDouble() << "\nd1: " << d1 << "\nd2: " << d2;
    }
}

TEST(exp, pow_int17)
{
    // random_pow_int<1, 7>();
}

TEST(exp, pow_int115)
{
    // random_pow_int<1, 15>();
}
