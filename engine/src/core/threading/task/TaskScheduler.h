#pragma once

#include "Callbacks.h"
#include "../threads/Fiber.h"
#include "Task.h"
#include "../threads/Thread.h"
#include "../threads/WaitFreeQueue.h"
#include "TaskSchedulerSettings.h"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <array>

namespace core::threading
{
    class BaseCounter;
    class TaskCounter;
    class AtomicFlag;
    class FullAtomicCounter;

    enum class EmptyQueueBehavior
    {
     Spin,
     Yield,
     Sleep
    };

    struct TaskSchedulerInitOptions
    {
        /**
        * @brief The `fiberPoolSize` variable represents the size of the fiber pool.
        *
        * This variable indicates the maximum number of fibers that can be active
        * simultaneously in the fiber pool. A fiber pool is a collection of fibers
        * that can be used for executing lightweight tasks concurrently.
        *
        * The value of `fiberPoolSize` determines the capacity or the total number of
        * fibers available in the pool. Once the fiber pool size is reached, any new
        * requests to create a fiber will be put on hold until a fiber becomes
        * available from the pool.
        *
        * @note The value of `fiberPoolSize` is fixed and should be set to a positive
        *       integer that represents the desired number of fibers in the pool.
        *
        * @warning Setting an extremely large pool size may consume excessive system
        *          resources, leading to performance degradation. It is important to
        *          consider the available hardware resources and the expected usage
        *          pattern before setting the value of `fiberPoolSize`.
        *
        * @see https://en.wikipedia.org/wiki/Fiber_(computer_science)
        */

        u32 fiberPoolSize = 400;

        /**
        * @brief The number of threads in the thread pool.
        *
        * The `threadPoolSize` variable represents the number of threads that will be maintained in the thread pool. Setting it to 0 means that there are no threads in the pool. Increasing the value will result in more threads being available for executing tasks concurrently.
        *
        * @note If `threadPoolSize` is set to 0, no tasks will be executed in parallel. Instead, they will be executed serially, one after another.
        *
        * @note The appropriate value for `threadPoolSize` depends on various factors such as the number of available CPU cores, the nature of the tasks being executed, and the expected workload. It should be carefully tuned to achieve the desired balance between performance and resource utilization.
        *
        * @see ThreadPool
        * @see Task
        */

        u32 threadPoolSize = 0;

        /**
        * @brief Enum class representing the behavior of an empty queue.
        */

        EmptyQueueBehavior behavior = EmptyQueueBehavior::Spin;

        /**
        * @file Callbacks.h
        *
        * @brief Definition of callback functions
        */

        EventCallbacks callbacks;
    };

    class TaskScheduler
    {
    public:

        /**
        * @class TaskScheduler
        * @brief The TaskScheduler class is responsible for scheduling and managing tasks.
        *
        *  The TaskScheduler class provides functionality for scheduling and managing tasks.
        * It allows adding new tasks, removing existing tasks, and executing tasks at a specific time or interval.
        */

        TaskScheduler() = default;

        /**
        * @class TaskScheduler
        * @brief This class represents a task scheduler that manages the execution of tasks.
        *
        * The TaskScheduler class provides the functionality to schedule and execute tasks
        * at specified times or intervals. It ensures that only one instance of the TaskScheduler
        * can be created and disallows copy construction.
        *
        * @note This class must be used as a singleton to ensure correct functionality.
        */

        TaskScheduler(TaskScheduler const &) = delete;

        /**
        * @class TaskScheduler
        * @brief Class that represents a task scheduler.
        *
        * The TaskScheduler class is responsible for scheduling and executing tasks asynchronously.
        * It provides functionality to move (i.e., transfer ownership) of a TaskScheduler object.
        *
        * @note This class is non-copyable, and the move constructor is explicitly deleted.
        *
        * @see Task
        */

        TaskScheduler(TaskScheduler &&) noexcept = delete;

        /**
        * @brief Assignment operator overload (deleted)
        *
        * This assignment operator overload is deleted, meaning it is not
        * allowed to assign one instance of TaskScheduler to another.
        *
        * @param rhs The right-hand side of the assignment
        *
        * @return This function does not return a value
        */

