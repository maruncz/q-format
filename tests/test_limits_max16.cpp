#include "test_limits.h"

TEST(limits, max16)
{
    CHECK_MAX(1, 8);
    CHECK_MAX(1, 9);
    CHECK_MAX(1, 10);
    CHECK_MAX(1, 11);
    CHECK_MAX(1, 12);
    CHECK_MAX(1, 13);
    CHECK_MAX(1, 14);
    CHECK_MAX(1, 15);
    CHECK_MAX(2, 7);
    CHECK_MAX(2, 8);
    CHECK_MAX(2, 9);
    CHECK_MAX(2, 10);
    CHECK_MAX(2, 11);
    CHECK_MAX(2, 12);
    CHECK_MAX(2, 13);
    CHECK_MAX(2, 14);
    CHECK_MAX(3, 6);
    CHECK_MAX(3, 7);
    CHECK_MAX(3, 8);
    CHECK_MAX(3, 9);
    CHECK_MAX(3, 10);
    CHECK_MAX(3, 11);
    CHECK_MAX(3, 12);
    CHECK_MAX(3, 13);
    CHECK_MAX(4, 5);
    CHECK_MAX(4, 6);
    CHECK_MAX(4, 7);
    CHECK_MAX(4, 8);
    CHECK_MAX(4, 9);
    CHECK_MAX(4, 10);
    CHECK_MAX(4, 11);
    CHECK_MAX(4, 12);
    CHECK_MAX(5, 4);
    CHECK_MAX(5, 5);
    CHECK_MAX(5, 6);
    CHECK_MAX(5, 7);
    CHECK_MAX(5, 8);
    CHECK_MAX(5, 9);
    CHECK_MAX(5, 10);
    CHECK_MAX(5, 11);
    CHECK_MAX(6, 3);
    CHECK_MAX(6, 4);
    CHECK_MAX(6, 5);
    CHECK_MAX(6, 6);
    CHECK_MAX(6, 7);
    CHECK_MAX(6, 8);
    CHECK_MAX(6, 9);
    CHECK_MAX(6, 10);
    CHECK_MAX(7, 2);
    CHECK_MAX(7, 3);
    CHECK_MAX(7, 4);
    CHECK_MAX(7, 5);
    CHECK_MAX(7, 6);
    CHECK_MAX(7, 7);
    CHECK_MAX(7, 8);
    CHECK_MAX(7, 9);
    CHECK_MAX(8, 1);
    CHECK_MAX(8, 2);
    CHECK_MAX(8, 3);
    CHECK_MAX(8, 4);
    CHECK_MAX(8, 5);
    CHECK_MAX(8, 6);
    CHECK_MAX(8, 7);
    CHECK_MAX(8, 8);
    CHECK_MAX(9, 1);
    CHECK_MAX(9, 2);
    CHECK_MAX(9, 3);
    CHECK_MAX(9, 4);
    CHECK_MAX(9, 5);
    CHECK_MAX(9, 6);
    CHECK_MAX(9, 7);
    CHECK_MAX(10, 1);
    CHECK_MAX(10, 2);
    CHECK_MAX(10, 3);
    CHECK_MAX(10, 4);
    CHECK_MAX(10, 5);
    CHECK_MAX(10, 6);
    CHECK_MAX(11, 1);
    CHECK_MAX(11, 2);
    CHECK_MAX(11, 3);
    CHECK_MAX(11, 4);
    CHECK_MAX(11, 5);
    CHECK_MAX(12, 1);
    CHECK_MAX(12, 2);
    CHECK_MAX(12, 3);
    CHECK_MAX(12, 4);
    CHECK_MAX(13, 1);
    CHECK_MAX(13, 2);
    CHECK_MAX(13, 3);
    CHECK_MAX(14, 1);
    CHECK_MAX(14, 2);
    CHECK_MAX(15, 1);
}
