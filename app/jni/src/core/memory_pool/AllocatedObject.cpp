//
// Created by cx9ps3 on 09.05.2023.
//

#include "AllocatedObject.h"
#include "SDL_log.h"

std::unique_ptr<mem::MemoryPool> mem::AllocatedObject::memoryPool = nullptr;
vptr mem::AllocatedObject::operator new(u64 size)
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

void mem::AllocatedObject::operator delete(vptr address) noexcept
{
    if(address == nullptr || memoryPool == nullptr)
    {
        SDL_Log("Failed to freed memory!\n");
    }
    memoryPool->free(address);
}
