//
// Created by cx9ps3 on 18.08.2023.
//

#pragma once
#include "../../Types.hpp"
#include "../../memory_pool/AllocatedObject.hpp"
#include <nlohmann/json.hpp>

namespace hexen::engine::core::threading
{
	class TaskSchedulerSettings : public memory::AllocatedObject
	{
	public:
		/**
        * @class TaskSchedulerSettings
        * @brief This class represents the settings for a thread pool.
        *
        * The TaskSchedulerSettings class encapsulates the configurable settings for a thread pool.
        * These settings include the maximum number of threads.
        *
        * The default constructor creates a TaskSchedulerSettings object with default values for all settings.
        * The settings can be modified using the appropriate setter methods.
        *
        * @see TaskScheduler
        */

		TaskSchedulerSettings();

		/**
        * @brief Get the size of the fiber pool.
        *
        * This function returns the current size of the fiber pool.
        *
        * @return The size of the fiber pool as an integer.
        */

		[[nodiscard]] u32 getFiberPoolSize() const;

		/**
        * @brief Get the number of used cores.
        *
        * This function returns the number of cores that are currently being used in a multi-core system.
        * The value returned is constant and does not modify the state of the system.
        *
        * @return The number of used cores as an integer.
        */

		[[nodiscard]] u32 getUsedCores() const;

		/**
        * Set the size of the fiber pool.
        *
        * @param fiberPoolSize The new size of the fiber pool.
        */

		void setFiberPoolSize(u32 fiberPoolSize);

		/**
        * @brief Set the number of used cores.
        *
        * This function sets the number of used cores to the specified value.
        *
        * @param usedCores The number of used cores to set.
        */

		void setUsedCores(u32 usedCores);

	private:
		/**
        * @brief The file where the settings are stored.
        */

		nlohmann::json settingsFile;

		/**
        * @brief The path to the settings file.
        */

		std::string pathToSettingsFile = ".settings/tasks_settings.hxs";
	};
}// namespace hexen::engine::core::threading
