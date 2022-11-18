#ifndef COMMON_HPP
#define COMMON_HPP

#include "qfm/qfm.hpp"

template<int N, int D> double abs_prec(double a, qfm::q<N, D> in)
{
    return in.toDouble() - a;
}

template<int N, int D> double rel_prec(double a, qfm::q<N, D> in)
{
    return 100.0 * (abs_prec(a, in) / a);
}

#endif // COMMON_HPP
