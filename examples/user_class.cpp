#include <memoizer.hpp>
#include <iostream>

struct MyClass
{
    void MyMethod(){}; //   overload for ambiguity
    int MyMethod(int i) const
    {
        static unsigned count{};
        ++count;
        std::cout << "MyClass::MyMethod called " << count << "th time, with value " << i << "\n";
        return i + 123;
    }

    bool operator==(const MyClass &) const { return true; };
};

namespace std
{
    template <>
    struct hash<MyClass>
    {
        size_t operator()(const MyClass &x) const
        {
            return 0;
        }
    };
}

int main()
{
    MyClass s{};
    Memoizer<static_cast<int (MyClass::*)(int) const>(&MyClass::MyMethod)> mem{}; // pass MyMethodtion (cast,if ambiguite)
    mem(s, 13);                                                                   // prints
    mem(s, 13);                                                                   // uses cache
    mem(s, 745);                                                                  // prints

    // output:
    // MyClass::MyMethod called  1th time, with value 13
    // MyClass::MyMethod called  2th time, with value 745
}