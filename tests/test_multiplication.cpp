#include "qfm/qfm.hpp"
#include <random>
#include <testcasebasic.h>
#include <testmacros.h>

/**
 * @todo opravit limity
 */
template<std::uint8_t N, std::uint8_t D>
testBase::result random_multiplications()
{
    using q_t = qfm::q<N, D>;
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
        q_t f3 = f1 * f2;
        double d3 = d1 * d2;
        ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble());
    }
    return testBase::result(true);
}

/**
 * @todo opravit limity
 */
template<std::uint8_t N, std::uint8_t D>
testBase::result random_multiplications_int()
{
    using q_t = qfm::q<N, D>;
    auto qmin = q_t::min().toDouble();
    auto qmax = q_t::max().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t f1(dist(generator));
        const double d1 = f1.toDouble();

        const typename q_t::int_type max = std::abs(q_t::max().toDouble()
                                                    / f1.toDouble());
        const typename q_t::int_type min = 0;
        std::uniform_int_distribution<typename q_t::int_type> tmp(min, max);
        typename q_t::int_type f2(tmp(generator));

        double d2 = f2;
        q_t f3 = f1 * f2;
        double d3 = d1 * d2;
        ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble());
    }
    return testBase::result(true);
}

TEST(multiplication, 1_7)
{
    return random_multiplications<1, 7>();
}

TEST(multiplication, 1_15)
{
    return random_multiplications<1, 15>();
}

TEST(multiplication, 1_31)
{
    return random_multiplications<1, 31>();
}

TEST(multiplication, 1_7_int)
{
    return random_multiplications_int<1, 7>();
}

TEST(multiplication, 1_15_int)
{
    return random_multiplications_int<1, 15>();
}

TEST(multiplication, 1_31_int)
{
    return random_multiplications_int<1, 31>();
}