        TaskScheduler &operator=(TaskScheduler const &) = delete;

        /**
        *
        * @class TaskScheduler
        * @brief Represents a task scheduler with a deleted move assignment operator.
        *
        * This class is responsible for managing and scheduling tasks using a task queue.
        *
        * @note
        * This class does not allow move assignment.
        *
        * @author Your Name
        * @date Current Date
        *
        */

        TaskScheduler &operator=(TaskScheduler &&) noexcept = delete;

        /**
        * @class TaskScheduler
        * @brief This class represents a task scheduler that manages the execution of multiple tasks.
        *
        * The TaskScheduler class allows registering tasks and scheduling their execution based on a specified interval.
        * It provides methods to add, remove, and query tasks, as well as to start and stop the scheduler.
        */

        ~TaskScheduler();

    private:

        enum class FiberDestination
        {
          None = 0,
          ToPool = 1,
          ToWaiting = 2,
        };

        struct TaskBundle
        {

        /**
        * @brief Variable representing a task that needs to be executed.
        *
        * This variable stores the details of a task that needs to be executed. It can be used to
        * schedule and manage tasks within a software application. The task can be any unit of
        * work or action that needs to be performed.
        */

        Task taskToExecute;
        TaskCounter *counter;
        };

        struct ReadyFiberBundle
        {

            /**
            * @class ReadyFiberBundle
            * @brief A class representing a ready-to-use fiber bundle.
            *
            * The ReadyFiberBundle class provides the necessary capabilities to manage a fiber bundle
            * that is ready for use. It encapsulates the default constructor, which initializes the
            * object with default values.
            *
            * Here is how to use the ReadyFiberBundle class:
            * - Create an instance of ReadyFiberBundle using the default constructor.
            * - Use the various methods and properties provided by the class to manipulate the fiber bundle.
            *
            */

            ReadyFiberBundle() = default;

            /**
            * @brief Represents the fiber index.
            *
            * The fiberIndex variable is used to store the index of a fiber. It is typically an integer value that represents the position or identification of a fiber within a collection or system.
            *
            * The fiber index can be used to access or manipulate specific fibers within an array or data structure.
            *
            *
            */

            u32 fiberIndex;

            /**
            * @brief Indicates if the fiber connection is switched or not.
            *
            * This variable is used to determine whether the fiber connection has been switched or not.
            * A switched fiber connection means that the network traffic is being rerouted through an alternate fiber path,
            * typically due to a failure or maintenance in the primary path.
            *
            * A true value indicates that the fiber connection has been switched, while a false value indicates
            * that the fiber connection is not switched.
            *
            * It's important to monitor the value of this variable in order to quickly identify any disruptions in the fiber connection.
            *
            * @note This variable does not provide details about the specific reasons for the switching.
            *
            */

            std::atomic<bool> fiberIsSwitched;
        };

        struct alignas(cacheLineSize) ThreadLocalStorage
        {
            /**
            * @class ThreadLocalStorage
            * @brief This class represents the thread-specific storage for a fiber system.
            */

            ThreadLocalStorage(): currentFiberIndex(invalidIndex), oldFiberIndex(invalidIndex) {}

        public:

            /**
            * @brief The `highPriorityTaskQueue` variable is a queue that stores high priority tasks.
            *
            * The queue data structure is a first-in, first-out (FIFO) collection of tasks with high priority.
            * High priority tasks are meant to be processed before regular priority tasks.
            *
            * Usage:
            * - Initialize the `highPriorityTaskQueue` before usage.
            * - Add high priority tasks to the queue using the `push` function.
            * - Remove high priority tasks from the queue using the `pop` function.
            * - Retrieve the number of tasks in the queue using the `size` function.
            *
            * Example Usage:
            *
            * highPriorityTaskQueue.push(task1); // Add task1 to the queue
            *
            * unsigned int numTasks = highPriorityTaskQueue.size(); // Get the number of tasks in the queue
            */

            WaitFreeQueue<TaskBundle> highPriorityTaskQueue;

