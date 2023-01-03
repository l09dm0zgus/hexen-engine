//
// Created by cx9ps3 on 03.01.23.
//

#ifndef BATTLEBLAZE_SHADERPROGRAM_H
#define BATTLEBLAZE_SHADERPROGRAM_H
#include "ShaderFile.h"

class ShaderProgram
{
public:
    ShaderProgram(const std::string &vertexShaderPath,const std::string &fragmentShaderPath);
    ~ShaderProgram();
    void use();
private:
    ShaderFile vertexShaderFile;
    ShaderFile fragmentShaderFile;
    unsigned int vertexShader{0};
    unsigned int fragmentShader{0};
    unsigned int shaderProgram{0};

    void compileVertexShader();
    void compileFragmentShader();
    void linkShaders();
    void showCompilerLog(unsigned int shader);
    void showLinkerLog();
};


#endif //BATTLEBLAZE_SHADERPROGRAM_H
