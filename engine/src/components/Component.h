//
// Created by cx9ps3 on 19.01.23.
//

#ifndef BATTLEBLAZE_COMPONENT_H
#define BATTLEBLAZE_COMPONENT_H

#include <string>
#include "../core/memory_pool/AllocatedObject.h"
namespace comp
{
    class Component : public core::mem::AllocatedObject
    {
    public:
        ~Component() = default;
        virtual void start() = 0;
        virtual void update(float deltaTime) = 0;

        template<class T> void setOwnerUUID(T&& newOwnerUUID) noexcept
        {
            ownerUUID = std::forward<T>(newOwnerUUID);
        }
        std::string getOwnerUUID() const noexcept
        {
            return ownerUUID;
        }

        template<class T> void setName(T&& newName) noexcept
        {
            name = std::forward<T>(newName);
        }

        std::string getName() const noexcept
        {
            return name;
        }
    private:
        std::string  ownerUUID;
        std::string name;
    };
}


#endif //BATTLEBLAZE_COMPONENT_H
