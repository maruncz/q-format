#include "test_multiplications.h"
#include "q-format-ops-basic.h"
#include "test_misc.h"
#include <q-format.h>
#include <random>

/**
 * @todo opravit limity
 */
template<std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_multiplications()
{
    using q_t = q<T_numBits, T_denBits>;
    auto qmin = q_t::min().toDouble();
    auto qmax = q_t::max().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t f1(dist(generator));
        const double d1 = f1.toDouble();

        const double max = d1 / qmax;
        const double min = d1 / qmin;

        std::uniform_real_distribution<double> tmp(min, max);

        q_t f2(tmp(generator));
        const double d2 = f2.toDouble();
        q_t f3          = f1 * f2;
        double d3       = d1 * d2;
        assert_near(d3, f3.toDouble(), f3.eps().toDouble(), "");
    }
}

void test_operations_multiplication17()
{
    test_start(__func__);
    random_multiplications<1, 7>();
    test_done(__func__);
}

void test_operations_multiplication115()
{
    test_start(__func__);
    random_multiplications<1, 15>();
    test_done(__func__);
}

void test_operations_multiplication131()
{
    test_start(__func__);
    random_multiplications<1, 31>();
    test_done(__func__);
}
