//
// Created by cx9ps3 on 09.05.2023.
//

#pragma once

#include <any>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>
// Determine the OS
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
	#define HEXEN_OS_WINDOWS
#elif defined(__APPLE__)
	#define HEXEN_OS_APPLE
	#include "TargetConditionals.h"

	#if defined(TARGET_OS_MAC)
		#define HEXEN_OS_MAC
	#elif defined(TARGET_OS_IPHONE)
		#define HEXEN_OS_iOS
	#else
		#error Unknown Apple platform
	#endif
#elif defined(__linux__) || defined(__ANDROID__)
	#define HEXEN_OS_LINUX
#endif
#if defined(__GNUC__) || defined(__GNUG__)
	#define HEXEN_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
	#define HEXEN_INLINE inline __forceinline
#else
	#define HEXEN_INLINE inline
#endif
#include "../profiling/Profiling.hpp"

namespace hexen::engine::core
{
	/// @brief hardware integer of size 8 bits (alias for int8_t).
	using i8 = int8_t;

	/// @brief hardware integer of size 16 bits (alias for int16_t).
	using i16 = int16_t;

	/// @brief hardware integer of size 32 bits (alias for int32_t).
	using i32 = int32_t;

	/// @brief hardware integer of size 64 bits (alias for int64_t).
	using i64 = int64_t;


	/// @brief unsigned integer of size 8 bits (alias for uint8_t).
	using u8 = uint8_t;

	/// @brief unsigned integer of size 16 bits (alias for uint16_t).
	using u16 = uint16_t;

	/// @brief unsigned integer of size 32 bits (alias for uint32_t).
	using u32 = uint32_t;

	/// @brief unsigned integer of size 64 bits (alias for uint64_t).
	using u64 = uint64_t;

	/// @brief pointer to void (alias for void*).
	using vptr = void *;

	using size = size_t;

	static const auto ENGINE_VERSION = std::string("1.0");

#if defined(__ANDROID__)
	static const auto HOME_DIRECTORY = std::filesystem::path(getenv("EXTERNAL_STORAGE"));
#else
	//home directory for another os is folder with executable,this const used for settings files,i dont want clog users pc with saving engine files in many places.
	static const auto HOME_DIRECTORY = std::filesystem::current_path();
#endif

#define HEXEN_EXPAND(s) s
#define HEXEN_STR_IMPL(s) #s
#define HEXEN_STR(s) HEXEN_EXPAND(HEXEN_STR_IMPL(s))
#ifndef NDEBUG
	#define HEXEN_ASSERT(expression, message)                                                             \
		if (!(expression))                                                                                \
		{                                                                                                 \
			std::cerr << "Assertion Failure: " << HEXEN_STR(expression) << ". Expr: " << message << "\n"; \
			std::cerr << "Source File: " << __FILE__ << ":" << HEXEN_STR(__LINE__) << "\n";               \
			std::abort();                                                                                 \
		}


#else
	#define HEXEN_ASSERT(msg, expr)
#endif
#if defined(__unix__)
	const std::string PATH_SLASH("/");
#elif defined(HEXEN_OS_WINDOWS)
	const std::string PATH_SLASH("\\");
#endif

	struct Color
	{
		u8 r;
		u8 g;
		u8 b;
		u8 a;
	};

	/// Polynomial used for CRC32 calculation.
	constexpr core::u32 polynomial = 0xEDB88320;

	/// HASHING_ROUNDS represents the number of rounds to hash.
	constexpr core::u32 HASHING_ROUNDS = 32;


	/**
 	* @brief This function computes the CRC32 (Cyclic Redundancy Check).
 	*
 	* It uses the polynomial defined earlier. The function is inline for optimization.
 	*
 	* @param data The input data for which to compute the checksum.
 	* @param length The length of the input data.
 	* @param previousCRC The previous CRC value, if any (default is 0).
 	* @return The computed CRC32 value from the given data.
 	*/

	HEXEN_INLINE core::u32 crc32(const core::u8 *data, core::u32 lenght, core::u32 previousCRC = 0)
	{
		HEXEN_ADD_TO_PROFILE();
		core::u32 crc = ~previousCRC;
		while (lenght-- != 0)
		{
			crc ^= *data++;
			for (int i = 0; i < 8; i++)
			{
				crc = (crc >> 1) ^ (-core::u32(crc & 1) & polynomial);
			}
		}
		return ~crc;
	}

	/**
 	* @brief This function creates a hash string using the CRC32 function.
 	*
 	* It uses the HASHING_ROUNDS constant for the number of rounds to hash.
 	*
 	* @param s The string to hash.
 	* @return The CRC32 hashed value of the input string.
 	*/

