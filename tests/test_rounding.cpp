#include "qfm/qfm.hpp"
#include <random>
#include <testcasebasic.h>
#include <testmacros.h>

template<int N, int D, int N_O, int D_O> testBase::result random_rounding()
{
    using q_t = qfm::q<N, D>;
    using q_o = qfm::q<N_O, D_O>;
    auto eps  = std::max(q_t::eps().toDouble(), q_o::eps().toDouble());
    auto qmin = q_t::min().toDouble();
    auto qmax = q_t::max().toDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 1000; ++i)
    {
        double d = dist(generator);
        q_t f(d);
        q_o g(f);
        ASSERT_NEAR(f.toDouble(), g.toDouble(), eps / 2.0);
    }
    return testBase::result(true);
}

TEST(doubleConversions, 6_10_10_6)
{
    return random_rounding<6,10,10,6>();
}
