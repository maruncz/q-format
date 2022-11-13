#include "q-format.h"
#include <benchmarkbasic.h>
#include <cmath>

BENCHMARK(exp, float_std)
{
    float in = 5.0f;
    DoNotOptimize(in);
    auto res = std::exp(in);
    DoNotOptimize(res);
}

BENCHMARK(exp, q_16_16)
{
    q<16, 16> in{5.0f};
    DoNotOptimize(in);
    auto res = q<16, 16>::exp(in);
    DoNotOptimize(res);
}