            /**
            * @class normalPriorityTaskQueue
            * @brief A queue for normal priority tasks
            *
            * The normalPriorityTaskQueue class is designed to store and manage a queue of normal priority tasks.
            * Normal priority tasks are tasks that can be executed in the background without significantly impacting the
            * performance of the system. This queue follows a First-In-First-Out (FIFO) order.
            * Tasks can be added to the queue and retrieved for execution.
            */

            WaitFreeQueue<TaskBundle> normalPriorityTaskQueue;

            /**
            * @brief The flag to indicate whether the old fiber is stored or not.
            *
            * The oldFiberStoredFlag is a pointer that points to the memory address of the flag
            * indicating the state of the old fiber. When the old fiber is stored, the flag will
            * point to a non-null memory address, otherwise, it will be set to nullptr.
            */

            std::atomic<bool> *oldFiberStoredFlag{nullptr};

            /**
            * @brief An array of fibers that are ready to be executed and have been pinned to specific CPU cores.
            *
            * The `pinnedReadyFibers` variable represents an array of fibers that are ready to be executed and have been
            * pinned to specific CPU cores. This variable is used to keep track of the fibers that are ready for execution as
            * well as the CPU cores to which they have been pinned. It allows for efficient and optimized execution of fibers
            * on specific CPU cores, enabling better performance and resource utilization.
            *
            * This variable is typically used in multi-threaded or concurrent applications where fibers are used to achieve
            * lightweight concurrency and parallelism. By pinning fibers to specific CPU cores, it is possible to distribute
            * the workload evenly across multiple cores and minimize the overhead associated with thread context switching.
            *
            * The `pinnedReadyFibers` array is dynamically populated with fiber objects that are ready for execution and have
            * been explicitly pinned to specific CPU cores. The array is resized as needed to accommodate new fibers.
            *
            * Accessing and modifying the `pinnedReadyFibers` array should be done with caution and in a thread-safe manner,
            * especially when working with multiple threads that may execute fibers concurrently. Proper synchronization
            * mechanisms should be employed to ensure the integrity and consistency of the array contents.
            *
            */

            std::vector<ReadyFiberBundle *> pinnedReadyFibers;

            /**
            * @var threadFiber
            * @brief This variable represents a thread of execution in a fiber-based multitasking model.
            *
            * A threadFiber is a lightweight thread that runs within a fiber instead of a traditional operating system thread.
            * It provides a simpler and more efficient way to perform concurrent programming.
            *
            * This variable is an instance of a threadFiber object, which encapsulates the necessary information for executing
            * the thread in a fiber-based multitasking environment.
            *
            * @attention threadFiber objects are not meant to be directly executed, but rather to encapsulate and control the
            *            execution of a thread in a fiber-based multitasking environment. It should be used in conjunction with
            *            a fiber scheduler or similar system.
            *
            * @see Fiber
            */

            Fiber threadFiber;

            /**
            * @brief The pinnedReadyFibersLock variable is used to synchronize access to the pinnedReadyFibers queue.
            *
            * This lock ensures that only one thread can access the pinnedReadyFibers queue at a time. It is used to prevent race conditions
            * and ensure thread safety when adding or removing fibers from the queue.
            *
            */
            std::mutex pinnedReadyFibersLock;

            /**
            * @brief The index of the current fiber.
            *
            * This variable represents the index of the current fiber within a collection of fibers.
            * It is used to keep track of the current fiber being processed or accessed.
            *
            * @note The index value starts from 0 for the first fiber.
            */

            u32 currentFiberIndex;

            /**
            * @brief The index of the old fiber.
            *
            * This variable represents the index of the old fiber. It is typically used in fiber reassignment or swapping scenarios.
            * The index is an integer value that uniquely identifies the old fiber within a data structure or system.
            * The value of this variable is updated when a new fiber is assigned or swapped with the old one.
            *
            * @note This variable should be used in conjunction with other variables or functions to perform relevant operations.
            * For example, it can be used along with a fiber container to retrieve or manipulate the old fiber.
            *
            */

            u32 oldFiberIndex;