	HEXEN_INLINE core::u32 hashString(const std::string &s)
	{
		HEXEN_ADD_TO_PROFILE();
		core::u32 hash {0};
		for (core::u32 i {0}; i < HASHING_ROUNDS; i++)
		{
			hash = crc32((core::u8 *) s.c_str(), s.size(), hash);
		}
		return hash;
	}

	/**
 	* @class BaseDelegate
 	* @brief This is a base class for delegate templates.
 	* @tparam Args Template parameters, the argument types for this delegate.
 	*/

	template<typename... Args>
	class BaseDelegate
	{
	protected:
		std::tuple<Args...> parameters;

	public:
		/**
     	* @brief BaseDelegate constructor
     	* @param args The arguments for the delegate.
     	*/

		explicit BaseDelegate(Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			parameters = std::make_tuple(args...);
		}

		/**
     	* @brief Execute method which is meant to be overridden.
     	*/

		virtual void execute() = 0;

		/**
     	* @brief getId method which is meant to be overridden.
     	* @return the ID of the delegate.
     	*/

		[[nodiscard]] virtual std::size_t getId() const = 0;

		/**
     	* @brief Default destructor
     	*/

		virtual ~BaseDelegate() = default;
	};

	/**
 	* @class MethodDelegate
 	* @brief This is a delegate class for methods.
 	* @tparam T The type of the class where the method resides.
 	* @tparam Ret The return type of the method this delegate represents.
 	* @tparam Args The argument types for the method this delegate represents.
 	*/

	template<class T, typename Ret, typename... Args>
	class MethodDelegate : public BaseDelegate<Args...>
	{
	private:
		/**
     	* @brief Instance of the method this delegate represents.
     	*/

		Ret (T::*callableMethod)(Args...);

		/**
     	* @brief Instance of the method this delegate represents.
     	*/

		T *callableObject;

		/**
     	* @brief Process sequence
     	* @tparam I
     	* @param indexSequence
     	*/

		template<typename std::size_t... I>
		void process(std::index_sequence<I...> indexSequence)
		{
			HEXEN_ADD_TO_PROFILE();
			(callableObject->*callableMethod)(std::get<I>(this->parameters)...);
		}

	public:
		/**
     	* @brief MethodDelegate constructor
     	* @param object The object that method is associated with.
     	* @param method The method function pointer.
     	* @param args The arguments for the delegate method.
     	*/

		explicit MethodDelegate(T *object, Ret (T::*method)(Args...), Args... args) : BaseDelegate<Args...>(args...)
		{
			HEXEN_ADD_TO_PROFILE();
			callableMethod = method;
			callableObject = object;
		}

		/**
     	* @brief Execute the delegate
     	*/

		void execute() override
		{
			HEXEN_ADD_TO_PROFILE();
			process(std::make_index_sequence<std::tuple_size<decltype(this->parameters)>::value>());
		}

		/**
     	* @brief Get the method's unique id
     	* @return The method delegate's ID
     	*/

		[[nodiscard]] std::size_t getId() const override
		{
			HEXEN_ADD_TO_PROFILE();
			std::any object = callableMethod;
			return object.type().hash_code();
		}
	};

	/**
 	* @class FunctionDelegate
 	* @tparam Ret The return type of the callable function.
 	* @tparam Args The types of the arguments the callable function takes.
 	* @extends BaseDelegate<Args...>
 	* @brief A delegate class to hold and call a function with specified arguments.
 	*/

	template<typename Ret, typename... Args>
	class FunctionDelegate : public BaseDelegate<Args...>
	{
	private:
		/** @brief The callable function this delegate holds. */
		Ret (*callableFunction)(Args...);

	public:
		/**
     	* @brief Constructor taking a callable function and its arguments to initialize this delegate.
     	* @param function The function this delegate should hold.
     	* @param args The arguments to the function.
     	*/

		explicit FunctionDelegate(Ret (*function)(Args...), Args... args) : BaseDelegate<Args...>(args...)
		{
			HEXEN_ADD_TO_PROFILE();
			callableFunction = function;
		}

		/**
     	* @brief Executes the held function with the stored arguments.
     	*/

		void execute() override
		{
			HEXEN_ADD_TO_PROFILE();
			std::apply(callableFunction, this->parameters);
		}

		/**
     	* @brief Computes the unique hash code of the held callable function.
     	* @return The hash code as a size_t value.
     	* @note The returned id is not predictable and may change between different executions
     	*       and platforms.
     	*/

		[[nodiscard]] std::size_t getId() const override
		{
			HEXEN_ADD_TO_PROFILE();
			std::any object = callableFunction;
			return object.type().hash_code();
		}
	};

