#include <q-format.h>
#include <q-format-ops-exp.h>
#include <benchmarktemplate.h>
#include <benchmarkbasic.h>
#include <cmath>


BENCHMARK(exp,float_std)
{
    float in = 5.0f;
    DoNotOptimize(in);
    auto res = std::exp(in);
    DoNotOptimize(res);
}
