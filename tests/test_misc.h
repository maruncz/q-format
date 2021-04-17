#ifndef TEST_MISC_H
#define TEST_MISC_H

#include <string>

void assert_near_double(double d1, double d2, double eps,
                        const std::string &msg);
void send_msg(const std::string &s);
void test_start(const char * s);
void test_done(const char * s);

#endif // TEST_MISC_H
