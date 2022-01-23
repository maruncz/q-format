#include "q-format-ops-basic.h"
#include <gtest/gtest.h>
#include <random>

template<std::uint8_t T_numBits, std::uint8_t T_denBits> void random_divisions()
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

        const auto max = qmax;
        const auto min = std::abs(d1 / qmax) + q_t::eps().toDouble();
        std::uniform_real_distribution<double> tmp(min, max);

        q_t f2(tmp(generator));
        const double d2 = f2.toDouble();
        q_t f3          = f1 / f2;
        double d3       = d1 / d2;

        ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble());
    }
}

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_divisions_int()
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

        const typename q_t::int_type max = 1 / q_t::eps().toDouble();
        const typename q_t::int_type min = 1;
        std::uniform_int_distribution<typename q_t::int_type> tmp(min, max);
        typename q_t::int_type f2(tmp(generator));
        if (f2 == 0)
        {
            continue;
        }
        const double d2 = f2;
        q_t f3          = f1 / f2;
        double d3       = d1 / d2;

        ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble());
    }
}

TEST(division, 1_7)
{
    random_divisions<1, 7>();
}

TEST(division, 1_15)
{
    random_divisions<1, 15>();
}

TEST(division, 1_31)
{
    random_divisions<1, 31>();
}

TEST(division, 1_7_int)
{
    random_divisions_int<1, 7>();
}

TEST(division, 1_15_int)
{
    random_divisions_int<1, 15>();
}

TEST(division, 1_31_int)
{
    random_divisions_int<1, 31>();
}
