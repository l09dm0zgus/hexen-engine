//
// Created by cx9ps3 on 13.07.2023.
//

#ifndef HEXENEDITOR_THREADLOCALSTORAGE_H
#define HEXENEDITOR_THREADLOCALSTORAGE_H

#include <core/Types.h>
#include <vector>
#include <atomic>
#include "Fiber.h"

namespace core::threading
{
    enum class FiberDestination : u8
    {
        None,
        Waiting,
        Pool
    };
    struct ThreadLocalStorage
    {
        ThreadLocalStorage() = default;
        ~ThreadLocalStorage() = default;

        u8 threadIndex = UINT8_MAX;
        bool setAffinity = false;

        Fiber threadFiber;

        u16 currentFiberIndex = UINT16_MAX;
        u16 previousFiberIndex = UINT16_MAX;
        std::atomic_bool* isPreviousFiberStored = nullptr;
        FiberDestination previousFiberDestination = FiberDestination::None;

        std::vector<std::pair<u16,std::atomic_bool*>> readyFibers;

    };
}

#endif //HEXENEDITOR_THREADLOCALSTORAGE_H
