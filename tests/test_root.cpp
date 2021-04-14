#include "test_root.h"
#include "q-format-ops-root.h"
#include <random>

template <std::uint8_t T_numBits, std::uint8_t T_denBits> void random_sqrt()
{
    using q_t                                   = q<T_numBits, T_denBits>;
    auto                                   qmin = q_t::min().toDouble();
    auto                                   qmax = q_t::max().toDouble();
    std::default_random_engine             generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t    f1(dist(generator));
        double d1 = f1.toDouble();
        q_t    f2 = f1.sqrt();
        double d2 = sqrt(d1);

        ASSERT_NEAR(f2.toDouble(), d2, q_t::eps().toDouble())
            << "i: " << i << "\nf1: " << f1.toDouble()
            << "\nf2: " << f2.toDouble() << "\nd1: " << d1 << "\nd2: " << d2;
    }
}

TEST(root, sqrt17)
{
    //random_sqrt<1, 7>();
}

TEST(root, sqrt115)
{
    // random_sqrt<1,15>();
}