            /**
            * @brief The oldFiberDestination variable represents the destination of an old fiber.
            *
            * This variable is of type FiberDestination and is initialized with the value FiberDestination::None.
            * It is used to store the previous destination of a fiber before it is changed.
            */

            FiberDestination oldFiberDestination{FiberDestination::None};

            /**
            * @brief Variable to store the high priority last successful steal.
            *
            * This variable is used to track the high priority last successful steal.
            * It is typically updated when a high priority stealing operation is successfully executed.
            *
            * The value of this variable is an integer, representing the successful steal operation count.
            *
            * Example usage:
            *     higPriorityLastSuccessfulSteal = 1;
            *
            * @see Other related variables/functions
            */

            u32 higPriorityLastSuccessfulSteal{1};

            /**
            * @brief Represents the last successful steal by a thread with normal priority.
            *
            * This variable stores the value of the last successful steal (i.e., the successful transfer of work from one thread to another) performed by a thread with normal priority.
            *
            * The value stored in this variable is {1}.
            *
            * @note This documentation assumes a multi-threaded environment.
            */

            u32 normalPriorityLastSuccessfulSteal{1};

            /**
            * @brief Number of failed attempts to pop from the queue.
            *
            * This variable keeps track of the number of times an attempt to pop an element
            * from the queue has failed.
            *
            * @note This variable is handy when you need to monitor and debug issues related
            * to failed pop attempts in the queue.
            *
            * @warning You should update this variable whenever a pop attempt fails.
            *
            * @var failedQueuePopAttempts
            */

            u32 failedQueuePopAttempts{0};
        };

    private:
        // Member variables

        /**
        * @brief The maximum invalid index value.
        *
        * This constant variable represents the maximum value that can be used to
        * indicate an invalid index in an unsigned 32-bit integer context.
        * Specifically, it is set to the maximum value allowable for the 'u32'
        * data type defined in the 'std' namespace. This value can be used to
        * designate an index that is out of range or invalid in various algorithms
        * or data structures. For example, it can be utilized in situations where
        * an index is expected to be within a certain range, and a value exceeding
        * the maximum range is required to indicate an invalid or non-existent
        * index.
        *
        * The variable 'invalidIndex' should be used to clearly communicate the
        * intent of an invalid index value, avoiding the need to rely on "magic
        * numbers" or confusing code constructs.
        *
        * @note The 'std' namespace must be included in the code to make use of
        *       the 'u32' data type and the 'numeric_limits' class.
        *
        * @see std::numeric_limits
        *
        * @remark Although this variable is initialized with the maximum value,
        *           it is also possible to use a different value, such as zero, to
        *         indicate an invalid index depending on the specific context in
        *         which this variable is used.
        *
        * @warning The 'std::numeric_limits' class is part of the C++ standard
        *          library, and hence, this variable can only be applied in a
        *          C++ environment.
        *
        * @attention Before using this variable, ensure that the 'std' namespace
        *             and the 'numeric_limits' class are correctly imported.
        **/

        constexpr static u32 invalidIndex = std::numeric_limits<u32>::max();

        /**
        * @brief A constant variable indicating that no thread pinning is applied.
        *
        * This variable represents an upper limit value for a 32-bit unsigned integer type,
        * indicating that no thread pinning is applied. Thread pinning is a technique used
        * to bind a specific thread or set of threads to a particular CPU or set of CPUs.
        * By assigning this value to a variable, it can be used to indicate the absence of
        * thread pinning in a software system.
        *
        * @note The actual value of this constant variable depends on the maximum value
        *       supported by the `u32` type, typically represented by `std::numeric_limits<u32>::max()`.
        *       This ensures that the variable can accommodate the maximum value for the `u32` type
        *       on the platform.
        *
        */

        constexpr static u32 noThreadPinning = std::numeric_limits<u32>::max();

        /**
         * @brief Storing of settings of TaskScheduler
         *
         * @see class TaskSchedulerSettings
         *
         * @file TaskSchedulerSettings.h
         */

        std::unique_ptr<TaskSchedulerSettings> settings;

