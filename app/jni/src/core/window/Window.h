//
// Created by cx9ps3 on 28.12.22.
//

#ifndef BATTLEBLAZE_WINDOW_H
#define BATTLEBLAZE_WINDOW_H
#ifndef  __ANDROID__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#include <string>
class Window
{
public:
    Window(const std::string &title);
    ~Window();
    void swapBuffers();
    void close();
    void clear();

private:
    SDL_DisplayMode displayMode;
    SDL_Window* window{nullptr};
    SDL_GLContext glContext;
    int height;
    int width;

};


#endif //BATTLEBLAZE_WINDOW_H
