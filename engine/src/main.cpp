//
// Created by cx9ps3 on 22.12.22.
//
#define main SDL_main
#include "core/application/Application.h"

extern "C" __attribute__((visibility("default"))) int SDL_main(int argc, char** argv)
{
    core::Application application;
    application.run();
    return(0);
}