	/**
 	* @class FunctionalDelegate
 	* @brief Encapsulates a callable function and its associated arguments, allowing for delayed or repeated execution.
 	*
 	* This class provides a mechanism for storing a function with its arguments and executing it at a later time.
 	* It inherits from BaseDelegate, which offers base functionality for managing arguments.
 	*
 	* @tparam Args... The types of the arguments to be stored and passed to the function.
 	*/

	template<typename... Args>
	class FunctionalDelegate : BaseDelegate<Args...>
	{
	private:

		/**
     	* brief The stored function object.
     	*/
		std::function<void(Args...)> function;

	public:

		/**
     	* @brief Constructs a FunctionalDelegate with the given function and arguments.
     	*
     	* @param newFunction The callable function to store.
     	* @param args The arguments to pass to the function when executed.
     	*/

		explicit FunctionalDelegate(std::function<void(Args...)> &&newFunction, Args... args) : BaseDelegate<Args...>(args...), function(std::forward<std::function<void(Args...)>>(newFunction))
		{
			HEXEN_ADD_TO_PROFILE();
		}

		/**
     	* @brief Executes the stored function with the provided arguments.
     	*/

		void execute() override
		{
			HEXEN_ADD_TO_PROFILE();
			std::apply(function, this->parameters);
		}

		/**
     	* @brief Computes a unique hash code for the stored function.
     	*
     	* @note The returned ID might not be stable across different executions or platforms.
     	*
     	* @return The hash code as a size_t value.
     	*/

		[[nodiscard]] std::size_t getId() const override
		{
			HEXEN_ADD_TO_PROFILE();
			std::any object = function;
			return object.type().hash_code();
		}
	};

	/**
 	* @class FunctorDelegate
 	* @tparam T The type of the functor to be stored in the delegate.
 	* @tparam Args The types of the arguments the functor takes.
 	* @extends BaseDelegate<Args...>
 	* @brief A delegate class to hold and call a functor.
 	*/

	template<class T, typename... Args>
	class FunctorDelegate : public BaseDelegate<Args...>
	{
	private:
		/** @brief The functor this delegate holds. */
		T *functor;

		/**
     	* @brief Helper method to apply the parameters to the functor.
     	* @tparam I Indices sequence.
     	* @param indexSequence An index sequence generated by std::make_index_sequence.
     	*/

		template<typename std::size_t... I>
		void process(std::index_sequence<I...> indexSequence)
		{
			HEXEN_ADD_TO_PROFILE();
			functor->operator()(std::get<I>(this->parameters)...);
		}

	public:
		/**
     	* @brief Constructor taking a functor and its arguments to initialize this delegate.
     	* @param newFunctor The functor this delegate should hold.
     	* @param args The arguments to the functor.
     	*/

		explicit FunctorDelegate(T *newFunctor, Args... args) : BaseDelegate<Args...>(args...)
		{
			HEXEN_ADD_TO_PROFILE();
			functor = newFunctor;
		}

		/**
     	* @brief Executes the held functor with the stored arguments.
     	*/

		void execute() override
		{
			HEXEN_ADD_TO_PROFILE();
			process(std::make_index_sequence<std::tuple_size<decltype(this->parameters)>::value>());
		}

		/**
     	* @brief Computes the unique hash code of the held functor.
     	* @return The hash code as a size_t value.
     	* @note The returned id is not predictable and may change between different executions
     	*       and platforms.
     	*/

		[[nodiscard]] std::size_t getId() const override
		{
			HEXEN_ADD_TO_PROFILE();
			std::any object = functor;
			return object.type().hash_code();
		}
	};

	/**
 	* A HashTable class.
 	*
 	* This is a simple HashTable implementation.
 	* It maps keys (of type Key) to values (of type Value).
 	*
 	* @tparam Key The type of the keys.
 	* @tparam Value The type of the Value.
 	* @tparam Hash The type of the function object that hashes the Key.
 	* @tparam Equal The type of the function object that compares two keys for equality.
 	*/

	//
	//
	// Created by Arpad Goretity (H2CO3)
	// on 02/06/2015
	//
	// Licensed under the 2-clause BSD License
	// some modifications by cx9p3
	// taken from https://github.com/H2CO3/hash_table/blob/master/hash_table.hh
	//


	template<typename Key, typename Value, typename Hash = std::hash<Key>, typename Equal = std::equal_to<Key>>
	class HashTable
	{
	public:
		/** @brief A structure for storing Key-Value pairs. */
		struct KeyValue
		{
			Key key;
			Value value;
		};

