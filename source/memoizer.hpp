#ifndef MEMOIZER_HPP
#define MEMOIZER_HPP


#ifdef USE_CONCEPTS
#include <concepts>
#include <type_traits>
template <typename T>
concept Hashable = requires(T a)
{
    {
        std::hash<T>{}(a)
        } -> std::convertible_to<std::size_t>;
};
#endif

#include <functional>
#include "hash_tuple.hpp"
#include "function_signature.hpp"

template <auto func> // invocable
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
    Memoizer &operator=(Memoizer &&) const = default;
    Memoizer(const Memoizer &) = default;
    Memoizer &operator=(const Memoizer &) const = default;
    auto operator<=>(const Memoizer &) const = default;

    // requires size_t std::struct hash<T>::operator()(const T &x) const
    // requires bool operator==(const T&) const
    template <typename... T>
#ifdef USE_CONCEPTS
    requires(Hashable<T> &&...) && (std::equality_comparable<T> && ...)
#endif
                                       value_t
                                       operator()(T... t)
    {

        key_t tupl{key_t{t...}};
        return m_map.contains(tupl) ? m_map[tupl] : m_map[tupl] = std::invoke(func, t...);
    };

    hash_table m_map{};
}; // class Memoizer

#endif // MEMOIZER_HPP
