//
// Created by cx9ps3 on 13.07.2023.
//

#include "DebugGridComponent.h"

#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif

edit::comp::rend::DebugGridComponent::DebugGridComponent(const std::string &vertexShaderPath,const std::string &fragmentShaderPath)
{
    shaderProgram = core::mem::make_shared<core::rend::shader::ShaderProgram>(vertexShaderPath,fragmentShaderPath);

    grid = core::mem::make_unique<core::Grid>();

    if(grid != nullptr)
    {
        auto slices = grid->getNumberOfCells();
        for(core::i32 j = 0; j <= slices; ++j)
        {
            for(core::i32 i = 0; i <= slices; ++i)
            {
                float x = (float)i - grid->getUnitSize().x / (float)grid->getNumberOfCells();;
                float y = 0;
                float z = (float)j - grid->getUnitSize().y / (float)grid->getNumberOfCells();;
                vertices.emplace_back(x, y, z);
            }
        }

        for(core::i32 j = 0; j<slices; ++j)
        {
            for(core::i32 i = 0; i<slices; ++i)
            {

                int row1 =  j    * (slices+1);
                int row2 = (j+1) * (slices+1);

                indices.push_back(glm::uvec4(row1+i, row1+i+1, row1+i+1, row2+i+1));
                indices.push_back(glm::uvec4(row2+i+1, row2+i, row2+i, row1+i));

            }
        }

    }

    VAO.bind();
    VBO.bind(vertices);
    EBO.bind(indices);
    attributes.add(3,3,0);
    VBO.unbind();
    VAO.unbind();
    EBO.unbind();

    lenght = indices.size() * 4;

}

void edit::comp::rend::DebugGridComponent::draw() noexcept
{
    glEnable(GL_DEPTH_TEST);

    shaderProgram->use();
    shaderProgram->setMatrix4Uniform("model" , getTransformMatrix());
    shaderProgram->setMatrix4Uniform("projection",getProjectionMatrix());
    shaderProgram->setMatrix4Uniform("view" , getViewMatrix());
    shaderProgram->setVector3Uniform("color",color);


    VAO.bind();

    glDrawElements(GL_LINES, lenght, GL_UNSIGNED_INT, nullptr);

    VAO.unbind();

    glDisable(GL_DEPTH_TEST);
}
