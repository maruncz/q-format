#include "test_subtraction.h"
#include "q-format-ops-basic.h"
#include "q-format.h"
#include "test_misc.h"
#include <random>

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_subtractions()
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
        double max      = -std::min(qmax, qmax - d1);
        double min      = -std::max(qmin, qmin - d1);
        std::uniform_real_distribution<double> tmp_dist(min, max);
        q_t f2(tmp_dist(generator));
        double d2 = f2.toDouble();
        q_t f3    = f1 - f2;
        double d3 = d1 - d2;
        assert_near(d3, f3.toDouble(), f3.eps().toDouble(), "");
    }
}

void test_operations_subtraction17()
{
    test_start(__func__);
    random_subtractions<1, 7>();
    test_done(__func__);
}

void test_operations_subtraction115()
{
    test_start(__func__);
    random_subtractions<1, 15>();
    test_done(__func__);
}

void test_operations_subtraction131()
{
    test_start(__func__);
    random_subtractions<1, 31>();
    test_done(__func__);
}
