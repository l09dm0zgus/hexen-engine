//
// Created by cx9ps3 on 09.01.23.
//

#ifndef BATTLEBLAZE_TRANSFORM_H
#define BATTLEBLAZE_TRANSFORM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
    void setPosition(const glm::vec3 &newPosition);
    void setRotattion(const glm::vec3 &newRotation);
    void setScale(const glm::vec3 &newScale);
    glm::vec3 getScale();
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::mat4 getTransformMatrix();
    glm::mat4 getTransformMatrix(const glm::mat4 &parentTransform);
private:
    glm::mat4 transformMatrix{1.0f};
    glm::vec3 position{1.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{1.0f};
    float angle;
    void updateTransformMatrix();
};


#endif //BATTLEBLAZE_TRANSFORM_H
