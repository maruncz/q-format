#include "common.hpp"
#include "qfm/qfm.hpp"
#include <cmath>
#include <fstream>
#include <sstream>

template<int N, int D> void run()
{
    using T  = qfm::q<N, D>;
    auto max = T::max().toDouble();
    auto min = T::min().toDouble();
    auto eps = T::eps().toDouble();

    while (((max - min) / eps) > 512)
    {
        eps *= 2;
    }

    std::stringstream s;
    s << "acc_div-" << N << '-' << D << ".txt";
    std::ofstream f(s.str());

    for (auto a = min; a <= max; a += eps)
    {
        for (auto b = min; b <= max; b += eps)
        {
            if (std::abs(b) < T::eps().toDouble())
            {
                f << a << '\t' << b << '\t'
                  << std::numeric_limits<double>::quiet_NaN() << '\t'
                  << std::numeric_limits<double>::quiet_NaN() << '\t'
                  << std::numeric_limits<double>::quiet_NaN() << '\t'
                  << std::numeric_limits<double>::quiet_NaN() << '\n';
                continue;
            }
            double d = a / b;
            if ((d >= min) && (d <= max))
            {
                T c = T(a) / T(b);
                f << a << '\t' << b << '\t' << c.toDouble() << '\t' << d << '\t'
                  << rel_prec(d, c) << '\t'
                  << abs_prec(d, c) / T::eps().toDouble() << '\n';
            }
            else
            {
                f << a << '\t' << b << '\t'
                  << std::numeric_limits<double>::quiet_NaN() << '\t' << d
                  << '\t' << std::numeric_limits<double>::quiet_NaN() << '\t'
                  << std::numeric_limits<double>::quiet_NaN() << '\n';
            }
        }
        f << '\n';
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }
    std::string type = argv[1];
    if (type == "1-7")
    {
        run<1, 7>();
    }
    else if (type == "4-4")
    {
        run<4, 4>();
    }
    else if (type == "1-15")
    {
        run<1, 15>();
    }
    else if (type == "8-8")
    {
        run<8, 8>();
    }
    else if (type == "1-31")
    {
        run<1, 31>();
    }
    else if (type == "16-16")
    {
        run<16, 16>();
    }
    else
    {
        return 2;
    }

    return 0;
}
