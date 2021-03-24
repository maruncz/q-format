#include "test_limits.h"

TEST(limits, min8)
{
    CHECK_MIN(1, 1);
    CHECK_MIN(1, 2);
    CHECK_MIN(1, 3);
    CHECK_MIN(1, 4);
    CHECK_MIN(1, 5);
    CHECK_MIN(1, 6);
    CHECK_MIN(1, 7);
    CHECK_MIN(2, 1);
    CHECK_MIN(2, 2);
    CHECK_MIN(2, 3);
    CHECK_MIN(2, 4);
    CHECK_MIN(2, 5);
    CHECK_MIN(2, 6);
    CHECK_MIN(3, 1);
    CHECK_MIN(3, 2);
    CHECK_MIN(3, 3);
    CHECK_MIN(3, 4);
    CHECK_MIN(3, 5);
    CHECK_MIN(4, 1);
    CHECK_MIN(4, 2);
    CHECK_MIN(4, 3);
    CHECK_MIN(4, 4);
    CHECK_MIN(5, 1);
    CHECK_MIN(5, 2);
    CHECK_MIN(5, 3);
    CHECK_MIN(6, 1);
    CHECK_MIN(6, 2);
    CHECK_MIN(7, 1);
}
