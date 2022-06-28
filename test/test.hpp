struct
{
    unsigned long long n, res;
} g_fib_input[]{
    {0ULL, 0ULL},
    {1ULL, 1ULL},
    {2ULL, 1ULL},
    {3ULL, 2ULL},
    {4ULL, 3ULL},
    {5ULL, 5ULL},
    {6ULL, 8ULL},
    {7ULL, 13ULL},
    {8ULL, 21ULL},
    {9ULL, 34ULL},
    {10ULL, 55ULL},
    {11ULL, 89ULL},
    {12ULL, 144ULL},
    {13ULL, 233ULL},
    {14ULL, 377ULL},
    {15ULL, 610ULL},
    {16ULL, 987ULL},
    {17ULL, 1597ULL},
    {18ULL, 2584ULL},
    {19ULL, 4181ULL},
    {20ULL, 6765ULL},
    {21ULL, 10946ULL},
    {22ULL, 17711ULL},
    {23ULL, 28657ULL},
    {24ULL, 46368ULL},
    {25ULL, 75025ULL},
    {26ULL, 121393ULL},
    {27ULL, 196418ULL},
    {28ULL, 317811ULL},
    {29ULL, 514229ULL},
    {30ULL, 832040ULL},
    {31ULL, 1346269ULL},
    {32ULL, 2178309ULL},
    {33ULL, 3524578ULL},
    {34ULL, 5702887ULL},
    {35ULL, 9227465ULL},
    {36ULL, 14930352ULL},
    {37ULL, 24157817ULL},
    {38ULL, 39088169ULL},
    {39ULL, 63245986ULL},
    {40ULL, 102334155ULL},
    {41ULL, 165580141ULL},
    {42ULL, 267914296ULL},
    {43ULL, 433494437ULL},
    {44ULL, 701408733ULL},
    {45ULL, 1134903170ULL},
    {46ULL, 1836311903ULL},
    {47ULL, 2971215073ULL},
    {48ULL, 4807526976ULL},
    {49ULL, 7778742049ULL},
    {50ULL, 12586269025ULL},
    {51ULL, 20365011074ULL},
    {52ULL, 32951280099ULL},
    {53ULL, 53316291173ULL},
    {54ULL, 86267571272ULL},
    {55ULL, 139583862445ULL},
    {56ULL, 225851433717ULL},
    {57ULL, 365435296162ULL},
    {58ULL, 591286729879ULL},
    {59ULL, 956722026041ULL},
    {60ULL, 1548008755920ULL},
    {61ULL, 2504730781961ULL},
    {62ULL, 4052739537881ULL},
    {63ULL, 6557470319842ULL},
    {64ULL, 10610209857723ULL},
    {65ULL, 17167680177565ULL},
    {66ULL, 27777890035288ULL},
    {67ULL, 44945570212853ULL},
    {68ULL, 72723460248141ULL},
    {69ULL, 117669030460994ULL},
    {70ULL, 190392490709135ULL},
    {71ULL, 308061521170129ULL},
    {72ULL, 498454011879264ULL},
    {73ULL, 806515533049393ULL},
    {74ULL, 1304969544928657ULL},
    {75ULL, 2111485077978050ULL},
    {76ULL, 3416454622906707ULL},
    {77ULL, 5527939700884757ULL},
    {78ULL, 8944394323791464ULL},
    {79ULL, 14472334024676221ULL},
    {80ULL, 23416728348467685ULL},
    {81ULL, 37889062373143906ULL},
    {82ULL, 61305790721611591ULL},
    {83ULL, 99194853094755497ULL},
    {84ULL, 160500643816367088ULL},
    {85ULL, 259695496911122585ULL},
    {86ULL, 420196140727489673ULL},
    {87ULL, 679891637638612258ULL},
    {88ULL, 1100087778366101931ULL},
    {89ULL, 1779979416004714189ULL},
    {90ULL, 2880067194370816120ULL},
    {91ULL, 4660046610375530309ULL},
    {92ULL, 7540113804746346429ULL},
    {93ULL, 12200160415121876738ULL}
    // MAX == 18446744073709551615ULL

};

#define MAKE_HASHABLE(class_name, body)  namespace std {  \
    template <>                                           \
    struct hash<class_name>                               \
    {                                                     \
        size_t operator()(const class_name &obj) const body \
    };                                                    \
} 
#define MAKE_TRIVIALLY_HASHABLE(class_name)  MAKE_HASHABLE(class_name, { return 0; })
struct test_obj
{

    const char *test_obj_method_overload(int i) const {return "test_obj_const_overload_method_with_int";};
    const char *test_obj_method_overload() const {return "test_obj_const_overload_method";};

    const char *test_obj_method_overload(int i){return "test_obj_overload_method_with_int";};
    const char *test_obj_method_overload(){return "test_obj_overload_method";};

    inline static const char *s_method() { return "inline static method "; };
    constexpr static const char *constexpr_method() { return "constexpr static method "; };

    bool operator==(const test_obj &) const { return true; };

    size_t m_hash{};
};

MAKE_HASHABLE(test_obj, { return obj.m_hash; });

struct test_obj_non_hashable
{
    bool operator==(const test_obj &) const { return true; };
    inline static const char *s_method() { return "inline static method "; };
};

struct test_obj_non_comparable
{
    static constexpr const char *constexpr_method() { return "consexpt static method "; };
};
MAKE_TRIVIALLY_HASHABLE(test_obj_non_comparable);
