#include <gtest/gtest.h>
#include "../source/memoizer.hpp"
#include "test.hpp"

using namespace std;

#ifdef BE_VERBOSE
#define VERBOSE(expr) expr
#else
#define VERBOSE(expr)
#endif // BE_VERBOSE

TEST(memoizer, test_test)
{
    EXPECT_FALSE(false);
    EXPECT_TRUE(true);
}

unsigned long long fib(unsigned long long n)
{
    static Memoizer<fib> mem_fib{};
    if (n < 2ULL)
    {
        return n;
    }

    return mem_fib(n - 2ULL) + mem_fib(n - 1ULL);
};

TEST(with_functions, recurse_fib)
{
    for (int end{std::size(g_fib_input) - 1}; end >= 0; --end)
    {
        auto target{g_fib_input[end]};
        auto res{fib(target.n)};
        ASSERT_EQ(res, target.res);
    };
}
#if 0

TEST(with_lambda,basic)
{

   Memoizer<[](int i){return 213;}> mem_fib{};
   mem_fib(123);
   mem_fib(124);
     
};
#endif
TEST(with_method, hashable_comparable)
{

    test_obj equal_to_2{124};
    test_obj equal_to_1{124};
    test_obj unique_hash{555};
     
};

TEST(with_static_method, hashable_noncomparable){

};
TEST(with_static_method, nonhashable_comparable){

};