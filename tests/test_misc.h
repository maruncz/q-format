#ifndef TEST_MISC_H
#define TEST_MISC_H

#include <string>

void assert_near_double(double d1, double d2, double eps,
                        const std::string &msg);

#endif // TEST_MISC_H
