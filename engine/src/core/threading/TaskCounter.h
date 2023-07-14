//
// Created by cx9ps3 on 14.07.2023.
//

#ifndef HEXENEDITOR_TASKCOUNTER_H
#define HEXENEDITOR_TASKCOUNTER_H
#include <atomic>
#include "../Types.h"

namespace core::threading
{
    class TaskManager;
    namespace detail
    {
        class BaseCounter
        {
        private:
            friend class Manager;
        protected:
            std::atomic<u32> counter{0};

            struct WaitingFibers
            {
                u16 fiberIndex = UINT16_MAX;
                std::atomic_bool* fiberStored{nullptr};
                u32 targetValue{0};
                std::atomic_bool  inUse{true};
            };

            const u8 nubmberOfWaitingFibers;

            WaitingFibers* waitingFibers{nullptr};
            std::atomic_bool* freeWaitingSlots;

            void initializeWaitingFibers();

            TaskManager *manager;

            bool addWaitingFiber(u16 fiberIndex ,u32 targetValue,std::atomic_bool* fiberStored);
            void checkWaitingFibers(u32 value);

        public:
            BaseCounter(TaskManager* manager , u8 numberOfWaitingFibers,WaitingFibers* waitingFibers , std::atomic_bool* freeWaitingSlots);
            virtual ~BaseCounter() = default;

            u32 increment(u32 by = 1);
            u32 decrement(u32 by = 1);

            u32 getValue() const;

        };
        struct TinyCounter : public  BaseCounter
        {
            explicit TinyCounter(TaskManager *manager);
            ~TinyCounter() override = default;

            std::atomic_bool freeWaitingSlot{};
            WaitingFibers waitingFiber;
        };
    }
    class TaskCounter : public detail::BaseCounter
    {
    public:
        static const constexpr  u8 MAX_WAITING = 4;
        explicit TaskCounter(TaskManager *manager);
        ~TaskCounter() override = default;
    private:
        std::atomic_bool freeWaitingSlots[MAX_WAITING]{};
        WaitingFibers waitingFibers[MAX_WAITING];
    };
}



#endif //HEXENEDITOR_TASKCOUNTER_H
