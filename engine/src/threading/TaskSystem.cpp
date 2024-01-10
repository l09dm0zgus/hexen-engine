//
// Created by cx9ps3 on 29.07.2023.
//

#include "TaskSystem.hpp"
#include "../profiling/Profiling.hpp"

hexen::engine::core::threading::TaskScheduler hexen::engine::threads::TaskSystem::scheduler;
hexen::engine::core::threading::TaskCounter hexen::engine::threads::TaskSystem::counter(&scheduler);

void hexen::engine::threads::TaskSystem::waitForCounter(core::i32 value)
{
	HEXEN_ADD_TO_PROFILE();
	scheduler.waitForCounter(&counter, value);
}

void hexen::engine::threads::TaskSystem::initialize()
{
	HEXEN_ADD_TO_PROFILE();
	scheduler.initialize();
}

void hexen::engine::threads::TaskSystem::addTasks(core::threading::TaskPriority priority, const std::array<core::threading::Task, 400> &tasks)
{
	HEXEN_ADD_TO_PROFILE();
	scheduler.addTasks(tasks, priority, &counter);
}
