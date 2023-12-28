#pragma once
#include "../../Types.hpp"
#include <memory>
#include <any>

#ifdef __ANDROID__
namespace std
{
    template<class T, class U>
    std::shared_ptr<T> reinterpret_pointer_cast(const std::shared_ptr<U>& r) noexcept
    {
        auto p = reinterpret_cast<typename std::shared_ptr<T>::element_type*>(r.get());
        return std::shared_ptr<T>{r, p};
    }
}
#endif
namespace hexen::engine::core::threading
{
	class TaskScheduler;

	/**
 	* @struct Task
	* @brief This class is used for task management.
 	*
 	* It supports binding methods and functions, overloading the comparison operators,
 	* and executing the delegate if it's not null. Delegates are stored in shared pointers
 	* with an any-type base.
 	*/

	struct Task
	{
	public:

		/**
     	* @brief Default constructor for the class.
     	*/

		Task() = default;

		/**
 		* @brief Binds a function to an object.
 		*
 		* This method is used to bind a function to an instance (object) of a class. It uses a method delegate to wrap the method call, thus allowing us to indirectly call the method using any object of the class.
 		*
 		* @tparam T    The class to which the method belongs.
 		* @tparam Ret  The return type of the method.
 		* @tparam Args The types of the arguments the method takes.
 		*
 		* @param[in] object The instance (object) of the class.
 		* @param[in] method A pointer to the method in the class.
 		* @param[in] args   The arguments to pass to the method.
 		*
 		* @returns False if the delegate could not be created or set, true otherwise.
 		*/

		template<class T, typename Ret, typename... Args>
		bool bind(T *object, Ret (T::*method)(Args...), Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			auto methodDelegate = core::memory::make_shared<core::MethodDelegate<T, Ret, Args...>>(object, method, args...);
			delegate = std::reinterpret_pointer_cast<BaseDelegate<std::any>>(methodDelegate);

			return delegate != nullptr;
		}

		/**
 		* @brief Binds a callable function and its arguments to a delegate
 		*
 		* This function takes a callable function and a variadic number of arguments,
 		* and binds them to a delegate using the `std::bind()` function from the Standard Library.
 		* It uses `std::shared_ptr` to manage the memory of the delegate, ensuring automatic cleanup.
 		*
 		* This function allows the management of a function's invocation over time, delaying its execution for later,
 		* or storing it as part of a larger operation.
 		*
 		* @tparam Ret The return type of the callable function
 		* @tparam Args The types of the arguments to the callable function
 		* @param callableFunction A function pointer to the callable function
 		* @param args The arguments to bind to the function
 		* @return true if binding is successful, false otherwise
 		*/

		template<typename Ret, typename... Args>
		bool bind(Ret (*callableFunction)(Args...), Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			auto functionDelegate = core::memory::make_shared<core::FunctionDelegate<Ret, Args...>>(callableFunction, args...);
			delegate = std::reinterpret_pointer_cast<BaseDelegate<std::any>>(functionDelegate);

			return delegate != nullptr;
		}

		/**
 		* @brief Binds a callable function and its arguments to this object.
 		*
 		* @tparam Args... The types of the arguments to be stored and passed to the function.
 		* @param function The callable function to bind.
 		* @param args The arguments to pass to the function when executed.
 		* @return True if the binding was successful, false otherwise.
 		*/

		template<typename... Args>
		bool bind(std::function<void(Args...)> &&function, Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			auto functionalDelegate = core::memory::make_shared<core::FunctionalDelegate<Args...>>(std::forward<void(Args...)>(function), std::forward<Args...>(args...));
			delegate = std::reinterpret_pointer_cast<BaseDelegate<std::any>>(functionalDelegate);

			return delegate != nullptr;
		}

		/**
 		* @brief Compares this object with a given function for equality.
 		*
 		* This comparison is based on the unique hash code of the bound functions.
 		*
 		* @tparam Args... The types of the arguments accepted by the function.
 		* @param function The function to compare with.
 		* @return True if the bound functions are considered equal, false otherwise.
 		*/