		using keyType = Key;
		using mappedType = Value;
		using valueType = KeyValue;
		using sizeType = std::size_t;
		using differenceType = std::ptrdiff_t;
		using hasher = Hash;
		using keyEqual = Equal;
		using reference = valueType &;
		using constReference = const valueType &;
		using pointer = valueType *;
		using constPointer = const valueType *;

	private:
		/**
 * @struct Slot
 * @brief A struct to encapsulate a key-value pair.
 *
 * @details This struct also maintains an 'isUsed' Boolean to indicate whether the Key-Value pair is in use.
 */
		struct Slot
		{
			/// @brief Represents a Key-Value pair.
			KeyValue keyValue;

			/// @brief Boolean represents whether keyValue is in use.
			bool isUsed;

			/**
	 		* @brief Default contructor which initializes Slot.
	 		*/

			Slot() noexcept : keyValue(), isUsed(false) {}

			/**
	 		* @brief Parameterized constructor which constructs Slot with given key and value.
	 		*
	 		* @param key The key for keyValue.
	 		* @param value The value for keyValue.
	 		*/

			Slot(Key key, Value value) : keyValue {std::move(key), std::move(value)}, isUsed(true) {}

			/**
     		* @brief Copy constructor.
     		*/

			Slot(const Slot &other) = default;

			/**
	 		* @brief Move constructor which moves slot into new slot.
		 	*
	 		* @param slot The slot to be moved.
	 		*/

			Slot(Slot &&slot) noexcept : keyValue(std::move(slot.keyValue)), isUsed(slot.isUsed)
			{
				HEXEN_ADD_TO_PROFILE();
				slot.isUsed = false;
			}

			/**
     		* @brief swaps contents of lhs slot and rhs slot.
     		*
     		* @param lhs Left-hand slot.
     		* @param rhs Right-hand slot.
     		*/

			friend void swap(Slot &lhs, Slot &rhs) noexcept
			{
				HEXEN_ADD_TO_PROFILE();
				using std::swap;
				swap(lhs.keyValue, rhs.keyValue);
				swap(lhs.isUsed, rhs.isUsed);
			}

			/**
     		* @brief Overloads assignment operator for Slot.
     		*
     		* @param slot Slot to be assigned.
     		* @return Current Slot.
    	 	*/

			Slot &operator=(Slot slot)
			{
				HEXEN_ADD_TO_PROFILE();

				if (&slot == this)
				{
					return *this;
				}

				swap(*this, slot);
				return *this;
			}

			/**
	 		* @brief Template function to compare key with keyValue's key.
	 		*
	 		* @param key key for comparison.
	 		* @return True if keys are equal, False otherwise.
	 		*/

			template<class T>
			bool equals(T &&key) const
			{
				HEXEN_ADD_TO_PROFILE();

				assert(isUsed);
				return Equal {}(keyValue.key, std::forward<T>(key));
			}
		};

		std::vector<Slot> slots;
		u32 count {};
		u32 maxHashOffset {};


		/**
     	* @brief A function to get the current instance of the table.
     	* @return The current instance.
     	*/

		auto cthis() const { return this; }

		/**
     	* @brief Gets the index associated with a given key.
     	* @param key The key to get the index for.
     	* @return The index.
     	*/

		template<class T>
		u32 keyIndex(T &&key) const
		{
			HEXEN_ADD_TO_PROFILE();
			return Hash {}(std::forward<T>(key)) & mask();
		}

		/**
     	* @brief Mask function used as part of hash function.
     	* Asserts that the table size is a power of two.
     	* @return The mask for the hash function.
     	*/

		[[nodiscard]] u32 mask() const noexcept
		{
			HEXEN_ADD_TO_PROFILE();
			HEXEN_ASSERT(slots.size() && !(slots.size() & (slots.size() - 1)), "table size must be a power of two");
			return slots.size() - 1;
		}

		/**
     	* @brief Determines whether the table needs to be rehashed.
     	* @return true if rehash needed, false otherwise.
     	*/

		[[nodiscard]] bool isShouldRehash() const
		{
			HEXEN_ADD_TO_PROFILE();

			// keep load factor below 0.75
			// this ratio is chosen carefully so that it can be optimized well:
			// it is equivalent with ((size << 1) + size) >> 2.
			return slots.empty() || count >= slots.size() * 3 / 4;
		}

		/**
     	* @brief Gets the slot associated with a key.
     	* @param key The key get the slot for.
     	* @return The slot associated with the given key.
     	*/

