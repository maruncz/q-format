#include "qfm/qfm.hpp"
#include <cstdio>
#include <random>
#include <testcasebasic.h>
#include <testmacros.h>

template<std::uint8_t N, std::uint8_t D> testBase::result random_pow_int()
{
    using q_t = qfm::q<N, D>;
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
        std::array<char, 200> s{};
        snprintf(s.begin(), s.size(), "i: %i in: %f exp: %hhu\n", i, d1, exp);
        ASSERT_NEAR_MSG(f2.toDouble(), d2, q_t::eps().toDouble(), s.data());
    }
    return testBase::result(true);
}

template<std::uint8_t N, std::uint8_t D> testBase::result random_exp()
{
    using q_t = qfm::q<N, D>;
    std::default_random_engine generator;
    auto min = std::max(std::log(q_t::eps().toDouble()), q_t::min().toDouble());
    auto max = std::log(q_t::max().toDouble());
    std::uniform_real_distribution<double> dist(min, max);
    for (int i = 0; i < 10000; ++i)
    {
        auto exp = dist(generator);
        q_t f    = q_t::exp(q_t(exp));
        double d = std::exp(exp);
        std::array<char, 200> s{};
        snprintf(s.begin(), s.size(), "i: %i in: %f exp: %f\n", i, d, exp);
        double rel_tol = 6 * std::exp2(-D+1);
        ASSERT_NEAR_MSG(f.toDouble(), d, d * rel_tol, s.data());
    }
    return testBase::result(true);
}

TEST(exp, 1_7)
{
    return random_exp<1, 7>();
}

TEST(exp, 1_15)
{
    return random_exp<1, 15>();
}

TEST(exp, 8_8)
{
    return random_exp<8, 8>();
}

TEST(exp, 16_16)
{
    return random_exp<16, 16>();
}

TEST(exp, 1_31)
{
    return random_exp<1, 31>();
}