		template<typename... Args>
		HEXEN_INLINE bool operator==(std::function<void(Args...)> &&function)
		{
			HEXEN_ADD_TO_PROFILE();
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = std::forward<std::function<void(Args...)>>(function);
			return delegate->getId() == object.type().hash_code();
		}

		/**
 		* @brief Compares this object with a given function for inequality.
 		*
 		* This comparison is based on the unique hash code of the bound functions.
 		*
 		* @tparam Args... The types of the arguments accepted by the function.
 		* @param function The function to compare with.
 		* @return True if the bound functions are not equal, false otherwise.
 		*/

		template<typename... Args>
		HEXEN_INLINE bool operator!=(std::function<void(Args...)> &&function)
		{
			HEXEN_ADD_TO_PROFILE();
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = std::forward<std::function<void(Args...)>>(function);
			return delegate->getId() != object.type().hash_code();
		}


		/**
 		* @brief This second function template overloads the equality operator to compare
 		* if a member function's hash id is same as the delegate's id. This is same as the function above.
 		*
 		* @tparam T The class type.
 		* @tparam Ret The return type of the member function.
 		* @tparam Args The parameter types of the member function.
 		* @param callableMethod The pointer-to-member function.
 		* @return Returns true if delegate's id is the same as the function's hash code. Returns false if the delegate is null.
 		*/

		template<class T, typename Ret, typename... Args>
		HEXEN_INLINE bool operator==(Ret (T::*callableMethod)(Args...))
		{
			HEXEN_ADD_TO_PROFILE();
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = callableMethod;
			return delegate->getId() == object.type().hash_code();
		}

		/**
 		* @brief A template operator overload that checks whether a specified callable method
 		* does not match with the delegate's ID.
 		*
 		* @tparam T class or type of the object.
 		* @tparam Ret return type of the callable method.
 		* @tparam Args Variadic template for arguments of the callable method.
 		* @param callableMethod the callable method of an object of type T.
 		* @return bool If delegate is not null, it returns true if the delegate's ID does
 		* not match with the type hash of the callable method; otherwise it returns false.
 		* If the delegate is null, it immediately returns false.
 		*/

		template<class T, typename Ret, typename... Args>
		HEXEN_INLINE bool operator!=(Ret (T::*callableMethod)(Args...))
		{
			HEXEN_ADD_TO_PROFILE();
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = callableMethod;
			return delegate->getId() != object.type().hash_code();
		}

		/**
 		* @brief This function is an operator function that checks if the callableFunction matches the delegate's ID.
	 	*
 		* @tparam Ret return type of the callable function
 		* @tparam Args types of arguments that callable function accepts
 		* @param callableFunction pointer to function that can be invoked with specified arguments and returns specified type
 		* @return true if the delegate id matches the hash of the callable function type
 		* @return false if the delegate is a null pointer or if the delegate id is different from the hash of the callable function type
 		*/

		template<typename Ret, typename... Args>
		HEXEN_INLINE bool operator==(Ret (*callableFunction)(Args...))
		{
			HEXEN_ADD_TO_PROFILE();
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = callableFunction;
			return delegate->getId() == object.type().hash_code();
		}

		/**
 		* @brief Overloads the inequality operator to compare a given callable function with a delegate.
 		*
 		* This function overloads the operator '!=' to compare the provided callableFunction with the existing delegate.
 		* If the delegate is null, it returns false, otherwise, compares the ID of the delegate with the hash code of the object type of callableFunction.
 		*
 		* @tparam Ret The return type of the callable function.
 		* @tparam Args Variadic template parameter representing the types of the arguments of the callable function.
 		*
 		* @param callableFunction A pointer to the function to be compared with the delegate.
 		*
 		* @return bool Returns true if the delegate id is not equal to the hash code of object's type (i.e., the function type), otherwise false.
 		*/

		template<typename Ret, typename... Args>
		HEXEN_INLINE bool operator!=(Ret (*callableFunction)(Args...))
		{
			HEXEN_ADD_TO_PROFILE();
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = callableFunction;
			return delegate->getId() != object.type().hash_code();
		}

