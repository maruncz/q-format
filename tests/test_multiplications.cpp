#include "test_multiplications.h"
#include <random>

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
void random_multiplications()
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
        q_t f2(tmp_dist(generator));
        double d2 = f2.toDouble();
        q_t f3    = f1 * f2;
        double d3 = d1 * d2;
        ASSERT_NEAR(d3, f3.toDouble(), f3.eps().toDouble());
    }
}

TEST(operations, multiplication)
{
    {
        q<1, 7> f1 = q<1, 7>::max();
        q<1, 7> f2 = q<1, 7>::max();
        double d1  = f1.toDouble();
        double d2  = f2.toDouble();
        q<1, 7> f3;
        double d3 = d1 * d2;
        f3        = f1 * f2;
        ASSERT_NEAR(d3,f3.toDouble(),f3.eps().toDouble());
    }
}

TEST(operations, multiplication_int)
{
    std::default_random_engine generator;
    auto imin = std::numeric_limits<int16_t>::min();
    auto imax = std::numeric_limits<int16_t>::max();
    std::uniform_int_distribution<int64_t> dist(imin,imax);
    for(int i=0;i<10000;++i)
    {
        int16_t i1 = dist(generator);
        double d1 = i1;
        int16_t i2 = dist(generator);
        double d2 = i2;

        int16_t i3 = qf_mul128<16,15>(i1,i2);
        double d3 = d1 * d2;
        d3 /= exp2(15);

        ASSERT_NEAR(d3,i3,1) << "err at i1: " << i1 << " i2: " << i2;
    }
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