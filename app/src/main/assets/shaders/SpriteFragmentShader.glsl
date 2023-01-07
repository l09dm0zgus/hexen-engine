#version 310 es
precision mediump float;
out vec4 FragColor;

in vec2 textureCoordinate;

uniform sampler2D textures[10];
void main()
{
    FragColor = texture(textures[0],textureCoordinate);
}



