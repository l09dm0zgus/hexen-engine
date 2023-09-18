//
// Created by cx9ps3 on 29.07.2023.
//

#include "TaskSystem.hpp"

hexen::engine::core::threading::TaskScheduler hexen::engine::systems::TaskSystem::scheduler;
hexen::engine::core::threading::TaskCounter hexen::engine::systems::TaskSystem::counter(&scheduler);

void hexen::engine::systems::TaskSystem::waitForCounter(core::i32 value)
{
	scheduler.waitForCounter(&counter, value);
}

void hexen::engine::systems::TaskSystem::initialize()
{
	scheduler.initialize();
}

void hexen::engine::systems::TaskSystem::addTasks(core::threading::TaskPriority priority, const std::array<core::threading::Task, 400> &tasks)
{
	scheduler.addTasks(tasks, priority, &counter);
}
