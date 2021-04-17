#include "test_exp.h"
#include "q-format-ops-exp.h"
#include "q-format.h"
#include "test_misc.h"
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
        q_t f1(dist(generator));
        double d1   = f1.toDouble();
        uint8_t exp = dist2(generator);
        q_t f2      = f1.pow(f1, exp);
        double d2   = std::pow(d1, exp);

        assert_near(f2.toDouble(), d2, q_t::eps().toDouble(), "");
    }
}