        /**
        * @file Callbacks.h
        *
        * @brief Declaration of callback functions.
        */

        EventCallbacks callbacks;

        /**
        * @brief The number of threads to be used.
        *
        * This variable represents the number of threads that will be utilized
        * by the program. It determines the level of parallelism in the execution
        * and affects the overall performance of the application.
        *
        * The initial value of `numberOfThreads` is 0, which means that will be used all available cores.
        *
        */

        u32 numberOfThreads{0};

        /**
        * @brief Array Of threads.
        *
        * This variable holds a  array of threads. Initially, it is set to nullptr.
        * The threads array can be allocated and pointed to by assigning a valid memory address to this variable.
        * This variable is used to keep track of multiple threads within the program.
        */

        thread::ThreadType *threads{nullptr};

        /**
        * @brief The size of the fiber pool.
        *
        * This variable represents the size of the fiber pool, which determines the maximum number of fibers that can be
        * concurrently running. A fiber pool is a pool of lightweight threads, also known as fibers, which can be scheduled
        * by a fiber scheduler to execute tasks asynchronously.
        *
        * The value of this variable is of type integer. A value of 0 indicates that there is no limit on the number of fibers
        * in the fiber pool, meaning that fibers can be created and executed without any restriction.
        *
        * By adjusting the value of this variable, the application can control the level of concurrency and manage system
        * resources effectively. Higher values can increase the number of tasks that can be executed in parallel, but at the
        * expense of increased memory usage and potential resource contention. Lower values can limit concurrency and prevent
        * resource overload, but may also result in slower task execution.
        *
        * It is important to note that the appropriate value for fiberPoolSize depends on the specific application's requirements
        * and system constraints. Care should be taken to evaluate and fine-tune this value to ensure optimal performance and
        * resource utilization.
        */

        u32 fiberPoolSize{0};

        /**
        * @brief  Array of fibers.
        *
        *  This variable stores a  array of fibers. The fibers are
        * represented as objects or elements of the array.
        *
        * When the variable is initialized, it is set to nullptr, indicating that the
        * array of fibers has not been allocated yet.
        *
        * Usage:
        *     - Initialize the fibers variable with nullptr to indicate no allocation.
        *     - Allocate an array of fibers and assign the pointer to fibers.
        *     - Manipulate the fibers by accessing their elements through the pointer.
        *     - Deallocate the array of fibers and set fibers to nullptr if no longer needed.
        */

        Fiber *fibers{nullptr};

        /**
        * @brief Pointer to an array of free fibers.
        *
        * This pointer is used to track and manage the free fibers in a program. The variable 'freeFibers' is initialized to nullptr, indicating that there are currently no free fibers available. As fibers are created and released, this pointer is updated to reflect the current state of free fibers.
        *
        */

        std::atomic<bool> *freeFibers{nullptr};

        /**
        * @brief Variable containing ready fiber bundles.
        *
        */

        ReadyFiberBundle *readyFiberBundles{nullptr};


        /**
        * @brief Pointer variable to track the quitting state of fibers.
        *
        * This variable is used to indicate the state of quitting fibers. It is a pointer that can be set to nullptr initially,
        * indicating that no fibers have been instructed to quit. When the variable is set to a non-null value, it means that
        * fibers should quit. The specific value of the pointer is not relevant, only its null or non-null state.
        * Therefore, when quitFibers is nullptr, it means that no fibers should quit, and when it is not nullptr,
        * it means that fibers should quit.
        */

        Fiber *quitFibers{nullptr};

        /**
        * @brief This variable indicates whether an task scheduler has been initialized or not.
        *
        * By default, the value of isInitialized is set to false, indicating that the scheduler has not been initialized.
        * When the scheduler is initialized, the value of isInitialized should be set to true, indicating that it has been initialized.
        *
        * @see initialize()
        */

        std::atomic<bool> isInitialized{false};

        /**
        * @brief Boolean variable representing if the program should quit or not.
        *
        * It is initially set to false, indicating the program should not quit.
        */

        std::atomic<bool> isQuit{false};