		template<class T>
		const Slot *getSlot(T &&key) const
		{
			HEXEN_ADD_TO_PROFILE();

			if (slots.empty())
			{
				return nullptr;
			}

			u32 i = keyIndex(std::forward<T>(key));
			u32 hashOffset = 0;

			// linear probing using a cached maximal probe sequence length.
			// This avoids the need to mark deleted slots as special and
			// fixes the performance problem whereby searching for a key after
			// having performed lots of deletions results in O(n) running time.
			// (maxHashOffset is one less than the length of the longest sequence.)
			do
			{
				if (slots[i].isUsed && slots[i].equals(std::forward<T>(key)))
				{
					return &slots[i];
				}

				i = (i + 1) & mask();
				hashOffset++;
			} while (hashOffset <= maxHashOffset);

			return nullptr;
		}

		/**
     	* @brief Get slot associated with a key.
     	* Non-const variant.
     	* @param key The key to search.
     	* @return The slot associated with the given key.
     	*/

		template<class T>
		Slot *getSlot(T &&key)
		{
			HEXEN_ADD_TO_PROFILE();

			return const_cast<Slot *>(cthis()->getSlot(std::forward<T>(key)));
		}

		/**
     	* @brief Insert a new key-value pair to the hash table.
     	* No rehash is done after insertion.
     	* @param key The key of the pair to insert.
     	* @param value The value of the pair to insert.
     	* @return Pointer to the inserted key-value pair.
     	*/

		template<class T, class V>
		KeyValue *insertNonexistentNoRehash(T &&key, V &&value)
		{
			HEXEN_ADD_TO_PROFILE();

			assert(isShouldRehash() == false);
			assert(size() < slots.size());
			assert(cthis()->getSlot(std::forward<T>(key)) == nullptr);

			u32 i = keyIndex(std::forward<T>(key));
			u32 hashOffset = 0;

			//find unused slot
			while (slots[i].isUsed)
			{
				i = (i + 1) & mask();
				hashOffset++;
			}

			//insert and mark used slot
			slots[i] = {std::forward<T>(key), std::forward<V>(value)};

			assert(slots[i].isUsed);

			count++;

			//update maximal length of probe sequences
			if (hashOffset > maxHashOffset)
			{
				maxHashOffset = hashOffset;
			}
			return &slots[i].keyValue;
		}

		/**
     	* @brief Rehashes the hash table if it should be rehashed.
     	*/

		void rehash()
		{
			HEXEN_ADD_TO_PROFILE();

			const u32 newSize = slots.empty() ? 8 : slots.size() * 2;

			auto oldSlots = std::move(slots);


			// language lawyer: move() need not clear std::vector.
			// this->clear() takes care of that, however
			// (as well as zeroing out count and maxHashOffset.)

			clear();

			// make room for new slots (need to default-construct
			// in order for them to be in an 'unused'/free state)
			slots.resize(newSize);

			for (auto &slot : oldSlots)
			{
				if (slot.isUsed)
				{
					insertNonexistentNoRehash(std::forward<Key>(slot.keyValue.key), std::forward<Value>(slot.keyValue.value));
				}
			}
		}

	public:
		/**
		 * @brief Default constructor
		 */

		HashTable() noexcept : slots {}, count {0}, maxHashOffset {0} {}

		/**
		 * @brief Construct HashTable with a specific initial capacity
		 *
		 * @param capacity Initial capacity
		 */

		explicit HashTable(u32 capacity) noexcept : HashTable()
		{
			HEXEN_ADD_TO_PROFILE();
			// Make sure the real capacity is a power of two >= 8.
			// We should also keep in mind that the number of elements
			// is at most 3/4 of the number of slots!
			u32 minimalNumberSlots = (capacity * 4 + 2) / 3;
			u32 realCapacity = 8;
			while (realCapacity < minimalNumberSlots)
			{
				realCapacity *= 2;
			}
			slots.resize(realCapacity);
		}


		/**
		 * @brief Copy constructor
		 *
		 * @param hashTable Another HashTable to copy
		 */

		HashTable(const HashTable &hashTable) = default;

		/**
		 * @brief Move constructor
		 *
		 * @param hashTable Another HashTable to move into this one
		 */

		HashTable(HashTable &&hashTable) noexcept : slots {std::move(hashTable.slots)}, count {hashTable.count}, maxHashOffset {hashTable.maxHashOffset}
		{
			HEXEN_ADD_TO_PROFILE();
			hashTable.clear();
		}

		/**
		 * @brief Construct from a list of key-value pairs.
		 *
		 * @param elements The initializer list.
		 */

		HashTable(std::initializer_list<KeyValue> elements) : HashTable(elements.size())
		{
			HEXEN_ADD_TO_PROFILE();

			for (auto &element : elements)
			{
				set(element.key, element.value);
			}
		}

		/**
		* @brief Function to swap the contents of two HashTable objects
		* @param lhs First HashTable object
		* @param rhs Second HashTable object
		*/