		/**
 		* @brief Binds a functor delegate to an object and its member function with variable arguments.
 		*
 		* This template function creates a `shared_ptr` to a FunctorDelegate instance, then reinterprets that pointer
 		* as a pointer to a BaseDelegate and assigns it to the `delegate` member.
 		*
 		* @tparam T  The object type.
 		* @tparam Args The types of the member function arguments.
 		* @param object A pointer to the object to which the FunctorDelegate is to be bound.
 		* @param args The arguments to pass to the member function when the delegate is invoked.
 		*
 		* @return Returns true if the binding is successful, otherwise returns false.
 		*/

		template<typename T, typename... Args>
		bool bind(T *object, Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			auto functorDelegate = std::shared_ptr<core::FunctorDelegate<T, Args...>>(new core::FunctorDelegate(object, args...));
			delegate = std::reinterpret_pointer_cast<BaseDelegate<std::any>>(functorDelegate);

			if (delegate == nullptr)
			{
				return false;
			}

			return true;
		}

		/**
 		* @brief Binds a functor delegate to an object and its member function with variable arguments.
 		*
 		* This template function creates a `shared_ptr` to a FunctorDelegate instance, then reinterprets that pointer
 		* as a pointer to a BaseDelegate and assigns it to the `delegate` member.
 		*
 		* @tparam T  The object type.
 		* @tparam Args The types of the member function arguments.
 		* @param object A pointer to the object to which the FunctorDelegate is to be bound.
 		* @param args The arguments to pass to the member function when the delegate is invoked.
 		*
 		* @return Returns true if the binding is successful, otherwise returns false.
 		*/

		template<typename T, typename... Args>
		HEXEN_INLINE bool operator==(T *functor)
		{
			HEXEN_ADD_TO_PROFILE();
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = functor;
			return delegate->getId() == object.type().hash_code();
		}

		/**
 		*  @brief This function overloads the `operator !=` to compare a given functor with the delegate object's id.
 		*
 		*  @details The functor's type is stored in a `std::any` object, and its hash code (type identifier)
 		*  is compared with the delegate's id. If the delegate is null, the function automatically returns false.
 		*
 		*  @param functor The functor to be compared with the delegate.
 		*
 		*  @tparam T The type of the pointer to the functor.
 		*  @tparam Args Variadic template parameter representing optional additional arguments passed to the functor.
 		*
 		*  @return Returns true if delegate's id is not equal to the functor's type hash code. If delegate is nullptr, the function returns false.
 		*/

		template<typename T, typename... Args>
		HEXEN_INLINE bool operator!=(T *functor)
		{
			HEXEN_ADD_TO_PROFILE();
			if (delegate == nullptr)
			{
				return false;
			}

			std::any object = functor;
			return delegate->getId() != object.type().hash_code();
		}

		/**
 		* @brief A method to execute code in a delegate if it exists.
 		*
 		* This method allows for an execute call to a delegate object,
 		* provided the delegate pointer is not null.
 		*
 		* @pre The delegate object must be correctly set up and must implement the 'execute' method.
 		*
 		* @post The 'execute' method of the delegate object will be invoked if delegate is not null.
 		*/

		void execute() const
		{
			HEXEN_ADD_TO_PROFILE();
			if (delegate != nullptr)
			{
				delegate->execute();
			}
		}

		/**
 		* @brief An shared pointer instance to BaseDelegate.
 		*
 		* This shared pointer will be used to share the BaseDelegate instance
 		* across multiple classes or functions.
 		* The instance is initialized to `nullptr` which means there is no
 		* BaseDelegate instance associated with it initially.
 		*/

		std::shared_ptr<BaseDelegate<std::any>> delegate {nullptr};

		/**
 		* @brief A vector of pointers.
 		*
 		* This vector will be used to store the arguments data, each element
 		* in the vector represents a single argument value.
 		*/


		vptr ArgumentsData {};
	};

	enum class TaskPriority
	{
		High,
		Normal,
	};
}// namespace hexen::engine::core::threading
