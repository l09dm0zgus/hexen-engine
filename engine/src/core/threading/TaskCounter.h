//
// Created by cx9ps3 on 14.07.2023.
//

#ifndef HEXENEDITOR_TASKCOUNTER_H
#define HEXENEDITOR_TASKCOUNTER_H
#include <atomic>
#include "../Types.h"

namespace core::threading
{
    class TaskManager;
    class TaskCounter
    {
    private:
        friend class Manager;

        std::atomic<u32> counter{0};
        TaskManager *manager;


    public:
        TaskCounter(TaskManager* manager);

        u32 increment(u32 by = 1);
        u32 decrement(u32 by = 1);

        u32 getValue() const;
    };
}



#endif //HEXENEDITOR_TASKCOUNTER_H
