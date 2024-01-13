//
// Created by cx9ps3 on 09.05.2023.
//

#pragma once

#include "../Types.hpp"
#include "MemoryPool.hpp"
#include <memory>

namespace hexen::engine::core::memory
{
	/**
    * @class AllocatedObject
    * @brief Represents an allocated memory object.
    *
    * AllocatedObject is a base class that is used to represent
    * objects allocated in memory. It provides constructor and
    * destructor functions to manage the lifetime of the object.
    */

	class AllocatedObject
	{
	public:
		/**
		* @brief Overloaded delete operator for the AllocaredObject class.
		* This function logs an error message if it fails to free
		* the memory pointed to by the given address.
		* If memory pool exists, it directly calls upon memory pool to free the given address.
		*
		* @param address The address of the memory space to be freed.
		*
		* @exception noexcept This function is guaranteed not to throw an exception.
		*/

		void operator delete(vptr address) noexcept;

		/**
 		* @brief Overloaded new operator for allocating memory for objects of AllocatedObject.
 		*
 		* This function is responsible for allocating memory for objects of AllocatedObject class.
 		* It is an overloaded version of the new operator that takes the size of the object as a parameter and returns a pointer to the allocated memory.
 		*
 		* @param size The size of the object to be allocated.
 		* @return A pointer to the allocated memory for the object.
 		*/

		vptr operator new(u64 size);

		/**
 		* @class AllocatedObject
 		* @namespace hexen::engine::core::memory
 		* @brief Default Constructor for the AllocatedObject class.
 		*
 		* Sets the new_handler function of the C++ Standard Library. The new_handler function
 		* is a global function that is called by the new operator when it fails to allocate storage.
 		*
 		*/

		AllocatedObject();

		/**
     	* @brief Virtual destructor for the AllocatedObject class.
     	*
     	* The destructor is declared as virtual to ensure that the destructors for derived classes are
     	* called correctly when an object is deleted through a pointer-to-base.
     	* It is defaulted because it does not have any specific implementation details.
     	*/

		virtual ~AllocatedObject() = default;

		/**
 		* @brief Copy constructor.
 		*
 		* The copy constructor is defaulted, meaning it will perform a member-wise copy of the source object.
 		*
 		* @param allocationManager The source AllocatedObject from which to create this object.
 		*/

		AllocatedObject(const AllocatedObject &allocationManager) = default;

		/**
 		* @brief Move constructor.
 		*
 		* The move constructor is defaulted, meaning it will 'steal' the resources from the source object,
 		* leaving it in a valid but unspecified state.
 		*
 		* @param allocationManager The source AllocatedObject from which to 'move' resources into this object.
 		*/

		AllocatedObject(AllocatedObject &&allocationManager) = default;

		/**
 		* @brief Copy assignment operator.
 		*
 		* The copy assignment operator is defaulted, meaning it will perform member-wise copy assignment
 		* from the source object.
 		*
 		* @param allocationManager The source AllocatedObject from which to copy.
 		* @return Returns a reference to the object that the member belongs to.
 		*/

		AllocatedObject &operator=(const AllocatedObject &allocationManager) = default;

		/**
 		* @brief Move assignment operator.
 		*
 		* The move assignment operator is defaulted, meaning it will 'steal' the resources from the source object,
 		* leaving it in a valid but unspecified state.
 		*
 		* @param allocationManager The source AllocatedObject from which to 'move' resources.
 		* @return Returns a reference to the object that the member belongs to.
 		*/

		AllocatedObject &operator=(AllocatedObject &&allocationManager) = default;


	private:
		static constexpr u64 POOL_SIZE = 208128;
		static constexpr std::string_view pathToSettings = "settings/memory.hxs";
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
	inline auto make_unique(Ts &&...params)
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
	inline auto make_shared(Ts &&...params)
	{
		return std::shared_ptr<T>(new T(std::forward<Ts>(params)...));
	}
}// namespace hexen::engine::core::memory
