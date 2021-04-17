#include "test_limits.h"

void test_limits_max8()
{
    test_start(__func__);
    check_max<1, 1>();
    check_max<1, 2>();
    check_max<1, 3>();
    check_max<1, 4>();
    check_max<1, 5>();
    check_max<1, 6>();
    check_max<1, 7>();
    check_max<2, 1>();
    check_max<2, 2>();
    check_max<2, 3>();
    check_max<2, 4>();
    check_max<2, 5>();
    check_max<2, 6>();
    check_max<3, 1>();
    check_max<3, 2>();
    check_max<3, 3>();
    check_max<3, 4>();
    check_max<3, 5>();
    check_max<4, 1>();
    check_max<4, 2>();
    check_max<4, 3>();
    check_max<4, 4>();
    check_max<5, 1>();
    check_max<5, 2>();
    check_max<5, 3>();
    check_max<6, 1>();
    check_max<6, 2>();
    check_max<7, 1>();
    test_done(__func__);
}
