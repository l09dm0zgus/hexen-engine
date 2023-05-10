//
// Created by cx9ps3 on 03.01.23.
//

#ifndef BATTLEBLAZE_SHADERPROGRAM_H
#define BATTLEBLAZE_SHADERPROGRAM_H
#include "ShaderFile.h"
#include <glm/glm.hpp>
#include "../../Types.h"
namespace core::rend::shader
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string &vertexShaderPath,const std::string &fragmentShaderPath);
        ~ShaderProgram();
        void use();
        void setIntUniform(const std::string &uniformVariable,i32 value);
        void setMatrix4Uniform(const std::string &uniformVariable,const glm::mat4 &matrix);
    private:
        ShaderFile vertexShaderFile;
        ShaderFile fragmentShaderFile;
        i32 vertexShader{0};
        i32 fragmentShader{0};
        i32 shaderProgram{0};
        char* fragmentShaderText{nullptr};
        char* vertexShaderText{nullptr};

        void compileVertexShader();
        void compileFragmentShader();
        void linkShaders();
        void showCompilerLog(u32 shader);
        void showLinkerLog();
    };
}
#endif //BATTLEBLAZE_SHADERPROGRAM_H
