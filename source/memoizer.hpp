#ifndef MEMOIZER_HPP
#define MEMOIZER_HPP

#include <functional>
#include "hash_tuple.hpp"
#include "function_signature.hpp"


template <auto func>
class Memoizer
{
    using func_t = decltype(func);
    using value_t = function_return_t<func_t>;
    using key_t = function_args_as_tuple_t<func_t>;
    using hash_table = std::unordered_map<key_t, value_t>;

public:
    // requires size_t std::struct hash<T>::operator()(const T &x) const
    // requires bool operator==(const T&) const
    template <typename... T>
    value_t operator()(T... t)
    {
        key_t tupl{key_t{t...}};
        return m_map.contains(tupl) ? m_map[tupl] : m_map[tupl] = std::invoke(func, t...);
    };

    hash_table m_map{};
};

#endif // MEMOIZER_HPP
