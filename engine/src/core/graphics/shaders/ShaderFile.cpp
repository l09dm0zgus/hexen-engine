//
// Created by cx9ps3 on 03.01.23.
//

#include "ShaderFile.hpp"
#include <SDL3/SDL.h>


void hexen::engine::graphics::shader::ShaderFile::read(const std::string &path)
{
    SDL_RWops *file = SDL_RWFromFile(path.c_str(),"r");
    if(file != nullptr)
    {
        int size = SDL_RWsize(file);
        SDL_Log("ShaderFile file size : %d", size);
        char *shaderData = new char[size];
        if(SDL_RWread(file,shaderData,size) < 0)
        {
            SDL_Log("Failed to read %s shader.\n",path.c_str());
        }

        shaderText.assign(shaderData, size);
        SDL_Log("Shader %s code : %s",path.c_str(),shaderText.c_str());

        delete [] shaderData;
        shaderData = nullptr;
    }
    else
    {
        SDL_Log("Failed to open %s shader.\n" ,path.c_str());
    }
    SDL_RWclose(file);
}

char *hexen::engine::graphics::shader::ShaderFile::getContent()
{
    return const_cast<char *>(shaderText.c_str());
}
