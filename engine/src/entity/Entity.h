//
// Created by cx9ps3 on 14.05.2023.
//

#ifndef BATTLEBLAZE_ENTITY_H
#define BATTLEBLAZE_ENTITY_H
#include "../core/uuid/uuid.h"
#include "../core/Types.h"
#include "../components/Component.h"
#include <iostream>

namespace ent
{
    class Entity
    {
    public:
        Entity();
        explicit Entity(std::string UUID);
        virtual ~Entity() = default;
        Entity(Entity &&entity) = delete;
        Entity(const Entity &entity) = delete;
        Entity& operator=(Entity &&entity) = delete;
        Entity& operator=(const Entity &entity) = delete;
        std::string getUUID()  const noexcept;
        template<class T> void addComponent(T &&component);
        template<class T, class... Ts> void addComponent(Ts&&... params);
        template<class T> T getComponentByName(const std::string &name);
        template<class T> T getComponentByUUID(const std::string &UUID);
    private:
        std::string UUID;
        core::HashTable<std::string,std::shared_ptr<comp::Component>> components;
    };

}



#endif //BATTLEBLAZE_ENTITY_H
