//
// Created by cx9ps3 on 03.01.23.
//

#ifndef BATTLEBLAZE_SHADERFILE_H
#define BATTLEBLAZE_SHADERFILE_H
#include <string>

class ShaderFile
{
private:
    char *shaderData{nullptr};
public:
    ~ShaderFile();
    void read( const std::string &path);
    char *getContent();
};


#endif //BATTLEBLAZE_SHADERFILE_H
