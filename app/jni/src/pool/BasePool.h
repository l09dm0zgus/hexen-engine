//
// Created by cx9ps3 on 19.01.23.
//

#ifndef BATTLEBLAZE_BASEPOOL_H
#define BATTLEBLAZE_BASEPOOL_H
#ifndef  __ANDROID__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#include <vector>
template<typename T>
class BasePool
{
public:
    BasePool(int numberOfObjects);
    T* create();
    void remove();
    std::vector<T> *getObjects();
    std::vector<bool> *getIsUsing();
    int getNumberOfUsingObjects();
private:
    void reserve(int numberOfObjects);
    std::vector<T> objects;
    std::vector<bool> isUsing;
    int numberOfUsingObjects{0};
    int numberOfObjects{0};

};

template<typename T>
BasePool<T>::BasePool(int numberOfObjects)
{
    reserve(numberOfObjects);
    this->numberOfObjects = numberOfObjects;
}

template<typename T>
T *BasePool<T>::create()
{
    auto iterator = std::find(isUsing.begin(),isUsing.end(),false);
    if(iterator == isUsing.end())
    {
        reserve(numberOfObjects*2);
    }

    T* object = &objects[numberOfUsingObjects];
    isUsing[numberOfUsingObjects] = true;
    numberOfUsingObjects++;
    return object;
}

template<typename T>
void BasePool<T>::reserve(int numberOfObjects)
{
    objects.reserve(numberOfObjects);
    isUsing.reserve(numberOfObjects);
    for(int i = 0;i < numberOfObjects;i++)
    {
        objects.emplace_back();
        isUsing.emplace_back(false);
    }
}

template<typename T>
std::vector<T> *BasePool<T>::getObjects()
{
    return &objects;
}

template<typename T>
std::vector<bool> *BasePool<T>::getIsUsing()
{
    return &isUsing;
}

template<typename T>
int BasePool<T>::getNumberOfUsingObjects()
{
    return numberOfUsingObjects;
}

template<typename T>
void BasePool<T>::remove()
{
    numberOfUsingObjects--;
}



#endif //BATTLEBLAZE_BASEPOOL_H
