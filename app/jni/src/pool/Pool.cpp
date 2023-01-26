//
// Created by cx9ps3 on 19.01.23.
//

#include <cstdlib>
#include "Pool.h"
template<class T>
Pool<T>::Pool(int numberOfObjects)
{
    objects = new int[numberOfObjects];
    this->numberOfObjects = numberOfObjects;
    if(objects == nullptr)
    {
        SDL_Log("Failed to allocate memory in pool.\n");
        exit(-1);
    }
}

template<class T>
Pool<T>::~Pool()
{
    delete []objects;
    objects = nullptr;
}

template<class T>
T *Pool<T>::create()
{
    T *object = &objects[usedObjects];
    usedObjects++;
    return object;
}

template<class T>
void Pool<T>::remove()
{
    usedObjects--;
}

template<class T>
T *Pool<T>::getObjects()
{
    return objects;
}

template<class T>
int Pool<T>::getUsedObjects()
{
    return usedObjects;
}