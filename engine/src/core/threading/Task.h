#pragma once
#include "../Types.h"

namespace core::threading
{
    class TaskScheduler;

    using TaskFunction = void (*)(TaskScheduler *taskScheduler ,vptr arg);

    struct Task
    {
        TaskFunction Function;
        vptr *ArgumentsData;
    };

    enum class TaskPriority
    {
        High,
        Normal,
    };
}
