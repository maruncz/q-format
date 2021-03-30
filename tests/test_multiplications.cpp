#include "test_multiplications.h"
#include <iomanip>
#include <random>

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_multiplications()
{
    using q_t                                   = q<T_numBits, T_denBits>;
    auto                                   qmin = q_t::min().toDouble();
    auto                                   qmax = q_t::max().toDouble();
    std::default_random_engine             generator;
    std::uniform_real_distribution<double> dist(qmin, qmax);
    for (int i = 0; i < 10000; ++i)
    {
        q_t          f1(dist(generator));
        const double d1 = f1.toDouble();

        double max = qmax / d1;
        if (max > qmax)
        {
            max = qmax;
        }
        else if (max < qmin)
        {
            max = qmin;
        }

        double min = qmin / d1;
        if (min > qmax)
        {
            min = qmax;
        }
        else if (min < qmin)
        {
            min = qmin;
        }

        std::uniform_real_distribution<double> tmp_dist(min, max);
        q_t                                    f2(tmp_dist(generator));
        double                                 d2 = f2.toDouble();
        q_t                                    f3 = f1 * f2;
        double                                 d3 = d1 * d2;
        ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble())
            << "err at f1: " << f1.toDouble() << " f2: " << f2.toDouble();
    }
}

template <std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_multiplications_int()
{
    auto                       imin   = std::numeric_limits<int64_t>::min();
    auto                       imax   = std::numeric_limits<int64_t>::max();
    constexpr uint8_t          numRes = T_numBits + T_denBits;
    std::default_random_engine generator;
    std::uniform_int_distribution<int_t<numRes>> dist(imin, imax);

    for (int i = 0; i < 10000; ++i)
    {
        int_t<numRes> i1 = dist(generator);
        long double   d1 = i1;
        int_t<numRes> i2 = dist(generator);
        long double   d2 = i2;

        int_t<numRes> i3 = qf_mul128<numRes, T_denBits>(i1, i2);
        long double   d3 = d1 * d2 / exp2(T_denBits);

        if constexpr (numRes <= 52)
        {
            ASSERT_NEAR(d3, i3, 0.5)
                << std::setprecision(20) << "err at i1: " << +i1
                << " i2: " << +i2 << " d3: " << d3 << " i3: " << +i3;
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

TEST(operations, multiplication)
{
    {
        q<1, 7> f1 = q<1, 7>::max();
        q<1, 7> f2 = q<1, 7>::max();
        double  d1 = f1.toDouble();
        double  d2 = f2.toDouble();
        q<1, 7> f3;
        double  d3 = d1 * d2;
        f3         = f1 * f2;
        ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble());
    }
}

TEST(operations, multiplication_int)
{
    random_multiplications_int<1, 7>();
    random_multiplications_int<1, 15>();
    random_multiplications_int<1, 31>();
    random_multiplications_int<1, 63>();
}

TEST(operations, multiplication17)
{
    random_multiplications<1, 7>();
}

TEST(operations, multiplication115)
{
    random_multiplications<1, 15>();
}

TEST(operations, multiplication131)
{
    random_multiplications<1, 31>();
}

TEST(operations, multiplication163)
{
    random_multiplications<1, 63>();
}
