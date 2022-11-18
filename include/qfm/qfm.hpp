#ifndef QFM_HPP
#define QFM_HPP

#include "detail/q_impl.hpp"

namespace qfm
{

template<int N, int D> class q : public q_base<N, D>
{
    static_assert((N + D) <= 32, "unsupported width");

public:
    using q_base<N, D>::q_base;
    q(const q_base<N, D> &f) : q_base<N, D>(f) {}
};

} // namespace qfm

#endif // QFM_HPP