		friend void swap(HashTable &lhs, HashTable &rhs) noexcept
		{
			HEXEN_ADD_TO_PROFILE();
			using std::swap;
			swap(lhs.slots, rhs.slots);
			swap(lhs.count, rhs.count);
			swap(lhs.maxHashOffset, rhs.maxHashOffset);
		}

		/**
 		* @brief Overloaded assignment operator for the HashTable class
 		* @param hashTable HashTable object to be assigned
 		* @return A reference to the current HashTable object
 		*/

		HashTable &operator=(HashTable hashTable)
		{
			HEXEN_ADD_TO_PROFILE();
			if (&hashTable == this)
			{
				return *this;
			}

			swap(*this, hashTable);
			return *this;
		}

		/**
 		* @brief Function to clear the HashTable
 		*/

		void clear() noexcept
		{
			HEXEN_ADD_TO_PROFILE();
			slots.clear();
			count = 0;
			maxHashOffset = 0;
		}

		/**
 		* @brief Function to get a value by a key
 		* @param key The key of the value to be retrieved
 		* @return A pointer to the value if it exists, else nullptr
 		*/

		const Value *get(const Key &key) const
		{
			HEXEN_ADD_TO_PROFILE();
			if (const Slot *slot = getSlot(key))
			{
				return &slot->keyValue.value;
			}

			return nullptr;
		}

		/**
 		* @brief Function to get a value by a key
 		* @param key The key of the value to be retrieved
 		* @return A pointer to the value if it exists, else nullptr
 		*/

		Value *get(const Key &key)
		{
			HEXEN_ADD_TO_PROFILE();
			if (Slot *slot = getSlot(key))
			{
				return &slot->keyValue.value;
			}

			return nullptr;
		}

		/**
 		* @brief Function to set a key-value pair
 		* @param key The key of the value to be set
 		* @param value The value to be set
 		* @return A pointer to the value set
 		*/

		Value *set(const Key &key, Value value)
		{
			HEXEN_ADD_TO_PROFILE();
			// if the key is already in the table, just replace it and move on
			if (Value *candidate = get(key))
			{
				*candidate = std::move(value);
				return candidate;
			}

			// else we need to insert it. First, check if we need to expand.
			if (isShouldRehash())
			{
				rehash();
			}

			//insert the key
			auto keyValue = insertNonexistentNoRehash(key, std::forward<Value>(value));
			return &keyValue->value;
		}

		/**
 		* @brief Function to set a key-value pair
 		* @param key The key of the value to be set
 		* @param value The value to be set
 		* @return A pointer to the value set
 		*/

		Value *set(Key &&key, Value value)
		{
			HEXEN_ADD_TO_PROFILE();
			// if the key is already in the table, just replace it and move on
			if (Value *candidate = get(key))
			{
				*candidate = std::move(value);
				return candidate;
			}

			// else we need to insert it. First, check if we need to expand.
			if (isShouldRehash())
			{
				rehash();
			}

			//insert the key
			auto keyValue = insertNonexistentNoRehash(std::move(key), std::move(value));
			return &keyValue->value;
		}

		/**
 		* @brief Function to remove a key-value pair from the HashTable
 		* @param key The key of the value to be removed
 		*/

		void remove(const Key &key)
		{
			HEXEN_ADD_TO_PROFILE();
			if (Slot *slot = getSlot(key))
			{
				*slot = {};
				assert(slot->isUsed == false);
				count--;
			}
		}

		/**
 		* @brief Function to retrieve the size of the HashTable
 		* @return The number of elements in the HashTable
 		*/

		[[nodiscard]] u32 size() const noexcept
		{
			HEXEN_ADD_TO_PROFILE();
			return count;
		}

		/**
 		* @brief Function to check if the HashTable is empty
 		* @return True if the size of the HashTable is 0, else False
 		*/

		[[nodiscard]] bool empty() const
		{
			HEXEN_ADD_TO_PROFILE();
			return size() == 0;
		};

		/**
 		* @brief Function to calculate the load factor of the HashTable
 		* @return The load factor of the HashTable
 		*/

		[[nodiscard]] double loadFactor() const
		{
			HEXEN_ADD_TO_PROFILE();
			return double(size() / slots.size());
		}

		/**
 		* @brief Overloaded subscript operator for the HashTable class
 		* @param key The key of the value to be retrieved
 		* @return A reference to the value associated with the key
 		*/

		Value &operator[](const Key &key)
		{
			HEXEN_ADD_TO_PROFILE();
			if (Value *value = get(key))
			{
				return *value;
			}
			return *set(key, {});
		}

		/**
 		* @brief Overloaded subscript operator for the HashTable class
 		* @param key The key of the value to be retrieved
 		* @return A reference to the value associated with the key
 		*/

