#ifndef COMMON_HPP
#define COMMON_HPP

#include "qfm/qfm.hpp"
#include <limits>
#include <ostream>

template<int N, int D> double abs_prec(double a, qfm::q<N, D> in)
{
    return in.toDouble() - a;
}

template<int N, int D> double rel_prec(double a, qfm::q<N, D> in)
{
    return 100.0 * (abs_prec(a, in) / a);
}

double abs_prec(double a, double in)
{
    return in - a;
}

double rel_prec(double a, double in)
{
    return 100.0 * (abs_prec(a, in) / a);
}

class binary_record
{
public:
    binary_record() = delete;
    binary_record(double a, double b) : x(a), y(b) {}
    binary_record(double a, double b, double c, double d)
        : x(a), y(b)
    {
    }

    std::ostream &operator<<(std::ostream &os)
    {
        os << x << '\t' << y << '\t' << rel_prec << '\t' << lsb_prec;
        return os;
    }

private:
    double x;
    double y;
    double rel_prec{std::numeric_limits<double>::quiet_NaN()};
    double lsb_prec{std::numeric_limits<double>::quiet_NaN()};
};

#endif // COMMON_HPP
