//
// Created by cx9ps3 on 29.07.2023.
//

#pragma once
#include "../memory_pool/AllocatedObject.h"
#include <chrono>

namespace core
{
    class Window;
    class GameLoop : public mem::MemoryPool
    {
    public:
        virtual ~GameLoop() = default;
        GameLoop(const GameLoop&) = delete;
        GameLoop(GameLoop&&) = delete;
        GameLoop& operator=(const GameLoop&) = delete;
        GameLoop& operator=(GameLoop&&) = delete;
        virtual void start();
        virtual void loop(const std::shared_ptr<Window> &window);
    protected:
        void initializeClock();
        void setFrameStart();
        void setAccumulator();
        float getAlpha();
        std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<double>> framesStart;
        const float framesLimit{240.0f};
        const float deltaTime = 1 / framesLimit;
        float accumulator{0};
        const float msPerUpdate{0.2f};
    };
}


