#include <gtest/gtest.h>
#include "../source/memoizer.hpp"

using namespace std;

#ifndef BE_VERBOSE
#define VERBOSE(expr) expr
#else
#define VERBOSE(expr)
#endif // BE_VERBOSE

TEST(memoizer, test_test)
{
    EXPECT_FALSE(false);
    EXPECT_TRUE(true);
}

struct test_dummy
{
    void func(){}; //   overload for ambiguity
    int func(int i) const
    {
        static unsigned count{};
        ++count;
        VERBOSE(cout << "test_dummy::func called " << count << "th time, with value " << i << "\n");
        return i + 123;
    }

    bool operator==(const test_dummy &) const { return true; };
};
namespace std
{
    template <>
    struct hash<test_dummy>
    {
        size_t operator()(const test_dummy &x) const
        {
            return 0;
        }
    };
}
TEST(memoizer, member_function_call)
{
    test_dummy s{};
    Memoizer<static_cast<int (test_dummy::*)(int) const>(&test_dummy::func)> mem{}; // pass function (cast,if ambiguite)
    mem(s, 13);                                                                     // prints test_dummy::func called  1th time, with value 13";
    mem(s, 13);                                                                     // uses cache
    mem(s, 745);                                                                    // prints test_dummy::func called  2th time, with value 745";
}

int fib(int n)
{
    static Memoizer<fib> mem_fib{};
    static unsigned count{};
    ++count;
    if (n < 2)
    {
        return n;
    }

    return mem_fib(n - 2) + mem_fib(n - 1);
};

TEST(memoizer, fib)
{

    int fib_number{200};

    fib(fib_number);

    // ASSERT_EQ(expected_iterations, 0);
}
