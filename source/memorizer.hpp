#ifndef MEMORIZER_HPP
#define MEMORIZER_HPP


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

template <auto func> // TODO: use  invocable
class Memorizer
{

    using func_t = decltype(func);
    using value_t = function_return_t<func_t>;
    using key_t = function_args_as_tuple_t<func_t>;
    using hash_table = std::unordered_map<key_t, value_t>;

public:
    Memorizer() = default;
    ~Memorizer() = default;
    Memorizer(Memorizer &&) = default;
    Memorizer &operator=(Memorizer &&) = default;
    Memorizer(const Memorizer &) = default;
    Memorizer &operator=(const Memorizer &) = default;

    // requires size_t std::struct hash<T>::operator()(const T &x) const
    // requires bool operator==(const T&) const
    template <typename... T>
#ifdef USE_CONCEPTS
    requires(Hashable<T> &&...) && (std::equality_comparable<T> && ...)
#endif
                                       value_t
                                       operator()(T &&...t)
    {

        key_t tupl{key_t{std::forward<T>(t)...}};
        auto value{m_map.find(tupl)};
        return (value != m_map.end()) ?  (*value).second : m_map[tupl] = std::invoke(func, std::forward<T>(t)...);
    };

    hash_table m_map{};
}; // class Memorizer

#endif // MEMORIZER_HPP
