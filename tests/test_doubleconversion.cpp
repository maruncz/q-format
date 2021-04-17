#include "test_doubleconversion.h"
#include "q-format.h"
#include "test_misc.h"
#include <random>

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_doubleConversions()
{
    using q_t = q<T_numBits, T_denBits>;
    auto qmin = q_t::min().toDouble();
    auto qmax = q_t::max().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 1000; ++i)
    {
        double d = dist(generator);
        q_t f(d);

        assert_near(d, f.toDouble(), f.eps().toDouble(), "");
    }
}

void test_conversion_doubleConversion17()
{
    test_start(__func__);
    random_doubleConversions<1, 7>();
}

void test_conversion_doubleConversion115()
{
    test_start(__func__);
    random_doubleConversions<1, 15>();
    test_done(__func__);
}

void test_conversion_doubleConversion131()
{
    test_start(__func__);
    random_doubleConversions<1, 31>();
    test_done(__func__);
}
