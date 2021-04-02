#include "test_division.h"
#include <iomanip>
#include <random>

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_divisions()
{
    using q_t                       = q<T_numBits, T_denBits>;
    auto                       qmin = q_t::min().toLongDouble();
    auto                       qmax = q_t::max().toLongDouble();
    std::default_random_engine generator;
    std::uniform_real_distribution<long double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t               f1(dist(generator));
        const long double d1 = f1.toLongDouble();

        const auto max = qmax;
        const auto min = std::abs(d1 / qmax) + q_t::eps().toDouble();
        std::uniform_real_distribution<long double> tmp(min, max);

        q_t               f2(tmp(generator));
        const long double d2 = f2.toLongDouble();
        q_t               f3 = f1 / f2;
        long double       d3 = d1 / d2;

        if constexpr ((T_numBits + T_denBits) <= 52)
        {
            ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble())
                << "err at " << i << " f1: " << f1.toDouble()
                << " f2: " << f2.toDouble();
        }
        else
        {
            long double diff = std::abs(d3 - f3.toLongDouble());
            ASSERT_TRUE(diff <=
                        (std::max(f3.eps().toLongDouble(),
                                  std::numeric_limits<long double>::epsilon())))
                << std::setprecision(20) << "err at\nf1:\t" << f1.toLongDouble()
                << "\nf2:\t" << f2.toLongDouble() << "\nd3:\t" << d3
                << "\nf3:\t" << f3.toLongDouble() << "\neps:\t"
                << f3.eps().toLongDouble() << "\ndiff:\t" << diff
                << "\ndiff rel:\t" << diff / f3.eps().toLongDouble();
        }
    }
}

template <std::uint8_t numRes> void random_divisions_int()
{
    auto                       imin = std::numeric_limits<int_t<numRes>>::min();
    auto                       imax = std::numeric_limits<int_t<numRes>>::max();
    std::default_random_engine generator;
    std::uniform_int_distribution<int_t<numRes>> dist(imin, imax);

    for (int i = 0; i < 10000; ++i)
    {
        int_t<numRes> i1 = dist(generator);
        long double   d1 = i1;

        const long double max = imax;
        const long double min = std::abs(d1 / imax) + 1;

        std::uniform_real_distribution<long double> tmp(min, max);

        int_t<numRes> i2 = tmp(generator);
        long double   d2 = i2;

        auto          ret = qf_div128<numRes>(i1, i2);
        int_t<numRes> i3  = ret.first;
        long double   d3  = d1 / d2;
        long double   d4  = i3 * i2 + ret.second;

        if constexpr (numRes <= 52)
        {
            ASSERT_NEAR(d3, i3, 0.5)
                << std::setprecision(20) << "err at i1: " << +i1
                << " i2: " << +i2 << " d3: " << d3 << " i3: " << +i3
                << " rem: " << +ret.second;

            ASSERT_NEAR(d1, d4, 0.01)
                << "err at i1: " << +i1 << " i2: " << +i2 << " d1: " << d1
                << " i3: " << +i3 << " rem: " << +ret.second;
        }
        else
        {
            long double diff = std::abs(d3 - static_cast<long double>(i3));
            ASSERT_TRUE(diff <= 0.5)
                << std::setprecision(20) << "err at i1: " << +i1
                << " i2: " << +i2 << " d3: " << d3 << " i3: " << +i3;
        }
    }
}

TEST(operations, division17)
{
    random_divisions<1, 7>();
}

TEST(operations, division115)
{
    random_divisions<1, 15>();
}

TEST(operations, division131)
{
    random_divisions<1, 31>();
}

