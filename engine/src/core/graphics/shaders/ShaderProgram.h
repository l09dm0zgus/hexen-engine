//
// Created by cx9ps3 on 03.01.23.
//

#ifndef BATTLEBLAZE_SHADERPROGRAM_H
#define BATTLEBLAZE_SHADERPROGRAM_H
#include "ShaderFile.h"
#include <glm/glm.hpp>
#include "../../memory_pool/AllocatedObject.h"
namespace core::rend::shader
{
class ShaderProgram : public mem::AllocatedObject
    {
    public:
        ShaderProgram(const std::string &vertexShaderPath,const std::string &fragmentShaderPath);
        ~ShaderProgram();
        void use() const noexcept;
        void setIntUniform(const std::string &uniformVariable,i32 value) const;
        void setMatrix4Uniform(const std::string &uniformVariable,const glm::mat4 &matrix) const;
    private:
        ShaderFile vertexShaderFile;
        ShaderFile fragmentShaderFile;
        u32 vertexShader{0};
        u32 fragmentShader{0};
        u32 shaderProgram{0};
        char* fragmentShaderText{nullptr};
        char* vertexShaderText{nullptr};

        void compileVertexShader();
        void compileFragmentShader();
        void linkShaders();
        void showCompilerLog(u32 shader) const noexcept;
        void showLinkerLog() const noexcept;
    };
}
#endif //BATTLEBLAZE_SHADERPROGRAM_H
