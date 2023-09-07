//
// Created by cx9ps3 on 19.01.23.
//

#pragma once

#include <string>
#include "../core/memory_pool/AllocatedObject.hpp"
namespace hexen::engine::components
{
    class Component : public core::memory::AllocatedObject
    {
    public:
        ~Component() override = default;
        virtual void start() = 0;
        virtual void update(float deltaTime) = 0;

        template<class T> void setOwnerUUID(T&& newOwnerUUID) noexcept
        {
            ownerUUID = std::forward<T>(newOwnerUUID);
        }
        [[nodiscard]] std::string getOwnerUUID() const noexcept
        {
            return ownerUUID;
        }

        template<class T> void setName(T&& newName) noexcept
        {
            name = std::forward<T>(newName);
        }

        [[nodiscard]] std::string getName() const noexcept
        {
            return name;
        }
    private:
        std::string  ownerUUID;
        std::string name;
    };
}