        /**
        * @brief The number of times the quitting action has occurred.
        *
        * This variable keeps track of the number of times a quitting action
        * has been performed. It is initially set to 0 and will be incremented
        * each time the quitting action is triggered.
        *
        * @note This variable is expected to be of type integer.
         *
        * @var quitCount
         */

        std::atomic<u32> quitCount{0};

        /**
        * @enum EmptyQueueBehavior
        * @brief Specifies the behavior when operating on an empty queue
        *
        * This enum class defines the different behaviors that can be exhibited when performing operations on an empty queue.
        * The behavior is specified using the EmptyQueueBehavior enum value.
        */

        std::atomic<EmptyQueueBehavior> emptyQueueBehavior{EmptyQueueBehavior::Spin};

        /**
        * @brief The threadSleepLock variable is used to synchronize threads when pausing their execution for a certain period of time.
        *
        * This variable ensures that only one thread can enter the sleep state at a time, providing thread safety and preventing concurrent execution.
        * When a thread wants to pause its execution for a given period of time, it locks the threadSleepLock variable using a mutex. Once the thread is
        * done sleeping, it unlocks the mutex, allowing other threads to use the sleep functionality as well.
        *
        * Note that this variable should be used in conjunction with other synchronization mechanisms to ensure the correctness of shared data access.
        * It is also recommended to hold the lock for the minimum required time to avoid unnecessary delays in other threads.
        *
        */

        std::mutex threadSleepLock;

        /**
        * @brief An example of a condition variable for thread sleep synchronization.
        *
        * This condition variable is used to suspend a thread's execution until a certain condition is met.
        * It can be used in conjunction with a mutex to ensure thread safety and proper synchronization.
        *
        * This variable should be defined as a member variable in a class or as a global variable in a file.
        *
        * Note: Remember to use a mutex with the condition variable to avoid race conditions.
        */

        std::condition_variable threadSleepCv;

        /**
        * @brief The threadLocalStorage variable represents a pointer to thread-specific storage.
        *
        * Thread-specific storage provides a way to store data that is private to each thread in a multithreaded environment.
        * This variable, threadLocalStorage, is initialized with a value of nullptr.
        *
        * By default, threadLocalStorage has no associated data. Each thread can assign a unique value to threadLocalStorage using an appropriate mechanism.
        *
        * @note It is important to note that the use of threadLocalStorage may require synchronization mechanisms to ensure data integrity
        * and prevent data races when multiple threads try to access or modify the same data simultaneously.
        *
        */

        ThreadLocalStorage *threadLocalStorage{nullptr};

        friend class BaseCounter;



    public:


        /**
        * @brief Initializes the task scheduler with the given options.
        *
        * This function initializes the task scheduler with the provided initialization options.
        * If no options are provided, default options will be used.
        *
        * @param options The initialization options for the task scheduler (default: TaskSchedulerInitOptions()).
        *
        * @see TaskSchedulerInitOptions
        */

        i32 initialize(TaskSchedulerInitOptions options = TaskSchedulerInitOptions());

        /**
        * @brief Add a task with specified priority to the task list.
        *
        * This function adds a task to the task list with the specified priority.
        * If a TaskCounter pointer is provided, it will be incremented to reflect
        * the new task addition.
        *
        * @param task The task to be added.
        * @param priority The priority of the task.
        * @param counter Pointer to a TaskCounter that will be incremented (optional).
        *
        */

        void addTask(Task task,TaskPriority priority,TaskCounter *counter = nullptr);

        /**
        * @brief Add multiple tasks to the task scheduler.
        *
        * This function adds multiple tasks to the task scheduler provided. The tasks are
        * specified in an array of Task objects. By default, the function does not
        * pin the task counter to the current thread, but this behavior can be changed
        * by setting the optional pinToCurrentThread parameter to true.
        *
        * @param tasks The array of Task objects to be added to the task counter.
        * @param counter Pointer to the TaskCounter object.
        * @param priority The priority of the task.
        *
        * @see Task
        * @see TaskCounter
        */

        void addTasks(const std::array<Task,400> &tasks, TaskPriority priority, TaskCounter *counter);


