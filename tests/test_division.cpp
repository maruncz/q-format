#include "qfm/detail/q_impl.hpp"
#include "qfm/qfm.hpp"
#include <random>
#include <testcasebasic.h>
#include <testmacros.h>

namespace qfm
{

template<int N, int D> class q_test : public q_base<N, D>
{
public:
    using q_base<N, D>::q_base;
    q_test(const q_base<N, D> &f) : q_base<N, D>(f) {}
    template<int N_A, int D_A, int N_B, int D_B>
    static constexpr q_test<N_A + D_B, D_A + N_B> div(q_test<N_A, D_A> a,
                                                      q_test<N_B, D_B> b)
    {
        return q_base<N, D>::div(a, b);
    }
};

} // namespace qfm

template<std::uint8_t N, std::uint8_t D> testBase::result random_divisions()
{
    using std::abs;
    using q_t           = qfm::q<N, D>;
    constexpr auto qmax = q_t::max().toDouble();
    constexpr auto qmin = q_t::min().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);

    for (int i = 0; i < 10000; ++i)
    {
        auto da    = dist(generator);
        double max = (da > 0) ? (da / qmax) + q_t::eps().toDouble() / 2
                              : (-da / qmin) - q_t::eps().toDouble() / 2;
        double min = (da > 0) ? qmax - q_t::eps().toDouble() / 2
                              : qmin + q_t::eps().toDouble() / 2;
        std::uniform_real_distribution<double> tmpdist(min, max);
        auto db = tmpdist(generator);
        q_t fa{da};
        q_t fb{db};
        if (fb == q_t(0))
        {
            continue;
        }
        auto fc = fa / fb;
        auto dc = fa.toDouble() / fb.toDouble();

        ASSERT_NEAR(dc, fc.toDouble(), fc.eps().toDouble() / 2);
    }
    return testBase::result(true);
}

template<std::uint8_t N, std::uint8_t D>
testBase::result random_divisions_priv()
{
    using std::abs;
    using q_t           = qfm::q_test<N, D>;
    constexpr auto qmax = q_t::max().toDouble();
    constexpr auto qmin = q_t::min().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);

    for (int i = 0; i < 10000; ++i)
    {
        auto da    = dist(generator);
        double max = (da > 0) ? (da / qmax) + q_t::eps().toDouble() / 2
                              : (-da / qmin) - q_t::eps().toDouble() / 2;
        double min = (da > 0) ? qmax - q_t::eps().toDouble() / 2
                              : qmin + q_t::eps().toDouble() / 2;
        std::uniform_real_distribution<double> tmpdist(min, max);
        auto db = tmpdist(generator);
        q_t fa{da};
        q_t fb{db};
        if (fb == q_t(0))
        {
            continue;
        }
        auto fc = q_t::div(fa, fb);
        auto dc = fa.toDouble() / fb.toDouble();

        ASSERT_NEAR(dc, fc.toDouble(), fc.eps().toDouble());
    }
    return testBase::result(true);
}

template<std::uint8_t N, std::uint8_t D> testBase::result random_divisions_int()
{
    using q_t    = qfm::q<N, D>;
    using int_tt = typename q_t::int_type;
    auto qmin    = q_t::min().toDouble();
    auto qmax    = q_t::max().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t f1(dist(generator));
        const double d1 = f1.toDouble();

        int_tt max = (1l << (N + D - 1)) - 1;
        int_tt min = 1;
        std::uniform_int_distribution<int_tt> tmp(min, max);
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

TEST(random_divisions, 4_4)
{
    return random_divisions<4, 4>();
}

TEST(random_divisions, 8_8)
{
    return random_divisions<8, 8>();
}

TEST(random_divisions, 16_16)
{
    return random_divisions<16, 16>();
}
/********************************************/
TEST(random_divisions, 4_4_priv)
{
    return random_divisions_priv<4, 4>();
}

TEST(random_divisions, 8_8_priv)
{
    return random_divisions_priv<8, 8>();
}

TEST(random_divisions, 16_16_priv)
{
    return random_divisions_priv<16, 16>();
}
/********************************************/
TEST(random_divisions, 4_4_int)
{
    return random_divisions_int<4, 4>();
}

TEST(random_divisions, 8_8_int)
{
    return random_divisions_int<8, 8>();
}

TEST(random_divisions, 16_16_int)
{
    return random_divisions_int<16, 16>();
}
