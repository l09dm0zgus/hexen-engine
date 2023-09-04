//
// Created by cx9ps3 on 09.05.2023.
//

#include "AllocatedObject.h"
#include <SDL3/SDL.h>
namespace core::mem
{
    void handler()
    {
        SDL_Log("Memory allocation failed.\n Not enough memory in pool.\n Please increase memory pool size!\n");
        std::set_new_handler(nullptr);
    }
}


std::unique_ptr<core::mem::MemoryPool> core::mem::AllocatedObject::memoryPool = nullptr;
/**
 * @brief Overloaded new operator for allocating memory for objects of AllocatedObject.
 *
 * This function is responsible for allocating memory for objects of AllocatedObject class.
 * It is an overloaded version of the new operator that takes the size of the object as a parameter and returns a pointer to the allocated memory.
 *
 * @param size The size of the object to be allocated.
 * @return A pointer to the allocated memory for the object.
 */

core::vptr core::mem::AllocatedObject::operator new(u64 size)
{
    if(memoryPool == nullptr)
    {
        memoryPool = std::make_unique<MemoryPool>(POOL_SIZE);
    }
    if(size == 0)
    {
        size = 1;
    }
    while (true)
    {
        auto  memory = memoryPool->allocate(size);
        if(memory != nullptr)
        {
            return memory;
        }
        std::new_handler handler = std::get_new_handler();
        if(handler != nullptr)
        {
            handler();
        }
        else
        {
            throw std::bad_alloc();
        }
    }
}

void core::mem::AllocatedObject::operator delete(core::vptr address) noexcept
{
    if(address == nullptr)
    {
        SDL_Log("Failed to freed memory!\n");
    }
    if(memoryPool != nullptr)
    {
        memoryPool->free(address);
    }
}

core::mem::AllocatedObject::AllocatedObject()
{
    std::set_new_handler(handler);
}

