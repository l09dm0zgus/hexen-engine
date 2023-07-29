//
// Created by cx9ps3 on 29.07.2023.
//

#include "TaskSystem.h"

core::threading::TaskScheduler sys::TaskSystem::scheduler;
core::threading::TaskCounter sys::TaskSystem::counter(&scheduler);

void sys::TaskSystem::waitForCounter(core::i32 value)
{
    scheduler.waitForCounter(&counter,value);
}

void sys::TaskSystem::initialize()
{
    scheduler.initialize();
}

void sys::TaskSystem::addTasks(core::threading::TaskPriority priority,const std::array<core::threading::Task, 400> &tasks)
{
    scheduler.addTasks(tasks,priority,&counter);
}
