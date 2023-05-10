//
// Created by cx9ps3 on 19.01.23.
//

#ifndef BATTLEBLAZE_RENDERCOMPONENT_H
#define BATTLEBLAZE_RENDERCOMPONENT_H
#include "../IComponent.h"
#include "../../core/camera/Camera.h"
#include <glm/glm.hpp>
#include <iostream>

namespace comp::rend
{
    class RenderComponent : public IComponent
    {
    public:
        ~RenderComponent();
        virtual void start() override;
        virtual void update(float deltaTime) override;
        void setCamera(core::Camera *camera);
        virtual void create(const std::string &vertexShaderPath , const std::string &fragmentShaderPath) = 0;
        virtual void draw() = 0;

    protected:
        core::Camera *camera;
    };
}



#endif //BATTLEBLAZE_RENDERCOMPONENT_H
