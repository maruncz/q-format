#include "test_misc.h"

#ifndef LIBOPENCM3
#    include <iostream>
#else
#    include <cstring>
#    include <uart.h>
#endif

void send_msg(const char *s)
{
#ifndef LIBOPENCM3
    std::cout << s;
#else
    uart_send(s, strlen(s));
#endif
}

void test_start(const char *s)
{
    std::array<char, 500> ss{};
    snprintf(ss.begin(), 200, "%s start\n", s);
    send_msg(ss.begin());
}

void test_done(const char *s)
{
    std::array<char, 500> ss{};
    snprintf(ss.begin(), 200, "%s done\n", s);
    send_msg(ss.begin());
}
