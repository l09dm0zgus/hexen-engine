//
// Created by cx9ps3 on 03.01.23.
//

#include "ShaderFile.h"
#include <fstream>
#include <sstream>
#include <SDL.h>

void ShaderFile::read(const std::string &path)
{
    SDL_RWops *file = SDL_RWFromFile(path.c_str(),"r");
    if(file != nullptr)
    {
        int size = SDL_RWsize(file);
        SDL_Log("ShaderFile file size : %d", size);
        shaderData = new char[size];
        if(SDL_RWread(file,shaderData,size,1) < 0)
        {
            SDL_Log("Failed to read %s shader.\n",path.c_str());
        }
    }
    else
    {
        SDL_Log("Failed to open %s shader.\n" ,path.c_str());
    }
    SDL_RWclose(file);
}

char *ShaderFile::getContent()
{
    return shaderData;
}

ShaderFile::~ShaderFile()
{
    if(shaderData != nullptr)
    {
        delete [] shaderData;
        shaderData = nullptr;
    }

}
