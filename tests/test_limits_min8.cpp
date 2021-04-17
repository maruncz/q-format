#include "test_limits.h"

void test_limits_min8()
{
    test_start(__func__);
    check_min<1, 1>();
    check_min<1, 2>();
    check_min<1, 3>();
    check_min<1, 4>();
    check_min<1, 5>();
    check_min<1, 6>();
    check_min<1, 7>();
    check_min<2, 1>();
    check_min<2, 2>();
    check_min<2, 3>();
    check_min<2, 4>();
    check_min<2, 5>();
    check_min<2, 6>();
    check_min<3, 1>();
    check_min<3, 2>();
    check_min<3, 3>();
    check_min<3, 4>();
    check_min<3, 5>();
    check_min<4, 1>();
    check_min<4, 2>();
    check_min<4, 3>();
    check_min<4, 4>();
    check_min<5, 1>();
    check_min<5, 2>();
    check_min<5, 3>();
    check_min<6, 1>();
    check_min<6, 2>();
    check_min<7, 1>();
    test_done(__func__);
}
