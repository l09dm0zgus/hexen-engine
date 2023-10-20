//
// Created by cx9ps3 on 14.05.2023.
//

#include "Entity.h"
#include "../profiling/Profiling.hpp"

hexen::engine::entity::Entity::Entity()
{
	HEXEN_ADD_TO_PROFILE();
	UUID = generateUUIDV4();
}

hexen::engine::entity::Entity::Entity(std::string UUID) : UUID(std::move(UUID))
{
	HEXEN_ADD_TO_PROFILE();
}

std::string hexen::engine::entity::Entity::getUUID() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return UUID;
}
