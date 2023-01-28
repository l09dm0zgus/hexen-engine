//
// Created by cx9ps3 on 28.01.23.
//

#ifndef BATTLEBLAZE_BASECOMPONENTPOOL_H
#define BATTLEBLAZE_BASECOMPONENTPOOL_H
#include "../components/IComponent.h"
#include "../core/graphics/texture/Texture.h"
#include <type_traits>
#include "BasePool.h"
template<typename T, std::enable_if_t<std::is_base_of_v<IComponent, T>, bool> = true>
class BaseComponentPool
{
private:
    BasePool<T> *basePool{nullptr};
public:
    BaseComponentPool(int numberOfObjects)
    {
        basePool = new BasePool<T>(numberOfObjects);
    }
    ~BaseComponentPool()
    {
        delete basePool;
        basePool = nullptr;
    }
    T *create()
    {
        return basePool->create();
    }
    void remove(T* object)
    {
        auto iterator = std::find_if(basePool->getObjects()->begin(),basePool->getObjects()->end(),[&object](T o){
            if(o.uuid == object->uuid)
            {
                return true;
            }
        });
        if (iterator != basePool->getObjects()->end())
        {
            std::vector<bool> *isUsing = basePool->getIsUsing();
            *isUsing[*iterator] = false;
        }
        basePool->remove();
    }
    std::vector<T> *getObjects()
    {
        basePool->getObjects();
    }
    int getNumberOfUsingObjects()
    {
        return basePool->getNumberOfUsingObjects();
    }

};
#endif //BATTLEBLAZE_BASECOMPONENTPOOL_H
