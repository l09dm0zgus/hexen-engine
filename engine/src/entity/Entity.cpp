//
// Created by cx9ps3 on 14.05.2023.
//

#include "Entity.h"

#include <algorithm>
#include "../core/exceptions/ComponentNotFound.h"

hexen::engine::entity::Entity::Entity()
{
    UUID = generateUUIDV4();
}

hexen::engine::entity::Entity::Entity(std::string UUID)  : UUID(std::move(UUID))
{

}

std::string hexen::engine::entity::Entity::getUUID() const noexcept
{
    return UUID;
}

template<class T>
T hexen::engine::entity::Entity::getComponentByUUID(const std::string &UUID)
{
    return dynamic_cast<T>(components[UUID]);
}

template<class T>
T hexen::engine::entity::Entity::getComponentByName(const std::string &name)
{
    auto component = std::find_if(components.cbegin(),components.cend(), [name = name](auto& comp)
    {
        return  comp->getName() == name;
    });
    if(component != components.cend())
    {
        return dynamic_cast<T>(*component);
    }
    else
    {
        throw hexen::engine::exceptions::ComponentNotFound(name);
    }
}
