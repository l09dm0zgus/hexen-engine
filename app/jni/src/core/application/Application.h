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
    Application(const Application &application) = delete;
    Application(Application &&application) =delete;

    Application& operator=(const Application &application) = delete;
    Application& operator=(Application &&application) = delete;

    void run();
private:
     std::unique_ptr<Window> window;
     SDL_Event sdlEvent{};
};


#endif //BATTLEBLAZE_APPLICATION_H
