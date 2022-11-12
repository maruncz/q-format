#include "q-format.h"
#include <random>
#include <testcasebasic.h>
#include <testmacros.h>

template<std::uint8_t N, std::uint8_t D> testBase::result random_divisions()
{
    using std::abs;
    using q_t           = q<N, D>;
    constexpr auto qmax = q_t::max().toDouble();
    constexpr auto qmin = q_t::min().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin,
                                                qmax - q_t::eps().toDouble());
    std::uniform_int_distribution<int> signdist(0, 1);

    for (int i = 0; i < 10000; ++i)
    {
        auto da    = dist(generator);
        double max = qmax;
        double min = abs(da / qmax);
        std::uniform_real_distribution<double> tmpdist(
            min + q_t::eps().toDouble(), max - q_t::eps().toDouble());
        auto db = tmpdist(generator);
        if (signdist(generator))
        {
            db *= -1.0;
        }
        q_t fa{da};
        q_t fb{db};
        if (fb == q_t(0))
        {
            continue;
        }
        auto fc = fa / fb;
        auto dc = fa.toDouble() / fb.toDouble();

        ASSERT_NEAR(dc, fc.toDouble(), fc.eps().toDouble());
    }
    return testBase::result(true);
}

template<std::uint8_t N, std::uint8_t D>
testBase::result random_divisions_normals()
{
    static_assert(N == 1, "this test is ment for numbers with N == 1");
    using q_t = q<N, D>;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    for (int i = 0; i < 10000; ++i)
    {
        auto db = dist(generator);
        auto dc = dist(generator);
        auto da = db * dc;
        q_t fa{da};
        q_t fb{db};
        if (fb == q_t(0))
        {
            continue;
        }
        if (fa == fb)
        {
            continue;
        }
        auto fc     = fa / fb;
        double ctrl = fa.toDouble() / fb.toDouble();
        ASSERT_NEAR(ctrl, fc.toDouble(), fc.eps().toDouble());
    }
    return testBase::result(true);
}

template<std::uint8_t N, std::uint8_t D> testBase::result random_divisions_int()
{
    using q_t = q<N, D>;
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
    return testBase::result(true);
}

TEST(random_divisions, 1_7)
{
    return random_divisions_normals<1, 7>();
}

TEST(random_divisions, 4_4)
{
    return random_divisions<4, 4>();
}

TEST(random_divisions, 1_15)
{
    return random_divisions_normals<1, 15>();
}

TEST(random_divisions, 8_8)
{
    return random_divisions<8, 8>();
}

TEST(random_divisions, 1_31)
{
    return random_divisions_normals<1, 31>();
}

TEST(random_divisions, 16_16)
{
    return random_divisions<16, 16>();
}

TEST(random_divisions, 1_7_int)
{
    return random_divisions_int<1, 7>();
}

TEST(random_divisions, 1_15_int)
{
    return random_divisions_int<1, 15>();
}

TEST(random_divisions, 1_31_int)
{
    return random_divisions_int<1, 31>();
}
