//
// Created by cx9ps3 on 14.07.2023.
//

#ifndef HEXENEDITOR_DETAILS_H
#define HEXENEDITOR_DETAILS_H
#include <tuple>

namespace core::threading::detail
{
    // Index Tuple
    template <unsigned... Indices>
    struct IndexTuple
    {
        template <unsigned N>
        using append = IndexTuple<Indices..., N>;
    };

    template <unsigned Size>
    struct MakeIndexTuple
    {
        using type = typename MakeIndexTuple<Size - 1>::type::template append<Size - 1>;
    };

    template <>
    struct MakeIndexTuple<0>
    {
        using type = IndexTuple<>;
    };

    template<typename... Types>
    using ToIndexTuple = typename MakeIndexTuple<sizeof...(Types)>::type;

    // Apply
    template <typename Function, typename Tuple, unsigned... I>
    auto applyImplementation(Function func, Tuple&& tuple, IndexTuple<I...>)
    {
        return func(std::get<I>(tuple)...);
    }

    template <typename Function, typename... Args>
    auto apply(Function func, std::tuple<Args...> args, typename std::enable_if<!std::is_member_function_pointer<Function>::value>::type* = 0)
    {
        using indices = ToIndexTuple<Args...>;
        return applyImplementation(func, args, indices());
    }

    // Apply (Member functions)
    template <typename Class, typename Function, typename Tuple, unsigned... I>
    auto applyImplementation(Class* inst, Function func, Tuple&& tuple, index_tuple<I...>)
    {
        return (inst->*func)(std::get<I>(tuple)...);
    }

    template <typename Class, typename Function, typename... Args>
    auto apply(Class* inst, Function func, std::tuple<Args...> args)
    {
        using indices = ToIndexTuple<Args...>;
        return applyImplementation(inst, func, args, indices());
    }

    // is_callable
    template <typename T>
    struct IsCallable
    {
    private:
        using TrueType = char;
        using FalseType = long;

        template <typename X>
        static TrueType testType( decltype(&X::operator()) );

        template <typename X>
        static FalseType testType(...);

    public:
        static constexpr bool value = sizeof(testType<T>(0)) == sizeof(TrueType);
    };

    template <typename T>
    struct IsCallable<T*>
    {
        static constexpr bool value = IsCallable<T>::value;
    };

    template <typename Ret, typename... Args>
    struct IsCallable<Ret(*)(Args...)> : public IsCallable<Ret(Args...)>
    {
        static constexpr bool value = true;
    };

    template <class T, typename Ret, typename... Args>
    struct IsCallable<Ret(T::*)(Args...)> : public IsCallable<Ret(T*, Args...)>
    {
        static constexpr bool value = true;
    };

    template <class T, typename Ret, typename... Args>
    struct IsCallable<Ret(T::*)(Args...) const> : public IsCallable<Ret(T*, Args...)>
    {
        static constexpr bool value = true;
    };
}


#endif //HEXENEDITOR_DETAILS_H
