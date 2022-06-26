#ifndef FUNCTION_SIGNATURE_HPP
#define FUNCTION_SIGNATURE_HPP

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

#endif // FUNCTION_SIGNATURE_HPP