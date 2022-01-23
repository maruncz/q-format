#include "test_exp.h"
#include "q-format-ops-exp.h"
#include "q-format.h"
#include "test_misc.h"
#include <cstdio>
#include <random>

template<std::uint8_t T_numBits, std::uint8_t T_denBits> void random_pow_int()
{
    using q_t = q<T_numBits, T_denBits>;
    std::default_random_engine generator;
    std::uniform_int_distribution<uint8_t> dist2(1, 15);
    for (int i = 0; i < 10000; ++i)
    {
        uint8_t exp = dist2(generator);
        auto qmin   = -std::pow(q_t::max().toDouble(), 1.0 / exp);
        auto qmax   = std::pow(q_t::max().toDouble(), 1.0 / exp);
        std::uniform_real_distribution<double> dist(qmin, qmax);
        q_t f1(dist(generator));
        double d1 = f1.toDouble();
        q_t f2    = f1.pow(f1, exp);
        double d2 = std::pow(d1, exp);
        std::array<char, 200> s;
        snprintf(s.begin(), s.size(), "i: %i in: %f exp: %hhu\n", i, d1, exp);
        assert_near(f2.toDouble(), d2, q_t::eps().toDouble(), s.begin());
    }
}

void test_operations_exp17()
{
    test_start(__func__);
    random_pow_int<1, 7>();
    test_done(__func__);
}

void test_operations_exp115()
{
    test_start(__func__);
    random_pow_int<1, 15>();
    test_done(__func__);
}

void test_operations_exp88()
{
    test_start(__func__);
    random_pow_int<8, 8>();
    test_done(__func__);
}

void test_operations_exp1616()
{
    test_start(__func__);
    random_pow_int<16, 16>();
    test_done(__func__);
}

void test_operations_exp131()
{
    test_start(__func__);
    random_pow_int<1, 31>();
    test_done(__func__);
}
