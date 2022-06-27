
#include <memoizer.hpp>
#include <iostream>

unsigned long long fib(unsigned long long n)
{
    static Memoizer<fib> mem_fib{};
    if (n < 2ULL)
    {
        return n;
    }

    return mem_fib(n - 2ULL) + mem_fib(n - 1ULL);
};

int main(int args, char *argv[])
{
    if (args >= 2)
    {
        std::string str{argv[1]};
        auto input_num{std::stoull(str)};

        if (input_num > 93)
        {
            std::cerr << "overflow\n";
            return -1;
        }
        std::cout << "fib of " << input_num << " is " << fib(input_num) << '\n';
    }
    else
    {
        std::cerr << "on input given";
    }
};