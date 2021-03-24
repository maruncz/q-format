#include "test_limits.h"

TEST(limits, max8)
{
    CHECK_MAX(1, 1);
    CHECK_MAX(1, 2);
    CHECK_MAX(1, 3);
    CHECK_MAX(1, 4);
    CHECK_MAX(1, 5);
    CHECK_MAX(1, 6);
    CHECK_MAX(1, 7);
    CHECK_MAX(2, 1);
    CHECK_MAX(2, 2);
    CHECK_MAX(2, 3);
    CHECK_MAX(2, 4);
    CHECK_MAX(2, 5);
    CHECK_MAX(2, 6);
    CHECK_MAX(3, 1);
    CHECK_MAX(3, 2);
    CHECK_MAX(3, 3);
    CHECK_MAX(3, 4);
    CHECK_MAX(3, 5);
    CHECK_MAX(4, 1);
    CHECK_MAX(4, 2);
    CHECK_MAX(4, 3);
    CHECK_MAX(4, 4);
    CHECK_MAX(5, 1);
    CHECK_MAX(5, 2);
    CHECK_MAX(5, 3);
    CHECK_MAX(6, 1);
    CHECK_MAX(6, 2);
    CHECK_MAX(7, 1);
}