		Value &operator[](Key &&key)
		{
			HEXEN_ADD_TO_PROFILE();
			if (Value *value = get(key))
			{
				return *value;
			}
			return *set(std::move(key), {});
		}

		/**
 		* @brief Overloaded subscript operator for retrieving const values
 		* @param key The key of the value to be retrieved
 		* @return A reference to the value associated with the key
 		*/

		const Value &operator[](const Key &key) const
		{
			HEXEN_ADD_TO_PROFILE();
			if (const Value *value = get(key))
			{
				return *value;
			}

			std::fprintf(stderr, "hash_table::operator[] failed: key does not exist\n");
			std::fflush(stderr);
			abort();
		}

		/**
		* @struct ConstIterator
 		* @brief Class for constant iteration over a hash table.
 		*/

		struct ConstIterator
		{
		protected:
			friend class HashTable;

			const HashTable *owner {nullptr};
			u32 slotIndex {0};

			/**
		 	* @brief Constructs a ConstIterator at a specific position.
		 	* @param owner The owning hashtable.
		 	* @param slotIndex Initial slot position for the iterator.
		 	*/

			ConstIterator(const HashTable *owner, u32 slotIndex) : owner(owner), slotIndex(slotIndex) {}

		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = HashTable::KeyValue;
			using difference_type = ptrdiff_t;
			using pointer = const value_type *;
			using reference = const value_type &;

			/**
		 	* @brief Copy constructor.
		 	* @param iterator The ConstIterator to copy from.
		 	*/

			ConstIterator(const ConstIterator &iterator) = default;

			/**
		 	* @brief Overloading the pointer operator.
		 	*/

			const KeyValue *operator->() const
			{
				HEXEN_ADD_TO_PROFILE();
				HEXEN_ASSERT(slotIndex < owner->slots.size(), "cannot dereference end iterator");
				return &owner->slots[slotIndex].keyValue;
			}

			/**
		 	* @brief Overloading the dereference operator.
		 	*/

			const KeyValue &operator*() const
			{
				HEXEN_ADD_TO_PROFILE();
				return *operator->();
			}


			/**
		 	* @brief Overloading the pre-increment operator.
		 	*/

			ConstIterator &operator++()
			{
				HEXEN_ADD_TO_PROFILE();
				HEXEN_ASSERT(slotIndex < owner->slots.size(), "cannot increment end iterator");
				do
				{
					slotIndex++;
				} while (slotIndex < owner->slots.size() && !owner->slots[slotIndex].isUsed);

				return *this;
			}

			/**
		 	* @brief Overloading the post-increment operator.
		 	*/

			ConstIterator operator++(core::i32)
			{
				HEXEN_ADD_TO_PROFILE();
				auto previous(*this);
				++*this;
				return previous;
			}

			/**
		 	* @brief Overloading the equality operator.
		 	*/

			bool operator==(const ConstIterator &constIterator) const
			{
				HEXEN_ADD_TO_PROFILE();
				HEXEN_ASSERT(owner == constIterator.owner, "different iterators owners!");
				return owner == constIterator.owner && slotIndex == constIterator.slotIndex;
			}

			/**
		 	* @brief Overloading the inequality operator.
		 	*/

			bool operator!=(const ConstIterator &constIterator) const
			{
				HEXEN_ADD_TO_PROFILE();
				return !operator==(constIterator);
			}
		};

		/**
 		* @struct Iterator
 		* @brief A class that implements the Iterator pattern for the HashTable class.
 		*
 		* Iterator is a subclass of ConstIterator. It allows modification of the elements it is iterating over.
 		*/

		struct Iterator : public ConstIterator
		{

		private:
			/**
     		* @brief Declare HashTable class as friend to grant it access to the Iterator's private and protected members.
     		*/

			friend class HashTable;

			/**
     		* @brief Explicit constructor that initializes Iterator from ConstIterator.
     		* @param constIterator The ConstIterator instance to initialize the Iterator.
     		*/

			explicit Iterator(const ConstIterator &constIterator) : ConstIterator(constIterator) {}

		public:
			/**
     		* @brief Copy constructor that initializes Iterator from another Iterator.
     		* @param iterator The Iterator instance to copy from.
     		*/

			Iterator(const Iterator &iterator) : ConstIterator(iterator) {}

			/**
     		* @brief Overloading dereference operator(*) to return the current KeyValue element.
     		* @return Current KeyValue element.
     		*/

			KeyValue &operator*() const
			{
				HEXEN_ADD_TO_PROFILE();
				return *operator->();
			}

