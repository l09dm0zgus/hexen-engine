//
// Created by cx9ps3 on 14.07.2023.
//

#include "TaskCounter.h"
#include "TaskManager.h"
#include "ThreadLocalStorage.h"


core::threading::TaskCounter::TaskCounter(core::threading::TaskManager *manager) : manager(manager)
{

}

core::u32 core::threading::TaskCounter::increment(core::u32 by)
{
    auto previous = counter.fetch_add(by);
    return previous;
}

core::u32 core::threading::TaskCounter::decrement(core::u32 by)
{
    auto previous = counter.fetch_sub(by);
    return previous;
}

core::u32 core::threading::TaskCounter::getValue() const
{
    return counter.load(std::memory_order_seq_cst);
}
