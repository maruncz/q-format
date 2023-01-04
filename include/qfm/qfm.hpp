#ifndef QFM_HPP
#define QFM_HPP

#include "detail/q_impl.hpp"

namespace qfm
{

template<int I, int F> class q : public q_base<I, F>
{
    static_assert((I + F) <= 32, "unsupported width");

public:
    using q_base<I, F>::q_base;
    q(const q_base<I, F> &f) : q_base<I, F>(f) {}
};

} // namespace qfm

#endif // QFM_HPP
