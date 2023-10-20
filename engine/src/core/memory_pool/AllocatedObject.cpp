//
// Created by cx9ps3 on 09.05.2023.
//

#include "AllocatedObject.hpp"
#include <SDL3/SDL.h>
namespace hexen::engine::core::memory
{
	void handler()
	{
		SDL_Log("Memory allocation failed.\n Not enough memory in pool.\n Please increase memory pool size!\n");
		std::set_new_handler(nullptr);
	}
}// namespace hexen::engine::core::memory


std::unique_ptr<hexen::engine::core::memory::MemoryPool> hexen::engine::core::memory::AllocatedObject::memoryPool = nullptr;

hexen::engine::core::vptr hexen::engine::core::memory::AllocatedObject::operator new(u64 size)
{
	HEXEN_ADD_TO_PROFILE();
	if (memoryPool == nullptr)
	{
		memoryPool = std::make_unique<MemoryPool>(POOL_SIZE);
	}
	if (size == 0)
	{
		size = 1;
	}
	while (true)
	{
		auto memory = memoryPool->allocate(size);
		if (memory != nullptr)
		{
			return memory;
		}
		std::new_handler handler = std::get_new_handler();
		if (handler != nullptr)
		{
			handler();
		}
		else
		{
			throw std::bad_alloc();
		}
	}
}

void hexen::engine::core::memory::AllocatedObject::operator delete(core::vptr address) noexcept
{
	HEXEN_ADD_TO_PROFILE();
	if (address == nullptr)
	{
		SDL_Log("Failed to freed memory!\n");
	}
	if (memoryPool != nullptr)
	{
		memoryPool->free(address);
	}
}

hexen::engine::core::memory::AllocatedObject::AllocatedObject()
{
	std::set_new_handler(handler);
}
