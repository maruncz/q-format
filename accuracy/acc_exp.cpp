#include "common.hpp"
#include "qfm/qfm.hpp"
#include <cmath>
#include <fstream>
#include <sstream>

template<int N, int D> void run()
{
    using T   = qfm::q<N, D>;
    auto dmax = std::log(T::max().toDouble() - (T::eps().toDouble() / 2));
    auto dmin = std::log(T::eps().toDouble() + (T::eps().toDouble() / 2));
    T max = T(std::min(dmax, T::max().toDouble() - (T::eps().toDouble() / 2)));
    T min = T(std::max(dmin, T::min().toDouble() + (T::eps().toDouble() / 2)));
    auto eps = T::eps();

    while (((max.toDouble() - min.toDouble()) / eps.toDouble()) > 100000)
    {
        eps *= 2;
    }

    std::stringstream s;
    s << "acc_exp-" << N << '-' << D << ".txt";
    std::ofstream f(s.str());
    for (T e = min; e <= max; e += eps)
    {
        T q      = T::exp(e);
        double d = std::exp(e.toDouble());
        f << e.toDouble() << '\t' << d << '\t' << q.toDouble() << '\t'
          << rel_prec(d, q) << '\t' << abs_prec(d, q) / T::eps().toDouble()
          << '\n';
        if (e == max)
        {
            break;
        }
    }
    f.close();
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