        /**
        * @brief Waits for the value of the atomic flag counter to become true.
        *
        * If the pinToCurrentThread parameter is set to true, the function will keep running on the current thread
        * until the value of the atomic flag becomes false. If pinToCurrentThread is set to false (default value),
        * the function will periodically check the atomic flag using a non-busy-wait approach, allowing other
        * threads to be scheduled in between checks.
        *
        * @param counter             The atomic flag to wait for.
        * @param pinToCurrentThread  Flag indicating whether to pin the waiting to the current thread.
        *                            Default value is false.
        */

        void waitForCounter(AtomicFlag *counter, bool pinToCurrentThread = false);


        /**
        * @brief Waits until the given counter reaches the specified value.
        *
        * This function blocks the execution until the counter reaches the desired value.
        * Optionally, it can pin the execution to the current thread.
        *
        * @param counter Pointer to the FullAtomicCounter instance.
        * @param value The desired value of the counter.
        * @param pinToCurrentThread (optional) Specifies whether to pin the execution to the current thread. Default is false.
        */

        void waitForCounter(FullAtomicCounter *counter,u32 value,bool pinToCurrentThread = false);


        /**
        * @brief Waits for the counter to reach zero.
        *
        * This function blocks the current thread until the specified counter reaches zero.
        *
        * @param counter Pointer to the TaskCounter object to wait for.
        *  @param pinToCurrentThread If set to true, the function will only unblock if called from the same thread as the counter.
        *
        * @warning Calling this function from multiple threads simultaneously without setting `pinToCurrentThread` to true may result in incorrect behavior.
        *
        */

        void waitForCounter(TaskCounter *counter, bool pinToCurrentThread = false);


        /**
        * @brief Get the index of the current thread.
        *
        * This function returns the index of the current thread.
        *
        * @return The index of the current thread.
        */

        HEXEN_NOINLINE u32 getCurrentThreadIndex() const;


        /**
        * @brief Retrieves the index of the current fiber.
        *
        * This function returns the index of the current fiber. The current fiber
        * refers to the fiber that is currently executing.
        *
        * @return The index of the current fiber.
        */


        u32 getCurrentFiberIndex() const;


        /**
        * @brief Returns the current count of threads.
        *
        * This function returns the current count of threads.
        * It is a const member function and does not throw any exceptions.
        *
        * @return The current count of threads.
        */

        u32 getThreadCount() const noexcept
        {
            return numberOfThreads;
        }


        /**
        * @brief Retrieves the fiber count.
        *
        * This function returns the fiber count as an integer value. The fiber count represents
        * the number of fiber optic cables present.
        *
        * @return The fiber count as an integer value.
        *
        * @note This function is marked as `const` and `noexcept`, indicating that it does not modify the
        * internal state of the object and does not throw any exceptions.
        */

        u32 getFiberCount() const noexcept
        {
            return fiberPoolSize;
        }

        /**
        * @brief Sets the behavior when trying to perform an operation on an empty queue.
        *
        * This function allows the behavior to be set when attempting to perform an operation on an empty queue.
        * The behavior can be one of the following options: ABORT, RETURN_DEFAULT, or THROW_EXCEPTION.
        *
        * @param behavior The behavior to set when trying to perform an operation on an empty queue.
        *                 It must be one of the EmptyQueueBehavior enum values: ABORT, RETURN_DEFAULT, or THROW_EXCEPTION.
        */

        void setEmptyQueueBehavior(EmptyQueueBehavior const behavior)
        {
            emptyQueueBehavior.store(behavior, std::memory_order_relaxed);
        }

    private:

        /**
        * @brief Perform cleanup of a thread's local storage and task buffer.
        *
        * This function cleans up the given thread's local storage and task buffer.
        *
        * @param tls The reference to the ThreadLocalStorage object to be cleaned up.
        * @param taskBuffer A pointer to the TaskBuffer vector to be cleaned up.
        *
        */

        void cleanup(ThreadLocalStorage &tls, std::vector<TaskBundle> *taskBuffer);


