#include "test_separ.h"
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

        ASSERT_NEAR(f2.toDouble(), d2, 0.5)
            << "i: " << i << "\nf1: " << f1.toDouble()
            << "\nf2: " << f2.toDouble() << "\nd1: " << d1 << "\nd2: " << d2;
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

        ASSERT_NEAR(f2.toDouble(), d2, 0.5)
            << "i: " << i << "\nf1: " << f1.toDouble()
            << "\nf2: " << f2.toDouble() << "\nd1: " << d1 << "\nd2: " << d2;
    }
}

TEST(separation, fract17)
{
    random_fract<1, 7>();
}

TEST(separation, fract115)
{
    random_fract<1, 15>();
}

TEST(separation, fract131)
{
    random_fract<1, 31>();
}

TEST(separation, fract26)
{
    random_fract<2, 6>();
}

TEST(separation, int17)
{
    random_int<1, 7>();
}

TEST(separation, int115)
{
    random_int<1, 15>();
}

TEST(separation, int131)
{
    random_int<1, 31>();
}

TEST(separation, int26)
{
    random_int<2, 6>();
}
