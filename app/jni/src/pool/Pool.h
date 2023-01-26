//
// Created by cx9ps3 on 19.01.23.
//

#ifndef BATTLEBLAZE_POOL_H
#define BATTLEBLAZE_POOL_H
#ifndef  __ANDROID__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif


template<class T>class Pool
{
public:
    Pool(int numberOfObjects);
    ~Pool();
    T *create();
    void remove();
    T *getObjects();
    int getUsedObjects();
private:
    T *objects{nullptr};
    int usedObjects{0};
    int numberOfObjects{0};
};

#endif //BATTLEBLAZE_POOL_H
