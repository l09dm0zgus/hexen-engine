//
// Created by cx9ps3 on 30.12.22.
//

#ifndef BATTLEBLAZE_APPLICATION_H
#define BATTLEBLAZE_APPLICATION_H

#include "../window/Window.h"

class Application
{
public:
    Application();
    ~Application();
    void run();
private:
     Window *window;
    SDL_Event sdlEvent;
};


#endif //BATTLEBLAZE_APPLICATION_H
