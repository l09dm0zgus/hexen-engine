#version 310 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoordinate;
layout (location = 2) in mat4 aInstanceMatrix;
out vec2 textureCoordinate;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * aInstanceMatrix * vec4(aPos,1.0);
    textureCoordinate = aTextureCoordinate;
}
