//
// Created by cx9ps3 on 14.07.2023.
//

#ifndef HEXENEDITOR_FUNCTIONTRAITS_H
#define HEXENEDITOR_FUNCTIONTRAITS_H
#include <tuple>
#include "../../Types.h"

namespace core::threading::detail
{
    template<typename F>
    struct FunctionTraits;

    // Function Pointer
    template <typename Ret, typename... Args>
    struct FunctionTraits<Ret(*)(Args...)> : public FunctionTraits<Ret(Args...)>
    {};

    // Member Function Pointer
    template <class T, typename Ret, typename... Args>
    struct FunctionTraits<Ret(T::*)(Args...)> : public FunctionTraits<Ret(T*, Args...)>
    {};

    template <class T, typename Ret, typename... Args>
    struct FunctionTraits<Ret(T::*)(Args...) const> : public FunctionTraits <Ret(T*, Args...)>
    {};

    template <typename F>
    struct FunctionTraits
    {
    private:
        using FuncTraits = FunctionTraits<decltype(&F::operator())>;

        template <typename T>
        struct RemoveThisArgument;

        template <typename T, typename... Args>
        struct RemoveThisArgument<std::tuple<T, Args...>>
        {
            using type = std::tuple<Args...>;
        };

    public:
        using args = typename RemoveThisArgument<typename FuncTraits::args>::type;
        using ReturnType = typename FuncTraits::ReturnType;

        static constexpr u64 NumberOfArguments = FuncTraits::NumberOfArguments - 1; // instance

        template <u64 N>
        struct Argument
        {
            static_assert(N < NumberOfArguments, "function_traits: Invalid Argument Index");
            using type = typename FuncTraits::template Argument<N + 1>::type;
        };
    };

    template<typename Ret, typename... Args>
    struct FunctionTraits<Ret(Args...)>
    {
    public:
        using args = typename std::tuple<Args...>;
        using ReturnType = Ret;

        static constexpr size_t NumberOfArguments = sizeof...(Args);

        template <u64 N>
        struct Argument
        {
            static_assert(N < NumberOfArguments, "function_traits: Invalid Argument Index");
            using type = typename std::tuple_element<N, typename std::tuple<Args...>>::type;
        };
    };
}

#endif //HEXENEDITOR_FUNCTIONTRAITS_H
