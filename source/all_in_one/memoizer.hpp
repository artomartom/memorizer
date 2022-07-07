#ifndef MEMOIZER_HPP
#define MEMOIZER_HPP

#include <functional>
#include <unordered_map>
#include <tuple>

namespace std
{
    namespace
    {

        // Code from boost
        // Reciprocal of the golden ratio helps spread entropy
        //     and handles duplicates.
        // See Mike Seymour in magic-numbers-in-boosthash-combine:
        //     http://stackoverflow.com/questions/4948780

        template <class T>
        inline void hash_combine(std::size_t &seed, T const &v)
        {
            seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        // Recursive template code derived from Matthieu M.
        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
        struct HashValueImpl
        {
            static void apply(size_t &seed, Tuple const &tuple)
            {
                HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
                hash_combine(seed, std::get<Index>(tuple));
            }
        };

        template <class Tuple>
        struct HashValueImpl<Tuple, 0>
        {
            static void apply(size_t &seed, Tuple const &tuple)
            {
                hash_combine(seed, std::get<0>(tuple));
            }
        };
    }

    template <typename... TT>
    struct hash<std::tuple<TT...>>
    {
        size_t
        operator()(std::tuple<TT...> const &tt) const
        {
            size_t seed = 0;
            HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
            return seed;
        }
    };
}

template <typename Sig>
struct function_signature;

template <typename R, typename... Args>
struct function_signature<R (*)(Args...)>
{
    using return_t = R;
    using args_t = std::tuple<Args...>;
};

template <typename R, typename C, typename... Args>
struct function_signature<R (C::*)(Args...)>
{
    using type = R;
    using args_t = std::tuple<C, Args...>;
};

template <typename R, typename C, typename... Args>
struct function_signature<R (C::*)(Args...) const>
{
    using return_t = R;
    using args_t = std::tuple<C, Args...>;
};

template <typename R, typename C, typename... Args>
struct function_signature<R (C::*)(Args...) volatile>
{
    using return_t = R;
    using args_t = std::tuple<C, Args...>;
};

template <typename R, typename C, typename... Args>
struct function_signature<R (C::*)(Args...) const volatile>
{
    using return_t = R;
    using args_t = std::tuple<C, Args...>;
};

template <typename T>
using function_return_t = typename function_signature<T>::return_t;
template <typename T>
using function_args_as_tuple_t = typename function_signature<T>::args_t;

template <auto func> // TODO: use  invocable
class Memoizer
{

    using func_t = decltype(func);
    using value_t = function_return_t<func_t>;
    using key_t = function_args_as_tuple_t<func_t>;
    using hash_table = std::unordered_map<key_t, value_t>;

public:
    Memoizer() = default;
    ~Memoizer() = default;
    Memoizer(Memoizer &&) = default;
    Memoizer &operator=(Memoizer &&) = default;
    Memoizer(const Memoizer &) = default;
    Memoizer &operator=(const Memoizer &) = default;

    // requires size_t std::struct hash<T>::operator()(const T &x) const
    // requires bool operator==(const T&) const

    template <typename... T>
    value_t operator()(T &&...t)
    {

        key_t tupl{key_t{std::forward<T>(t)...}};
        auto value{m_map.find(tupl)};
        return (value != m_map.end()) ? (*value).second : m_map[tupl] = std::invoke(func, std::forward<T>(t)...);
    };

    hash_table m_map{};
}; // class Memoizer

#endif // MEMOIZER_HPP