			/**
     		* @brief Overloading member access operator(->) to return a pointer to the current KeyValue element.
     		* @return Pointer to the current KeyValue element.
     		*/

			KeyValue *operator->() const
			{
				HEXEN_ADD_TO_PROFILE();
				return const_cast<KeyValue *>(static_cast<const ConstIterator *>(this)->operator->());
			}

			/**
     		* @brief Overloading increment operator++() for iterator to move to the next KeyValue element.
     		* @return Iterator pointing to the next KeyValue element.
     		*/

			Iterator &operator++()
			{
				HEXEN_ADD_TO_PROFILE();
				HEXEN_ASSERT(this->slotIndex < this->owner->slots.size(), "cannot increment end iterator");
				do
				{
					this->slotIndex++;
				} while (this->slotIndex < this->owner->slots.size() && !this->owner->slots[this->slotIndex].isUsed);
				return *this;
			}

			/**
     		* @brief Overloading post-increment operator++(int) for iterator to move to the next KeyValue element.
     		* @param An integer to differentiate it from the prefix increment operator.
     		* @return Iterator pointing to the current KeyValue element before the increment.
     		*/

			Iterator operator++(core::i32)
			{
				HEXEN_ADD_TO_PROFILE();
				auto previous(*this);
				++*this;
				return previous;
			}
		};

		/**
		 * @brief Returns a new iterator pointing to the start of the HashTable
		 *
		 * @return A ConstIterator pointing to the start of the HashTable
		 */

		ConstIterator begin() const
		{
			HEXEN_ADD_TO_PROFILE();
			auto iterator = ConstIterator(this, 0);
			while (iterator.slotIndex < slots.size() && !slots[iterator.slotIndex].isUsed)
			{
				iterator.slotIndex++;
			}
			return iterator;
		}

		/**
		 * @brief Returns a new iterator pointing to the end of the HashTable
		 *
		 * @return A ConstIterator pointing to the end of the HashTable
		 */

		ConstIterator end() const
		{
			HEXEN_ADD_TO_PROFILE();
			return ConstIterator(this, slots.size());
		}

		/**
		 * @brief Returns a new Iterator pointing to the start of the HashTable
		 *
		 * @return Iterator pointing to the start of the HashTable
		 */

		Iterator begin()
		{
			HEXEN_ADD_TO_PROFILE();
			return Iterator(cthis()->begin());
		}

		/**
		 * @brief Returns a new Iterator pointing to the end of the HashTable
		 *
		 * @return An Iterator pointing to the end of the HashTable
		 */

		Iterator end()
		{
			HEXEN_ADD_TO_PROFILE();
			return Iterator(cthis()->end());
		}

		/**
 		* @brief Constant Iterator to the beginning of the collection.
 		* This is identical to begin() but is used where the object is
 		* constant and allows for interface uniformity with non-constant objects.
 		* @return A ConstIterator pointing the beginning of the collection.
 		*/

		ConstIterator cbegin() const
		{
			HEXEN_ADD_TO_PROFILE();
			return begin();
		}

		/**
 		* @brief Constant Iterator to the end of the collection.
 		* This is identical to end() but is used where the object is
 		* constant and allows for interface uniformity with non-constant objects.
 		* @return A ConstIterator pointing to past-the-end element.
 		*/

		ConstIterator cend() const
		{
			HEXEN_ADD_TO_PROFILE();
			return end();
		}


		/**
	 	*@brief Returns an iterator to the element with key equivalent to key.
	 	*
	 	* @param key A key value of the element to search for.
	 	* @return ConstIterator to an element with key equivalent to key.
	 	* If no such element is found, past-the-end (see end()) iterator is returned.
	 	*/

		ConstIterator findConst(const Key &key) const
		{
			HEXEN_ADD_TO_PROFILE();
			if (const Slot *slot = getSlot(key))
			{
				return ConstIterator(this, slot - slots.data());
			}
			return end();
		}

		/**
		 * @brief Returns an iterator to the element with key equivalent to key.
		 *
		 * @param key A key value of the element to search for.
		 * @return Iterator to an element with key equivalent to key.
		 * If no such element is found, past-the-end (see end()) iterator is returned.
		 */

		Iterator find(const Key &key)
		{
			HEXEN_ADD_TO_PROFILE();
			return Iterator(cthis()->findConst(key));
		}

		/**
		 * @brief Erases the specified elements from the container.
		 *
		 * @param it ConstIterator to the element to be removed from the HashTable
		 */

		void erase(const ConstIterator &it)
		{
			HEXEN_ADD_TO_PROFILE();
			HEXEN_ASSERT(it.owner == this, "cannot erase an element of another instance");
			remove(it->key);
		}
	};
}// namespace hexen::engine::core
