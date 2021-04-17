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
        assert_near_double(d3, f3.toDouble(), f3.eps().toDouble(), "");
    }
}

void test_operations_multiplication17()
{
    random_multiplications<1, 7>();
}

void test_operations_multiplication115()
{
    random_multiplications<1, 15>();
}

void test_operations_multiplication131()
{
    random_multiplications<1, 31>();
}
