//
// Created by cx9ps3 on 10.01.23.
//

#ifndef BATTLEBLAZE_CAMERA_H
#define BATTLEBLAZE_CAMERA_H
#include <glm/glm.hpp>
namespace core
{
    class Camera
    {
    public:
        Camera(int viewportWidth,int viewportHeight,float FOV);
        void setPosition(const glm::vec3 &newPosition);
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();

    private:
        glm::vec3 position{0.0f,-6.0f,8.0f};
        glm::mat4 view{1.0f};
        glm::mat4 projection{1.0f};
        glm::vec3 cameraTarget{0.0f,0.0f,-1.0f};
        glm::vec3 cameraUp{0.0f,1.0f,0.0f};
        void updateViewMatrix();
    };
}

#endif //BATTLEBLAZE_CAMERA_H