        /**
        * @brief Retrieves the next high priority task from the given task buffer.
        *
        * This function searches through the task buffer to find the task with the highest priority.
        * The task is then assigned to the provided 'nextTask' variable.
        *
        * @param nextTask A pointer to a TaskBundle object where the next high priority task will be stored.
        * @param taskBuffer A pointer to a vector containing the task buffer.
        *
        *
        */

        bool getNextHighPriorityTask(TaskBundle *nextTask, std::vector<TaskBundle> *taskBuffer);

        /**
        * @brief Get the next task with normal priority from the task bundle.
        *
        * This function retrieves the next task with normal priority from the given task bundle and stores it in the nextTask parameter.
        *
        * @param nextTask A pointer to a TaskBundle object that will hold the next normal priority task.
        *
        * @note The nextTask parameter should be a valid pointer to a TaskBundle object.
        *
        * @return void
        */

        bool getNextNormalPriorityTask(/***/TaskBundle *nextTask);

        /**
        * @brief Checks if a task in the provided TaskBundle is ready to execute.
        *
        * This function takes a pointer to a TaskBundle and checks if there is any task in the bundle
        * that is ready to execute. A task is considered ready to execute if all its dependencies have
        * been completed.
        *
        * @param bundle Pointer to the TaskBundle instance to check.
        * @return Returns true if there is a task ready to execute, false otherwise.
        *
        * @see TaskBundle
        */

        bool taskIsReadyToExecute(TaskBundle *bundle) const;

        /**
        * @brief Get the index of the next available fiber.
        *
        * This function returns the index of the next free fiber in a pool of fibers.
        *
        * @return int The index of the next available fiber.
        */

        u32 getNextFreeFiberIndex() const;

        /**
        * @brief Cleans up old fiber.
        *
        * This function is responsible for cleaning up the old fiber. It should be called
        * whenever the fiber has completed its execution and is no longer needed.
        *
        * @note This function does not return any value.
        */

        void cleanUpOldFiber();


        /**
        * @brief Waits for the internal counter value to reach the specified value.
        *
        * This function blocks the execution until the internal counter of the provided BaseCounter object
        * reaches the specified value. The counter value can be accessed using the getValue() method of the BaseCounter class.
        *
        * @param counter A pointer to the BaseCounter object to monitor its internal counter value.
        * @param value The value to wait for the internal counter to reach.
        * @param pinToCurrentThread True if the function should be pinned to the current thread, false otherwise.
        *
        */

        void waitForCounterInternal(BaseCounter *counter,u32 value, bool pinToCurrentThread);


        /**
        * @brief Adds a ready fiber to the given bundle.
        *
        * This function is used to add a ready fiber to a bundle, given the pinned thread index and the bundle itself.
        *
        * @param pinnedThreadIndex The index of the pinned thread to which the fiber belongs.
        * @param bundle A pointer to the ReadyFiberBundle to which the fiber should be added.
        *
        * @note This function assumes that the bundle is valid and has enough capacity to store the fiber.
        *       It does not perform any checks to verify these conditions.
        * @warning Make sure the pinnedThreadIndex is within the valid range of indices for the given bundle.
        *
        * @return None.
        */

        void addReadyFiber(u32 pinnedThreadIndex, ReadyFiberBundle *bundle);

        /**
        * @brief Function pointer type for thread start routine.
        *
        * This function pointer type is used to define the signature of the
        * function that will be executed when a new thread starts. This function
        * takes a single argument of type void pointer.
        *
        * @param arg The argument to be passed to the thread start routine.
        *
        * @return None.
        */

        static HEXEN_THREAD_FUNC_DECL threadStartFunction(vptr arg);


        /**
        * @brief Function to start a fiber.
        *
        * This function is used to start a fiber by executing the provided function.
        *
        * @param arg A pointer to any user-defined data that needs to be passed to the fiber function.
        */

        static void fiberStartFunction(vptr arg);

        /**
        * @brief This function represents the function that will be executed by a
        *        thread when it is terminated.
        *
        * @param arg A pointer to the argument that was passed to the thread during its creation.
        *
        */

        static void threadEndFunction(vptr arg);
    };

}
