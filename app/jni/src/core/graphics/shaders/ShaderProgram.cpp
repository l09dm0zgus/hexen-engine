//
// Created by cx9ps3 on 03.01.23.
//

#include "ShaderProgram.h"
#ifndef  __ANDROID__
#include <GL/glew.h>
#include <SDL2/SDL.h>
#else
#include <GLES3/gl31.h>
#include <SDL.h>
#endif
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const std::string &vertexShaderPath,const std::string &fragmentShaderPath)
{
    vertexShaderFile.read(vertexShaderPath);
    fragmentShaderFile.read(fragmentShaderPath);
    compileVertexShader();
    compileFragmentShader();
    linkShaders();
}

void ShaderProgram::compileVertexShader()
{
    vertexShaderText = vertexShaderFile.getContent();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1,&vertexShaderText, nullptr);
    glCompileShader(vertexShader);
    showCompilerLog(vertexShader);
}

void ShaderProgram::showCompilerLog(unsigned int shader)
{
    int success{0};
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        SDL_Log("Error:Failed compile shader.What : %s",infoLog);
    }
}

void ShaderProgram::compileFragmentShader()
{
    fragmentShaderText = fragmentShaderFile.getContent();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1,&fragmentShaderText, nullptr);
    glCompileShader(fragmentShader);
    showCompilerLog(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderProgram::linkShaders()
{
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    showLinkerLog();
}

void ShaderProgram::showLinkerLog()
{
    int success{0};
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        SDL_Log("Error:Failed to link shader.What : %s",infoLog);

    }
}

void ShaderProgram::use()
{
    glUseProgram(shaderProgram);
}

void ShaderProgram::setIntUniform(const std::string &uniformVariable, int value)
{
    glUniform1i(glGetUniformLocation(shaderProgram, uniformVariable.c_str()), value);
}

void ShaderProgram::setMatrix4Uniform(const std::string &uniformVariable, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniformVariable.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
