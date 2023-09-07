//
// Created by cx9ps3 on 09.05.2023.
//

#pragma once

#include "../Types.hpp"
#include "MemoryPool.hpp"
#include <memory>
namespace hexen::engine::core::memory
{
    class AllocatedObject
    {
    public:

        /**
        * @class core::mem::AllocatedObject
        *
        * @brief The `AllocatedObject` class provides the `operator delete` function used
        *        for deallocating memory of objects allocated using `operator new`.
        *        This function is part of the core memory management module.
        *
        * This class defines the `operator delete` which is used to deallocate memory
        * for objects of classes derived from `AllocatedObject`.
        *
        * @note This operator should only be used to deallocate memory for objects allocated
        *       using `operator new`.
        *
        * @remarks
        * - Memory that was not allocated with `operator new` should not be deallocated
        *   using this operator.
        * - This operator should not be used to delete arrays. Use `operator delete[]`
        *   for arrays allocated with `operator new[]`.
        * - Overriding this operator for a derived class allows custom deallocation of
        *   memory for the objects of that class.
        *
        * @param address The pointer to the memory block to deallocate.
        *
        * @return None. Memory is deallocated implicitly.
        *
        * @remark This function does not throw any exceptions and is guaranteed to be noexcept.
        */

        void operator delete(vptr address) noexcept;
        vptr operator new(u64 size);

        /**
        * @class AllocatedObject
        * @brief Represents an allocated memory object.
        *
        * AllocatedObject is a base class that is used to represent
        * objects allocated in memory. It provides constructor and
        * destructor functions to manage the lifetime of the object.
        */

        AllocatedObject();
        virtual ~AllocatedObject() = default;
        AllocatedObject(const AllocatedObject &allocationManager) = default;
        AllocatedObject(AllocatedObject &&allocationManager) = default;

        AllocatedObject& operator=(const AllocatedObject &allocationManager) = default;
        AllocatedObject& operator=(AllocatedObject &&allocationManager) = default;



    private:
        static constexpr u64 POOL_SIZE = 8128;
        static std::unique_ptr<MemoryPool> memoryPool;
    };

    /**
     * @brief Creates a unique_ptr object that owns and manages the provided object.
     *
     * This function is similar to the std::make_unique function introduced in C++14,
     * but it is compatible with older C++ standards (C++11 and C++98).
     *
     * @tparam T      The type of the object to be created.
     * @tparam Ts     The types of the arguments to be passed to the constructor of the object.
     * @param params  The arguments to be passed to the constructor of the object.
     * @return        A unique_ptr object that owns the newly created object.
     *
     * @note This function should be used when a unique_ptr needs to be created for an object,
     *       in order to ensure that the memory is properly managed.
     *
     * @note This function is only available in C++11 and later versions.
     *
     * @warning The provided object should be allocated on the heap using the new operator,
     *          in order to ensure correct memory management.
     *
     * @example
     *     // Example usage:
     *
     *     struct MyStruct {
     *         int value;
     *         MyStruct(int value) : value(value) {}
     *     };
     *
     *     auto ptr = make_unique<MyStruct>(42);
     *
     *     // The pointer is automatically deallocated when it goes out of scope.
     *     // No manual memory deallocation is required.
     */

    template<class T, class... Ts>
    inline auto make_unique(Ts&&... params)
    {
        return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
    }

    /**
     * @brief Creates a std::shared_ptr object using variadic template arguments.
     *
     * This function creates a std::shared_ptr object that manages ownership of a dynamically allocated object.
     * It provides a convenient way to create shared pointers to objects by forwarding the given arguments to the constructor of the object.
     * The object is created using the perfect forwarding technique, which preserves the value category (lvalue or rvalue) of the original arguments.
     *
     * @tparam Ts          The types of the arguments being passed to the constructor.
     * @param params       The arguments being passed to the constructor.
     * @return std::shared_ptr<T>  A std::shared_ptr object pointing to the dynamically allocated object.
     *
     * @note This function uses std::make_shared internally to create the shared pointer.
     * @note This function can be used with any type that has a constructor compatible with the given arguments.
     * @note The object created by this function will be allocated using the default allocator.
     * @note When using this function, the ownership of the dynamically allocated object is transferred to the created std::shared_ptr.
     *       Ensure that the created shared pointer is properly managed to prevent memory leaks.
     *
     * Usage example:
     * @code{.cpp}
     *   struct MyClass {
     *     int value;
     *     MyClass(int val) : value(val) {}
     *   };
     *
     *   // Creating a shared pointer to MyClass
     *   auto shared = make_shared<MyClass>(42);
     * @endcode
     */

    template<class T, class... Ts>
    inline auto make_shared(Ts&&... params)
    {
        return std::shared_ptr<T>(new T(std::forward<Ts>(params)...));
    }
}
