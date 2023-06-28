//
// Created by cx9ps3 on 14.05.2023.
//

#include "Entity.h"

#include <algorithm>
#include "../core/exceptions/ComponentNotFound.h"

ent::Entity::Entity()
{
    UUID = generateUUIDV4();
}

ent::Entity::Entity(std::string UUID)  : UUID(std::move(UUID))
{

}

std::string ent::Entity::getUUID() const noexcept
{
    return UUID;
}

template<class T, class... Ts>
void ent::Entity::addComponent(Ts &&... params)
{
    components.set(generateUUIDV4(),core::mem::make_shared<T>(params...));
}

template<class T>
void ent::Entity::addComponent(T &&component)
{
    components.set(generateUUIDV4(),std::forward<T>(component));

}

template<class T>
T ent::Entity::getComponentByUUID(const std::string &UUID)
{
    return dynamic_cast<T>(components[UUID]);
}

template<class T>
T ent::Entity::getComponentByName(const std::string &name)
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
        throw core::exc::ComponentNotFound(name);
    }
}
