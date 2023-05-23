//
// Created by cx9ps3 on 09.05.2023.
//

#include "AllocatedObject.h"
#include <SDL3/SDL.h>


std::unique_ptr<core::mem::MemoryPool> core::mem::AllocatedObject::memoryPool = nullptr;
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
    if(address == nullptr || memoryPool == nullptr)
    {
        SDL_Log("Failed to freed memory!\n");
    }
    memoryPool->free(address);
}

