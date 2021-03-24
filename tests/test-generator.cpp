#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

//#define MINMAX

//#define FLT_CONV

#define CONV_CTOR

#ifdef MINMAX
std::vector<std::string> s8;
std::vector<std::string> s16;
std::vector<std::string> s32;
std::vector<std::string> s64;

void produce_tests_minmax()
{
    for (int i = 1; i < 64; ++i)
    {
        for (int j = 1; j < 64; ++j)
        {
            if ((i + j) > 64)
            {
                continue;
            }
            std::stringstream s;
            s << "CHECK_MIN(" << i << " ," << j << ");\n";
            if ((i + j) <= 8)
            {
                s8.emplace_back(s.str());
            }
            else if ((i + j) <= 16)
            {
                s16.emplace_back(s.str());
            }
            else if ((i + j) <= 32)
            {
                s32.emplace_back(s.str());
            }
            else if ((i + j) <= 64)
            {
                s64.emplace_back(s.str());
            }
        }
    }
}

void print_tests_minmax(const std::vector<std::string> &s)
{
    for (const auto &e : s) { std::cout << e; }
}

#endif

#ifdef FLT_CONV
std::vector<std::string> s;

void produce_tests()
{
    for (int i = 1; i < 64; ++i)
    {
        for (int j = 1; j < 64; ++j)
        {
            if ((i + j) > 64)
            {
                continue;
            }
            std::stringstream ss;
            ss << "CHECK_CONV(" << i << " ," << j << ");\n";
            s.emplace_back(ss.str());
        }
    }
}

void print_tests()
{
    for (auto i = s.begin(); i != s.end(); ++i)
    {
        auto dist = std::distance(s.begin(), i);
        if (!(dist % 128))
        {
            if (dist != 0)
            {
                std::cout << "}\n\n";
            }
            std::cout << "TEST(floatConversion,floatConversion" << dist / 128
                      << ")\n{\n";
        }
        std::cout << *i;
    }
    std::cout << "}\n\n";
}

#endif

#ifdef CONV_CTOR
std::vector<std::string> s;

void produce_tests()
{
    for (int i = 1; i < 64; ++i)
    {
        for (int j = 1; j < 64; ++j)
        {
            if ((i + j) > 63)
            {
                continue;
            }
            std::stringstream ss;
            ss << "CONV_SIZE(" << i << ", " << j << ");\n";
            s.emplace_back(ss.str());
        }
    }
}

void print_tests()
{
    for (auto i = s.begin(); i != s.end(); ++i)
    {
        auto dist = std::distance(s.begin(), i);
        if (!(dist % 128))
        {
            if (dist != 0)
            {
                std::cout << "}\n\n";
            }
            std::cout << "TEST(conversion,size" << dist / 128 << ")\n{\n";
        }
        std::cout << *i;
    }
    std::cout << "}\n\n";
}
#endif

int main()
{
#ifdef MINMAX
    produce_tests_minmax();

    std::cout << "TEST(limits,min8)\n{\n";
    print_tests_minmax(s8);
    std::cout << "}\n\n";

    std::cout << "TEST(limits,min16)\n{\n";
    print_tests_minmax(s16);
    std::cout << "}\n\n";

    std::cout << "TEST(limits,min32)\n{\n";
    print_tests_minmax(s32);
    std::cout << "}\n\n";

    std::cout << "TEST(limits,min64)\n{\n";
    print_tests_minmax(s64);
    std::cout << "}\n\n";
#endif

#if defined(FLT_CONV) || defined(CONV_CTOR)
    produce_tests();
    print_tests();
#endif

    return 0;
}
