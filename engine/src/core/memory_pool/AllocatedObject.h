//
// Created by cx9ps3 on 09.05.2023.
//

#ifndef BATTLEBLAZE_ALLOCATEDOBJECT_H
#define BATTLEBLAZE_ALLOCATEDOBJECT_H


#include "../Types.h"
#include "MemoryPool.h"
#include <memory>
namespace core::mem
{
    class AllocatedObject
    {
    public:
        void operator delete(vptr address) noexcept;
        vptr operator new(u64 size);
        AllocatedObject() = default;
        virtual ~AllocatedObject() = default;
        AllocatedObject(const AllocatedObject &allocationManager) = default;
        AllocatedObject(AllocatedObject &&allocationManager) = default;

        AllocatedObject& operator=(const AllocatedObject &allocationManager) = default;
        AllocatedObject& operator=(AllocatedObject &&allocationManager) = default;



    private:
        static constexpr u64 POOL_SIZE = 4096;
        static std::unique_ptr<MemoryPool> memoryPool;
    };
    template<class T, class... Ts>
    inline auto make_unique(Ts&&... params)
    {
        return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
    }
    template<class T, class... Ts>
    inline auto make_shared(Ts&&... params)
    {
        return std::shared_ptr<T>(new T(std::forward<Ts>(params)...));
    }
}


#endif //BATTLEBLAZE_ALLOCATEDOBJECT_H
