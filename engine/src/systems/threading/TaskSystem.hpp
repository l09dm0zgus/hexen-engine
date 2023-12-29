//
// Created by cx9ps3 on 29.07.2023.
//

#pragma once
#include "../../profiling/Profiling.hpp"
#include "threading/Threading.hpp"
#include <memory>

namespace hexen::engine::systems
{
	/**
 	* @class TaskSystem
 	* @brief This class manages tasks in the system.
 	*
 	* Manages tasks by using the TaskScheduler and TaskCounter objects.
 	*/

	class TaskSystem
	{
	private:

		/**
	 	* @brief A TaskScheduler object manages the tasks in the background.
	 	*
	 	* This object is responsible for the scheduling and execution of tasks. It operates independently of the TaskSystem.
	 	*/

		static core::threading::TaskScheduler scheduler;

		/**
         * @brief A TaskCounter object keeps track of the number of tasks.
         *
         * This object keeps count of the tasks in the TaskSystem. It operates independently of the TaskSystem.
  	 	 */

		static core::threading::TaskCounter counter;

	public:

		/**
 		* @brief Initializes the Task System.
 		*/

		static void initialize();

		/**
	 	* @brief Adds a new task to the task system.
	 	*
	 	* This method allows for the creation of new tasks that are added to the task scheduler.
     	* These tasks are added with a specified priority and a counter.
	 	*
	 	* @param priority The priority of the task that is being added. This is of the type core::threading::TaskPriority.
	 	* @param object Pointer to the object of the class where the method resides. It should be of generic type T.
	 	* @param method The method to be executed as the task. It should be a member method of type T.
	 	* @param args Varargs. The parameters to the method that represents the task.
     	* This is a variadic parameter which can take multiple arguments of any type.
	 	*
	 	*
	 	* Example usage:
	 	* @code
	 	*     TaskSystem tasks;
	 	*     MyClass myObject;
	 	*     tasks.addTask(core::threading::TaskPriority::High, &myObject, &MyClass::myMethod, arg1, arg2);
	 	* @endcode
	 	*/

		template<class T, typename Ret, typename... Args1, typename... Args2>
		static void addTask(core::threading::TaskPriority priority, T *object, Ret (T::*method)(Args1...), Args2... args);

		/**
 		* @brief The `TaskSystem::addTask` function is a method in the TaskSystem
 		*        class that adds tasks to the task scheduler.
 		*
 		* @tparam Ret: Return type of the function assigned for the task.
 		*        It can be any user-defined or built-in data type or void.
 		* @tparam Args: Variadic template that holds types of any number of arguments.
 		*        This allows `addTask` method to accept functions which have
 		*        different number and types of parameters.
 		*
 		* @param priority: The priority of the task in the task scheduling system.
 		*        It is of type `core::threading::TaskPriority`,
 		*        a user-defined type that represents the task's priority level.
 		* @param function: The function that the task is supposed to execute.
 		*        This is a function pointer that points to a function
 		*        returning a `Ret` data type and taking `Args...` types as parameters.
 		* @param args: These are the arguments that the function will be called with.
 		*
 		* This function works by first creating an object of type `core::threading::Task`,
 		* then binding the function pointer and its parameters to it. This task object
 		* is then added to the scheduler with the specified priority and a counter reference.
 		*/

		template<typename Ret, typename... Args1, typename... Args2>
		static void addTask(core::threading::TaskPriority priority, Ret (*function)(Args1...), Args2... args);

		/**
     	* @brief method to add a new task to the task system scheduler.
     	*
     	* This method is a part of the TaskSystem class and is used to add a new task to the scheduler. The task is represented by a functor
     	* and its arguments. The TaskSystem is responsible for managing and scheduling tasks according to their priority, which
     	* is provided as a parameter to this method. The tasks are handled in the order of their priority, with the tasks of higher
     	* priority being handled before those of lower priority. The method also updates a counter every time a new task is added.
     	*
     	* @tparam T The type of the functor that represents the task.
     	* @tparam Args The type list representing the arguments of the functor.
     	*
     	* @param priority The priority of the task. The tasks are handled in priority order.
     	* @param newFunctor The functor that represents the task. It is a function object that can be called later with provided args.
     	* @param args The arguments for the functor.
     	*
     	*/

		template<class T, typename... Args1, typename... Args2>
		static void addTask(core::threading::TaskPriority priority, T *newFunctor(Args1...), Args2... args);

		/**
		* @brief Function to add tasks to the task scheduler.
		*
		* This function is a member of the TaskSystem class in the hexen::engine::systems namespace.
		* It acts as an interface to add tasks into the system's scheduler, based on their priority.
		*
		* @param priority The priority of the tasks, defined as a value of the TaskPriority enumeration in the core::threading namespace.
		* @param tasks An array of Task objects, defined in the core::threading namespace.
		*
		* @note The tasks are added to the scheduler along with their priority level and a pointer to decrement when task is completed.
		*
		*/

		static void addTasks(core::threading::TaskPriority priority, const std::array<core::threading::Task, 400> &tasks);

		/**
 		* @brief A method that waits for the task system's counter to reach a specified value.
 		*
 		* The method tasks a 32-bit integer value as input and waits until the counter of the underlying
 		* scheduler system reaches this value before proceeding with the execution. This can be used to synchronize
 		* tasks in the system based on completion of certain number of tasks denoted by the value
 		* of the counter.
 		*
 		* @param value A 32-bit integer referring to the counter value the system needs to wait for.
 		*/

		static void waitForCounter(core::i32 value = 0);

		template<typename... Args1 , typename...Args2>
		static void addTask(core::threading::TaskPriority priority, std::function<void(Args1...)> &function, Args2 ...args);
	};


	template<class T, typename... Args1, typename... Args2>
	void TaskSystem::addTask(core::threading::TaskPriority priority, T *newFunctor(Args1...), Args2... args)
	{
		HEXEN_ADD_TO_PROFILE();
		core::threading::Task task;
		task.bind(newFunctor, std::forward<Args2...>(args...));
		scheduler.addTask(task, priority, &counter);
	}

	template<typename... Args1 , typename...Args2>
	void TaskSystem::addTask(core::threading::TaskPriority priority, std::function<void(Args1...)> &function, Args2...args)
	{
		HEXEN_ADD_TO_PROFILE();
		core::threading::Task task;
		task.bind(function,args...);
		scheduler.addTask(task, priority, &counter);
	}

	template<typename Ret, typename... Args1, typename... Args2>
	void TaskSystem::addTask(core::threading::TaskPriority priority, Ret (*function)(Args1...), Args2... args)
	{
		HEXEN_ADD_TO_PROFILE();
		core::threading::Task task;
		task.bind(function, args...);
		scheduler.addTask(task, priority, &counter);
	}


	template<class T, typename Ret, typename... Args1, typename... Args2>
	void TaskSystem::addTask(core::threading::TaskPriority priority, T *object, Ret (T::*method)(Args1...), Args2... args)
	{
		HEXEN_ADD_TO_PROFILE();
		core::threading::Task task;
		task.bind(object, method, args...);
		scheduler.addTask(task, priority, &counter);
	}

}// namespace hexen::engine::systems
