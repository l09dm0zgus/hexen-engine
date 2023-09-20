//
// Created by cx9ps3 on 14.05.2023.
//

#include "Entity.h"

hexen::engine::entity::Entity::Entity()
{
	UUID = generateUUIDV4();
}

hexen::engine::entity::Entity::Entity(std::string UUID) : UUID(std::move(UUID))
{
}

std::string hexen::engine::entity::Entity::getUUID() const noexcept
{
	return UUID;
}
