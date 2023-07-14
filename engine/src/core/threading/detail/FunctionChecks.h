//
// Created by cx9ps3 on 14.07.2023.
//

#ifndef HEXENEDITOR_FUNCTIONCHECKS_H
#define HEXENEDITOR_FUNCTIONCHECKS_H


#include <type_traits>
#include <tuple>
#include "FunctionTraits.h"

namespace core::threading::detail
{

    // Checks if T is trivial
    template <typename T>
    struct AssertTrivialType
    {
        static constexpr void check()
        {
            static_assert(std::is_trivial<T>::value, " :expected trivial type <type>");
        }
    };


    // Checks if Type matches
    //template <unsigned Index, typename Expected, typename Actual>
    //struct assert_argument_type;

    template <unsigned Index, typename Expected, typename Actual>
    struct AssertArgumentType//<Index, Expected, Actual>
    {
        static constexpr void check()
        {
            static_assert(false, ": argument type mismatch <index, expected type, actual type>");
        }
    };

    template <unsigned Index, typename T>
    struct AssertArgumentType<Index, T, T>
    {
        static constexpr void check()
        {}
    };

    // Argument Checker
    template <unsigned Index, typename TExpected, typename TActual>
    struct ArgumentChecker;

    template <unsigned Index, typename TExpected, typename... TExpectedOthers, typename TActual, typename... TActualOthers>
    struct ArgumentChecker<Index, std::tuple<TExpected, TExpectedOthers...>, std::tuple<TActual, TActualOthers...>>
    {
        static constexpr void check()
        {
            AssertArgumentType<Index, TExpected, TActual>::check();
            AssertTrivialType<TActual>::check();

            ArgumentChecker<Index + 1, std::tuple<TExpectedOthers...>, std::tuple<TActualOthers...>>::check();
        }
    };

    template <unsigned Index>
    struct ArgumentChecker<Index, std::tuple<>, std::tuple<>>
    {
        static constexpr void check()
        {}
    };

    // Argument Count Checker
    template <unsigned Expected, unsigned Actual>
    struct ArgumentCountChecker
    {
        static constexpr void check()
        {
            static_assert(Expected == Actual, ": Argument count mismatch <expected, actual>");
        }
    };

    // Callable Checker
    template <typename TCallable>
    struct CallableChecker
    {
        static constexpr void check()
        {
            static_assert(IsCallable<TCallable>::value,": Type is not callable <type>");
        }
    };

    // Function Checker (seperated into different functions as template specialization errors could occur before checks are executed)
    template <typename TCallable, typename... Args>
    struct FunctionChecker
    {
    private:
        static constexpr void checkArguments()
        {
            using func_traits = FunctionTraits<TCallable>;
            ArgumentChecker<0, typename func_traits::args, typename std::tuple<Args...>>::check();
        }

        static constexpr void checkArgumentCount()
        {
            using func_traits = FunctionTraits<TCallable>;
            ArgumentCountChecker<func_traits::num_args, sizeof...(Args)>::check();

            checkArguments();
        }

    public:
        static constexpr void check()
        {
            CallableChecker<TCallable>::check();
            checkArgumentCount();
        }
    };

    // Size Checker
    template <unsigned Actual, unsigned Maximum>
    struct DelegateSizeChecker
    {
        static constexpr void check()
        {
            static_assert(Actual <= Maximum,  ": Delegate exceeds size limit <Actual Size, Maximum Size>");
        }
    };
}

#endif //HEXENEDITOR_FUNCTIONCHECKS_H
