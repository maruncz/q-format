#include "test_separ.h"
#include "q-format.h"
#include "test_misc.h"
#include <random>

template<std::uint8_t T_numBits, std::uint8_t T_denBits> void random_fract()
{
    using q_t    = q<T_numBits, T_denBits>;
    using int_tt = int_t<T_numBits + T_denBits>;
    auto qmin    = q_t::min().toDouble();
    auto qmax    = q_t::max().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t f1(dist(generator));
        double d1 = f1.toDouble();
        q_t f2    = f1.getFrac();
        double d2 = d1 - static_cast<int_tt>(d1);
        assert_near_double(f2.toDouble(), d2, 0.5, "");
    }
}

template<std::uint8_t T_numBits, std::uint8_t T_denBits> void random_int()
{
    using q_t    = q<T_numBits, T_denBits>;
    using int_tt = int_t<T_numBits + T_denBits>;
    auto qmin    = q_t::min().toDouble();
    auto qmax    = q_t::max().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t f1(dist(generator));
        double d1 = f1.toDouble();
        q_t f2    = f1.getInt();
        double d2 = static_cast<int_tt>(d1);

        assert_near_double(f2.toDouble(), d2, 0.5, "");
    }
}

void test_separation_fract17()
{
    test_start(__func__);
    random_fract<1, 7>();
    test_done(__func__);
}

void test_separation_fract115()
{
    test_start(__func__);
    random_fract<1, 15>();
    test_done(__func__);
}

void test_separation_fract131()
{
    test_start(__func__);
    random_fract<1, 31>();
    test_done(__func__);
}

void test_separation_int17()
{
    test_start(__func__);
    random_int<1, 7>();
    test_done(__func__);
}

void test_separation_int115()
{
    test_start(__func__);
    random_int<1, 15>();
    test_done(__func__);
}

void test_separation_int131()
{
    test_start(__func__);
    random_int<1, 31>();
    test_done(__func__);
}
