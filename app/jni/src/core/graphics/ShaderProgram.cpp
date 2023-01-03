//
// Created by cx9ps3 on 03.01.23.
//

#include "ShaderProgram.h"
#include <GLES3/gl31.h>
#include <SDL.h>

ShaderProgram::ShaderProgram(const std::string &vertexShaderPath,const std::string &fragmentShaderPath)
{
    vertexShaderFile.read(vertexShaderPath);
    fragmentShaderFile.read(fragmentShaderPath);
    compileFragmentShader();
    compileVertexShader();
    linkShaders();
}

void ShaderProgram::compileVertexShader()
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1,(const GLchar *const *)(vertexShaderFile.getContent()), nullptr);
    glCompileShader(vertexShader);
    showCompilerLog(vertexShader);
}

void ShaderProgram::showCompilerLog(unsigned int shader)
{
    int success{0};
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        SDL_Log("Error:Failed compile shader.What : %s",infoLog);
    }
}

void ShaderProgram::compileFragmentShader()
{
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1,(const GLchar *const *)(fragmentShaderFile.getContent()), nullptr);
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
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        SDL_Log("Error:Failed to link shader.What : %s",infoLog);

    }
}

void ShaderProgram::use()
{
    glUseProgram(shaderProgram);
}
