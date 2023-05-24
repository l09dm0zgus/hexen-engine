//
// Created by cx9ps3 on 22.12.22.
//
#ifndef  __ANDROID__
#define main main
#else
#define main SDL_main
#endif

#include "core/application/Application.h"

extern "C" __attribute__((visibility("default"))) int main(int argc, char** argv)
{
    core::Application application;
    application.run();
    return(0);
}