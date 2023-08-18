//
// Created by cx9ps3 on 18.08.2023.
//

#include "TaskSchedulerSettings.h"
#include <filesystem>
#include <fstream>

core::threading::TaskSchedulerSettings::TaskSchedulerSettings()
{
    if(!std::filesystem::exists(pathToSettingsFile))
    {
        settingsFile["task_scheduler"]["fiber_pool_size"] = 400;
        settingsFile["task_scheduler"]["used_cores"] = 1;
        std::ofstream file(pathToSettingsFile);
        file << settingsFile.dump(2);
    }
    else
    {
        std::ifstream file(pathToSettingsFile);
        settingsFile = nlohmann::json::parse(file);
    }
}

core::u32 core::threading::TaskSchedulerSettings::getFiberPoolSize() const
{
    return settingsFile["task_scheduler"]["fiber_pool_size"];
}

core::u32 core::threading::TaskSchedulerSettings::getUsedCores() const
{
    return settingsFile["task_scheduler"]["used_cores"];
}

void core::threading::TaskSchedulerSettings::setFiberPoolSize(core::u32 fiberPoolSize)
{
    settingsFile["task_scheduler"]["fiber_pool_size"] = fiberPoolSize;
    std::ofstream file(pathToSettingsFile);
    file << settingsFile.dump(2);
}

void core::threading::TaskSchedulerSettings::setUsedCores(core::u32 usedCores)
{
    settingsFile["task_scheduler"]["used_cores"] = usedCores;
    std::ofstream file(pathToSettingsFile);
    file << settingsFile.dump(2);
}

