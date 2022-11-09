#include "q-format-ops-exp.h"
#include "q-format.h"
#include <bitset>
#include <cmath>
#include <iostream>

template<std::uint8_t T_numBits, std::uint8_t T_denBits>
void print_q(const std::string &s, const q<T_numBits, T_denBits> &f)
{
    std::cout << s << f.toDouble() << "\t " << f.max().toDouble() << "\t "
              << f.eps().toDouble() << std::endl;
}

int main()
{
    //    using q_t = q<1,7>;
    //    q_t f1{0.827181};
    //    double d1 = f1.toDouble();
    //    auto f2 = f1;
    //    auto d2 = d1;
    //    int it = 1;
    //    while (true)
    //    {
    //        f2 = f2 * f1;
    //        d2 *= d1;
    //        ++it;
    //        auto diff = std::abs(d2 - f2.toDouble());
    //        std::cout << it << '\t' << f2.toDouble() << '\t' << d2 << '\t' <<
    //        diff
    //                  << "\t\t" << q_t::eps().toDouble() << std::endl;
    //        if (diff > q_t::eps().toDouble())
    //        {
    //            break;
    //        }
    //    }

    using q_t = q<8, 8>;

    q_t e0 = q_t::exp(q_t(0));
    q_t e1 = q_t::exp(q_t(1));
    q_t e2 = q_t::exp(q_t(2));
    q_t e3 = q_t::exp(q_t(3));
    q_t e4 = q_t::exp(q_t(4));

    std::cout << std::exp(0) << '\t' << std::exp(1) << '\t' << std::exp(2)
              << '\t' << std::exp(3) << '\t' << std::exp(4) << '\n';
    std::cout << e0.toDouble() << '\t' << e1.toDouble() << '\t' << e2.toDouble()
              << '\t' << e3.toDouble() << '\t' << e4.toDouble() << '\n';

    return 0;
}
