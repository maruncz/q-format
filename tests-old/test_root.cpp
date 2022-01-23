#include "test_root.h"
#include "q-format-ops-root.h"
#include "q-format.h"
#include "test_misc.h"
#include <random>

template<std::uint8_t T_numBits, std::uint8_t T_denBits> void random_sqrt()
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
        q_t f2    = f1.sqrt();
        double d2 = sqrt(d1);
        assert_near(f2.toDouble(), d2, q_t::eps().toDouble(), "");
    }
}

void test_root_sqrt17()
{
    test_start(__func__);
    random_sqrt<1, 7>();
    test_done(__func__);
}

void test_root_sqrt115()
{
    test_start(__func__);
    random_sqrt<1, 15>();
    test_done(__func__);
}
